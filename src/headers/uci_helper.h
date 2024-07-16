#ifndef UCI_HELPER_H /* Include guard */
#define UCI_HELPER_H

int uci_loop();
void uci();
void isready();
void setoption(char *command);
void ucinewgame();
void position(char *command);
void go(char *command);
void stop();
void quit();
void parseCommand(char *command);

typedef struct UCIHelper
{
    // Add any necessary fields here
    int wtime;
    int btime;
    int winc;
    int binc;

} UCIHelper;

#endif