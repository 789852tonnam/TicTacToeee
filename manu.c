#include <stdio.h>
#include "./scalableTicc.h"

void game_control(int mode, int gameType) {
    // Placeholder for game control logic
    switch (gameType)
    {
    case 1:
        scalable_ticc(3, 3);
        break;
    case 2:
        {
            int size, winSize;
            printf("Enter board size: ");
            scanf("%d", &size);
            printf("Enter win size: ");
            scanf("%d", &winSize);
            scalable_ticc(size, winSize);
        }
        break;
    case 3:
        break;
    
    default:
        break;
    }
}

int main(void) {
    int choice;
    printf("Selection Menu:\n1. Play Game (1)\n2. Exit (2)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if(choice - 1){
        printf("Exiting the program.\n");
        return 0;
    }
    
    printf("Gameplay Section:\n1: Standard Mode (3x3, win 3)\n2: Scalable Mode\n3: 3D Mode\n");
    int GameChoice;
    scanf("%d", &GameChoice);
    
    printf("Mode Selection\n1: 2 Player Mode\n2: Bot Mode\n");
    int ModeChoice;
    scanf("%d", &ModeChoice);
    
    game_control(ModeChoice, GameChoice);
    
    return 0;
}