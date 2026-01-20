#include <stdio.h>
#include <stdbool.h>
#include "./scalableTicc.h"

int scalable_ticc(int size, int winSize);
void print_table(int size, int table[size][size]);
char check_con(int size, int table[size][size], int winSize);
char check_con_rc(int size, int table[size][size], int row, int col, int winSize);
bool is_bound(int row, int col, int n);
bool play(int size, int table[size][size], int player, int row, int col);

int scalable_ticc(int size, int winSize)
{
    int table[size][size];
    for (int i = 0; i < size; i++)
    { // Reset table
        for (int j = 0; j < size; j++)
        {
            table[i][j] = -1;
        }
    }
    int row, column, player = 1; // Initailize player
    char result = 0;             // 0 => no Winner, -1 => ties, 1 => 1 Wins, 2 => 2 Wins

    while (!result)
    {                                                          // While no one wins
        print_table(size, table);                              // Print table
        printf("Player%d's turn\nEnter Row Column (1-%d): ", player, size); // Tell Whose turn
        scanf("%d%d", &row, &column);                          // Read input
        row--;
        column--;                                               // Adjust for 0 based index
        if (!is_bound(row, column, size))
        {                                         // Is not bound
            printf("Invalid Move. Try Again.\n"); // Tell "Invalid move"
            continue;
        }
        if (!play(size, table, player, row, column))
        {                                         // Is the square was already played
            printf("Invalid Move. Try Again.\n"); // Tell "invalid move"
            continue;
        }
        result = check_con(size, table, winSize); // Check winner
        player = player ^ 0b11;                   // Switch Player
    }

    if (result != -1)
    {                                       // If not ties
        print_table(size, table);           // Print final table
        printf("Player%d Wins!!!", result); // Tell winner
    }
    else
    {
        printf("Ties."); // Tell ties
    }
    return 0;
}

void print_table(int size, int table[size][size])
{
    for (int i = 0; i < size * 2 - 1; i++)
    {
        for (int j = 0; j < size * 2 - 1; j++)
        {
            if (i % 2 == 1)
            {
                if (j % 2 == 1)
                {
                    printf("+");
                    continue;
                }
                printf("---");
                continue;
            }
            if (j % 2 == 1)
            {
                printf("|");
            }
            else
            {
                switch (table[i / 2][j / 2])
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
                    printf(" %d ", table[i / 2][j / 2]);
                    break;
                }
            }
        }
        printf("\n");
    }
}

char check_con(int size, int table[size][size], int winSize)
{
    char result = 0;
    bool one_found = 0;
    for (int i = 0; i < size; i++)
    { // Check every entries
        for (int j = 0; j < size; j++)
        {
            // printf("Checking %d,%d\n", i, j); //debug
            if (table[i][j] == -1)
            {
                one_found = 1;
                continue;
            }
            result = check_con_rc(size, table, i, j, winSize);
            // printf("%d\n", (int)result); //debug
            if (result != 0)
                return result;
        }
    }
    if (!one_found)
        return -1;
    return result;
}

char check_con_rc(int size, int table[size][size], int row, int col, int winSize)
{
    char player = table[row][col];
    for (int i = 0; i < 8; i++)
    {
        int count = 0;
        for (int j = 0; j < winSize; j++)
        {
            if (i % 2 == 0)
            { // Verticle and Horizontal Check
                // debug
                // printf("Checking %d,%d for player %d\n", row, col, player);
                int con = (i / 2) % 4;
                switch (con)
                {
                case 0:
                    if (!is_bound(row - j, col, size))
                        break;
                    // printf("test"); //debug
                    if (table[row - j][col] == player)
                        count++; // Up
                    break;
                case 1:
                    if (!is_bound(row, col + j, size))
                        break;
                    if (table[row][col + j] == player)
                        count++; // Right
                    break;
                case 2:
                    if (!is_bound(row + j, col, size))
                        break;
                    if (table[row + j][col] == player)
                        count++; // Down
                    break;
                case 3:
                    if (!is_bound(row, col - j, size))
                        break;
                    if (table[row][col - j] == player)
                        count++; // Left
                    break;
                default:
                    printf("Invalid case!!\n");
                    break;
                }
                if (count >= winSize)
                    return player;
            }
            else
            { // Diagonal Check
                int con = (i / 2) % 4;
                switch (con)
                {
                case 0:
                    if (!is_bound(row - j, col + j, size))
                        break;
                    if (table[row - j][col + j] == player)
                        count++; // North-East
                    break;
                case 1:
                    if (!is_bound(row + j, col + j, size))
                        break;
                    if (table[row + j][col + j] == player)
                        count++; // South-East
                    break;
                case 2:
                    if (!is_bound(row + j, col - j, size))
                        break;
                    if (table[row + j][col - j] == player)
                        count++; // South-West
                    break;
                case 3:
                    if (!is_bound(row - j, col - j, size))
                        break;
                    if (table[row - j][col - j] == player)
                        count++; // North-West
                    break;
                default:
                    printf("Invalid case!!\n");
                    break;
                }
                if (count >= winSize)
                    return player;
            }
        }
        // printf("Count: %d\n", count); //debug
    }
    return 0;
}

bool is_bound(int row, int col, int n)
{
    return row < n && row >= 0 && col < n && col >= 0;
}

bool play(int size, int table[size][size], int player, int row, int col)
{
    // debug
    // printf("Playing %d at %d,%d\n", player, row, col);
    if (table[row][col] != -1)
    {
        return false;
    }
    table[row][col] = player;
    return true;
}