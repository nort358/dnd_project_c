#include <stdio.h>
#include <stdlib.h>
#include "../include/load_menu.h"

void menu() {
    printf("Initial Game Memu\n\n\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("\n\nChoose an action (1-2): ");
    int choice = 0;
    // int check_is_num = scanf("%d", &choice);
    while(scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
        while (getchar() != '\n');
        printf("Invalid choice. Please enter 1 or 2.\n");
        // check_is_num = scanf("%d", &choice);
    }
    printf("%d\n", choice);
    switch (choice) {
        case 1:
            printf("Starting a new game...\n");
            break;
            // new_game_fun();
        case 2:
            printf("Loading a saved game...\n");
            load_menu();
            break;
        }
}

int main() {
    menu();
    return 0;
}