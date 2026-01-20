#ifndef TTT3D_H
#define TTT3D_H

#include <stdbool.h>
int simple_check_con(int size, int table[size][size]);
int simple_check_3d_con(int size, int table[size][size][size]);
void print_3d_table(int size, int table[size][size][size]);
bool play_3d(int size, int table[size][size][size], int player, int z, int y, int x);
int tic_tac_toe_3D();

#endif