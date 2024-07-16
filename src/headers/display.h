#ifndef DISPLAY_H /* Include guard */
#define DISPLAY_H

#include "position.h"
void display_board(Position *pos);
void display_move(int move);
void display_move_and_nodes(int move, uint64_t nodes);
void move_str_from_int(int move, char *s);
int move_int_from_str(char *s);
#endif