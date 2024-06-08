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

// UCI Helper Class Structure
typedef struct
{
    // Add any necessary fields here
} UCIHelper;

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
    char *cmd = strtok(command, " ");
    cmd = strtok(NULL, " ");
    cmd[strcspn(cmd, "\n")] = '\0';

    if (strcmp(cmd, "startpos") == 0)
    {
        SetBoardFromFen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", pos);
        cmd = strtok(NULL, " ");
        if (cmd && strcmp(cmd, "moves") == 0)
        {
            char *moves = strtok(NULL, "");
            if (moves)
            {
                // applyMoves(moves);
            }
        }
    }
    else if (strcmp(cmd, "fen") == 0)
    {
        char *fen = strtok(NULL, "");
        char *moves = strstr(fen, " moves");
        if (moves)
        {
            *moves = '\0'; // Terminate FEN string
            moves += 6;    // Move past " moves"
        }
        SetBoardFromFen(fen, pos);
        if (moves)
        {
            // applyMoves(moves);
        }
    }
}
// Handle the 'go' command
void go(char *command)
{
    // Start the engine's thinking process
    // RootSearch()
    // Example move (replace with actual move generation)
    // DisplayBoard(pos);
    RootSearch(pos,4);
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
