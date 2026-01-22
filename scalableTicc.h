#ifndef SCALABLE_TICC_H
#define SCALABLE_TICC_H

#include <stdbool.h>
int scalable_ticc(int size, int winSize, int mode);
void print_table(int size, int table[size][size]);
char check_con(int size, int table[size][size], int winSize);
char check_con_rc(int size, int table[size][size], int row, int col, int winSize);
bool is_bound(int row, int col, int n);
bool play(int size, int table[size][size], int player, int row, int col);

#endif // SCALABLE_TICC_H