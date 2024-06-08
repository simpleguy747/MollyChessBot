#ifndef UCI_HELPER_H /* Include guard */
#define UCI_HELPER_H

int UciLoop();
void uci();
void isready();
void setoption(char *command);
void ucinewgame();
void position(char *command);
void go(char *command);
void stop();
void quit();
void parseCommand(char *command);

#endif