#include <stdio.h>
#include "scalableTicc.h"
#include "TTT3D.h"
#include <stdbool.h>

int simple_check_con(int size, int table[size][size]);
int simple_check_3d_con(int size, int table[size][size][size]);
void print_3d_table(int size, int table[size][size][size]);
bool play_3d(int size, int table[size][size][size], int player, int z, int y, int x);
int tic_tac_toe_3D();

int tic_tac_toe_3D() {
    // Placeholder for 3D Tic Tac Toe game logic
    int size = 3;
    int table[size][size][size]; // 3D array
    int current_player = 1; // 0 for X, 1 for O
    int result = 0;
    // Initialize the 3D table
    for(int z = 0; z < size; z++) {
        for(int y = 0; y < size; y++) {
            for(int x = 0; x < size; x++) {
                table[z][y][x] = -1; // Empty cell
            }
        }
    }

    while(!result) {
        print_3d_table(size, table);
        int z, y, x;
        printf("Player %d's turn. Enter level (1-%d), row (1-%d), column (1-%d): ", current_player, size, size, size);
        scanf("%d %d %d", &z, &y, &x);
        z--; y--; x--; // Adjust for 0-based index
        
        if(play_3d(size, table, current_player, z, y, x)) {
            result = simple_check_3d_con(size, table);
            if(result == 0) {
                current_player = current_player ^ 0b11; // Switch player
            }
        }
    }

    if(result != -1) {
        print_3d_table(size, table);
        printf("Player %d Wins!!!\n", result);
    } else {
        printf("It's a Tie!\n");
    }
    
    print_3d_table(size, table);
    
    return 0;
}

int simple_check_con(int size, int table[size][size]) {
    // Placeholder for win condition check logic
    // Horizontal and Vertical checks for 3x3
    if (table[0][0] != -1 &&
        table[0][0] == table[0][1] &&
        table[0][1] == table[0][2]) {
        return table[0][0];
    }
    if (table[1][0] != -1 &&
        table[1][0] == table[1][1] &&
        table[1][1] == table[1][2]) {
        return table[1][0];
    }
    if (table[2][0] != -1 &&
        table[2][0] == table[2][1] &&
        table[2][1] == table[2][2]) {
        return table[2][0];
    }
    if (table[0][0] != -1 &&
        table[0][0] == table[1][0] &&
        table[1][0] == table[2][0]) {
        return table[0][0];
    }
    if (table[0][1] != -1 &&
        table[0][1] == table[1][1] &&
        table[1][1] == table[2][1]) {
        return table[0][1];
    }
    if (table[0][2] != -1 &&
        table[0][2] == table[1][2] &&
        table[1][2] == table[2][2]) {
        return table [0][2];
    }

    // Diagonal checks
    if (table[0][0] != -1 &&
        table[0][0] == table[1][1] &&
        table[1][1] == table[2][2]) {
        return table[0][0];
    }
    if (table[0][2] != -1 &&
        table[0][2] == table[1][1] &&
        table[1][1] == table[2][0]) {
        return table[0][2];
    }

    return 0;
}

int simple_check_3d_con(int size, int table[size][size][size]) {
    // Placeholder for 3D win condition check logic
    // Check front planes
    for (int z = 0; z < size; z++) {
        int result = simple_check_con(size, table[z]);
        if (result != 0 && result != -1) {
            return result;
        }
    }
    // Check side planes
    for (int y = 0; y < size; y++) {
        int temp_table[size][size];
        for (int z = 0; z < size; z++) {
            for (int x = 0; x < size; x++) {
                temp_table[z][x] = table[z][y][x];
            }
        }
        int result = simple_check_con(size, temp_table);
        if (result != 0 && result != -1) {
            return result;
        }
    }
    // Check special diagonals
    // Diagonal from x plane
    {
        int temp_table[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                temp_table[i][i] = table[i][i][j];
            }
        }
        int result = simple_check_con(size, temp_table);
        if (result != 0 && result != -1) {
            return result;
        }
    }
    {
        int temp_table[size][size];
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                temp_table[i][size - 1 - i] = table[i][i][j];
            }
        }
        int result = simple_check_con(size, temp_table);
        if (result != 0 && result != -1) {
            return result;
        }
    }

    // Check if tie
    int is_tie = 0;
    for (int z = 0; z < size; z++) {
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (table[z][y][x] == -1) {
                    is_tie = 1;
                    break;
                }
            }
        }
    }

    if(!is_tie) {
        return -1; // Tie
    }
    return 0;
}

void print_3d_table(int size, int table[size][size][size]) {
    for (int z = 0; z < size; z++) {
        printf("Level %d:\n", z + 1);
        print_table(size, table[z]);
        printf("\n");
    }
}

bool play_3d(int size, int table[size][size][size], int player, int z, int y, int x) {
    if (table[z][y][x] == -1) {
        table[z][y][x] = player;
        return true;
    } else if(z < 0 || z >= size || y < 0 || y >= size || x < 0 || x >= size) {
        printf("Invalid move! Try again.\n");
        return false;
    } else {
        printf("Cell already occupied! Try again.\n");
        return false;
    }
}