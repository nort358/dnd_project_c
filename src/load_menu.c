#include <stdio.h>
#include <stdlib.h>
#include "../include/load_menu.h"

void load_menu() {
    printf("\nISaved Games:\n\n");
    printf("1. Saved Game #1\n2. Saved Game #2"); // TODO load a list of actual saved games
    printf("\nSelect a game: ");
    int choice = 0;
    const int MAX = 2; // TODO change to actual max number of saved games
    // int check_is_num = scanf("%d", &choice);
    while(scanf("%d", &choice) != 1 || choice < 1 || choice > MAX) {
        while (getchar() != '\n');
        printf("Invalid choice. Please a number less than %d\n", MAX);
        // check_is_num = scanf("%d", &choice);
    }
    printf("\n\nLoading Saved Game #%d...\n", choice);
}