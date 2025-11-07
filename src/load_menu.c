#include <stdio.h>
#include <stdlib.h>

void load_menu() {
    printf("\nISaved Games:\n\n");
    pxrintf("1. Saved Game #1\n2. Saved Game #2"); // TODO load a list of actual saved games
    printf("\nSelect a game: ");
    int choice = 0;
    scanf("%d", &choice);
    const int MAX = 2; // TODO change to actual max number of saved games
    while(choice != MAX) {
        printf("Invalid choice. Please enter 1 or 2.\n");
        scanf("%d", &choice);
    }
}