#include <stdio.h>
#include <stdbool.h>

void print_table (int size, int table[size][size]);
char check_con (int size, int table[size][size]);
char check_con_rc (int size, int table[size][size], int row, int col);
bool is_bound (int row, int col, int n);
bool play (int size, int table[size][size], int player, int row, int col);


int main (void) {
    int size = 3;
    int table[size][size];
    for (int i = 0; i < size; i++) { //Reset table
        for (int j = 0; j < size; j++) {
            table[i][j] = -1;
        }
    }
    int row, column ,player = 1;
    char result = 0;

    while (!result) {
        print_table(size, table);
        printf("Player%d's turn\nEnter Row Column: ", player);
        scanf("%d%d", &row, &column);
        if (!is_bound(row, column, size)) {
            printf("Invalid Move. Try Again.\n");
            continue;
        }
        if (!play(size, table, player, row, column)) {
            printf("Invalid Move. Try Again.\n");
            continue;
        }
        result = check_con(size, table);
        player = player ^ 0b11; //Switch Player
    }

    if(result != -1){
        print_table(size, table);
        printf("Player%d Wins!!!", result);
    } else {
        printf("Ties.");
    }
    return 0;
}

void print_table (int size, int table[size][size]) {
    for (int i = 0; i < size * 2 - 1; i++) {
        for (int j = 0; j < size * 2 - 1; j++) {
            if (i % 2 == 1) {
                if (j % 2 == 1) {
                    printf("+");
                    continue;
                }
                printf("---");
                continue;
            }
            if (j % 2 == 1) {
                printf("|");
            } else {
                switch (table[i/2][j/2])
                {
                case -1:
                    printf("   ");
                    break;
                case 1:
                    printf(" X ");
                    break;
                case 2:
                    printf(" O ");
                    break;
                default:
                    printf(" %d ", table[i/2][j/2]);
                    break;
                }
            }
        }
        printf("\n");
    }
}

char check_con(int size, int table[size][size]) {
    char result = 0;
    bool one_found = 0;
    for (int i = 0; i < size; i++) { //Check every entries
        for (int j = 0; j < size; j++) {
            //printf("Checking %d,%d\n", i, j); //debug
            if (table[i][j] == -1) {
                one_found = 1;
                continue;
            }
            result = check_con_rc(size, table, i, j);
            //printf("%d\n", (int)result); //debug
            if (result != 0) return result;
        }
    }
    if (!one_found) return -1;
    return result;
}

char check_con_rc(int size, int table[size][size], int row, int col) {
    char player = table[row][col];
    for (int i = 0; i < 8; i++) {
        int count = 0;
        for (int j = 0; j < 3; j++) {
            if (i % 2 == 0) { //Verticle and Horizontal Check
                //debug
                //printf("Checking %d,%d for player %d\n", row, col, player);
                int con = (i / 2) % 4;
                switch (con)
                {
                case 0:
                    if(!is_bound(row - j, col, size)) break;
                    //printf("test"); //debug
                    if(table[row - j][col] == player) count++; //Up
                    break;
                case 1:
                    if(!is_bound(row, col + j, size)) break;
                    if(table[row][col + j] == player) count++; //Right
                    break;
                case 2:
                    if(!is_bound(row + j, col, size)) break;
                    if(table[row + j][col] == player) count++; //Down
                    break;
                case 3:
                    if(!is_bound(row, col - j, size)) break;
                    if(table[row][col - j] == player) count++; //Left
                    break;
                default:
                    printf("Invalid case!!\n");
                    break;
                }
                if (count >= 3) return player;
            } else { //Diagonal Check
                int con = (i / 2) % 4;
                switch (con)
                {
                    case 0:
                    if(!is_bound(row - j, col + j, size)) break;
                    if(table[row - j][col  + j] == player) count++; //North-East
                    break;
                    case 1:
                    if(!is_bound(row + j, col + j, size)) break;
                    if(table[row + j][col + j] == player) count++; //South-East
                    break;
                    case 2:
                    if(!is_bound(row + j, col - j, size)) break;
                    if(table[row + j][col - j] == player) count++; //South-West
                    break;
                    case 3:
                    if(!is_bound(row - j, col - j, size)) break;
                    if(table[row - j][col - j] == player) count++; //North-West
                    break;
                default:
                    printf("Invalid case!!\n");
                    break;
                }
            if (count >= 3) return player;
            }
        }
        //printf("Count: %d\n", count); //debug
    }
    return 0;
}

bool is_bound (int row, int col, int n) {
    return row < n && row >= 0 && col < n && col >= 0;
}

bool play (int size, int table[size][size], int player, int row, int col) {
    //debug
    //printf("Playing %d at %d,%d\n", player, row, col);
    if (table[row][col] != -1) {
        return false;
    }
    table[row][col] = player;
    return true;
}