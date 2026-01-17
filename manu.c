#include <stdio.h>
#include "./scalableTicc.h"

int main(void) {
    int choice;
    printf("Selection Menu:\n1. Play Game (1)\n2. Exit (2)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    if(choice - 1){
        printf("Exiting the program.\n");
        return 0;
    }
    scalable_ticc(5, 4);
    return 0;
}