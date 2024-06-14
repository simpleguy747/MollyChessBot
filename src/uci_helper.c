#include "uci_helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "position.h"
#include "search.h"
#include "fen_manager.h"
#include "init.h"
#include "magic_bitboards.h"
#include "display.h"
#include "utilities.h"
#include "movegen.h"
#include "move_manager.h"
#include "assert.h"

Position pos[1];
// Main function
int UciLoop()
{
    char command[256];
    InitMagicsAll();

    // Main loop to read commands
    while (1)
    {
        if (!fgets(command, sizeof(command), stdin))
        {
            break;
        }
        parseCommand(command);
    }

    return 0;
}

// Function Definitions

// Handle the 'uci' command
void uci()
{
    printf("id name MollyBot\n");
    printf("id author CoolGuy747\n");
    // Add options here
    printf("uciok\n");
    fflush(stdout);
}

// Handle the 'isready' command
void isready()
{
    printf("readyok\n");
    fflush(stdout);
}

// Handle the 'setoption' command
void setoption(char *command)
{
    // Parse and set options here
    printf("Option set: %s\n", command);
}

// Handle the 'ucinewgame' command
void ucinewgame()
{
    InitAll(pos);
    // Initialize new game settings here
}

// Handle the 'position' command
void position(char *command)
{
    command += 9; // Skip "position "

    if (strncmp(command, "startpos", 8) == 0)
    {
        SetBoardFromFen(START_POSITION, pos);
        command += 8; // Move past "startpos"

        if (*command == ' ')
        {
            command++; // Move past the space after "startpos"
        }

        if (strncmp(command, "moves", 5) == 0)
        {
            command += 6; // Move past "moves "
        }
    }
    else
    {
        char *fen = strstr(command, "fen ");
        if (fen)
        {
            fen += 4; // Move past "fen "
            char *moves = strstr(fen, " moves");
            if (moves)
            {
                *moves = '\0'; // Terminate FEN string
                moves += 7;    // Move past " moves "
            }
            SetBoardFromFen(fen, pos);
            command = moves;
        }
        else
        {
            // Handle error case: no "fen" or "startpos" found
            return;
        }
    }

    // Process moves if any
    if (command)
    {

        command[strcspn(command, "\n")] = '\0';
        char *moveStr = strtok(command, " ");

        while (moveStr != NULL)
        {
            // Replace with actual function to convert moveStr to move
            int moveInt = MoveIntFromStr(moveStr);
            MoveList moveList;
            GenerateMoves(pos, &moveList);
            int moveMade = 0;
            for (int index = 0; index < moveList.count; index++)
            {
                if ((moveList.moves[index].move & 0xfff) == moveInt)
                {
                    MakeMove(pos, moveList.moves[index].move);
                    pos->sideToMove ^= 1;
                    moveMade = 1;
                    break;
                }
            }
            assert(moveMade != 0);
            moveStr = strtok(NULL, " ");
        }
    }
}

// Handle the 'go' command
void go(char *command)
{
    UCIHelper uciHelper;
    const char *delimiters = " \t\n";
    char *token = strtok(command, delimiters);
    // Loop through the tokens
    while (token != NULL)
    {
        if (strcmp(token, "wtime") == 0)
        {
            token = strtok(NULL, delimiters);
            uciHelper.wtime = atoi(token);
        }
        if (strcmp(token, "btime") == 0)
        {
            token = strtok(NULL, delimiters);
            uciHelper.btime = atoi(token);
        }
        if (strcmp(token, "winc") == 0)
        {
            token = strtok(NULL, delimiters);
            uciHelper.winc = atoi(token);
        }
        if (strcmp(token, "binc") == 0)
        {
            token = strtok(NULL, delimiters);
            uciHelper.binc = atoi(token);
        }

        token = strtok(NULL, delimiters);
    }

    // printf("wtime%d,btime:%d,winc:%d,binc:%d\n", uciHelper.wtime, uciHelper.btime, uciHelper.winc, uciHelper.binc);
    RootSearch(&uciHelper, pos, 4);
    fflush(stdout);
}

// Handle the 'stop' command
void stop()
{
    // Stop the engine's thinking process
    printf("Engine stopped\n");
}

// Handle the 'quit' command
void quit()
{
    // Clean up and exit
    printf("Quitting...\n");
    exit(0);
}

// Parse and handle commands
void parseCommand(char *command)
{
    if (strncmp(command, "ucinewgame", 10) == 0)
    {
        ucinewgame();
    }
    else if (strncmp(command, "isready", 7) == 0)
    {
        isready();
    }
    else if (strncmp(command, "setoption", 9) == 0)
    {
        setoption(command);
    }
    else if (strncmp(command, "uci", 3) == 0)
    {
        uci();
    }

    else if (strncmp(command, "position", 8) == 0)
    {
        position(command);
    }
    else if (strncmp(command, "go", 2) == 0)
    {
        go(command);
    }
    else if (strncmp(command, "stop", 4) == 0)
    {
        stop();
    }
    else if (strncmp(command, "quit", 4) == 0)
    {
        quit();
    }
    else
    {
        printf("Unknown command: %s", command);
    }
}
