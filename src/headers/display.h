#ifndef DISPLAY_H /* Include guard */
#define DISPLAY_H

#include "position.h"
void DisplayBoard(Position *pos);
void DisplayMove(int move);
void DisplayMoveAndNodes(int move, uint64_t nodes);
void MoveStrFromInt(int move, char *s);
int MoveIntFromStr(char *s);
#endif