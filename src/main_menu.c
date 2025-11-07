#include <stdio.h>
#include <stdlib.h>

void display_menu() {
    printf("Initial Game Memu\n\n\n");
    printf("1. New Game\n");
    printf("2. Load Game\n");
    printf("\n\nChoose an action (1-2): ");
    // might be char or float
    int choice = 0;
    scanf("%d", &choice);
    while(choice != 1 && choice != 2) {
        printf("Invalid choice. Please enter 1 or 2.\n");
        scanf("%d", &choice);
    }
    printf("%d\n", choice);
    switch (choice) {
        case 1:
            printf("Starting a new game...\n");
            break;
            // new_game_fun();
        case 2:
            printf("Loading a saved game...\n");
            break;
            // load_game_fun();
        }
    // if (choice == 1) {
    //     printf("Starting a new game...\n");
    //     // new_game_fun();
    // } else if (choice == 2) {
    //     printf("Loading a saved game...\n");
    //     // load_game_fun();

}

int main() {
    display_menu();
    return 0;
}