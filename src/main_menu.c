#include <stdio.h>
#include <stdlib.h>
#include "../include/load_menu.h"

void main_menu() {
    printf("\nInitial Game Memu\n\n\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("\n\nChoose an action (1-2): ");
    int choice = 0;
    while(scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)){ // scanf returns the number of successfully read items. if it's not 1, the input was invalid
        while (getchar() != '\n');
        printf("Choose an action: ");
    }
    switch (choice) {
        case 1:
            printf("Starting a new game...\n");
            break; // if you dont't put break here, it will continue to case 2
            // TODO village_menu();
        case 2:
            printf("Loading a saved game...\n");
            load_menu();
            break;
        }
}

int main() {
    main_menu();
    return 0;
}