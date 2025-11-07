#include <stdio.h>
#include <stdlib.h>
#include "../include/load_menu.h"
#include <string.h>
#include <strings.h> // for strcasecmp 

void load_menu() {
    printf("\nSaved Games:\n\n");
    printf("1. Saved Game #1\n2. Saved Game #2\n3. Saved Game #3\n"); // TODO load a list of actual saved games
    printf("\nSelect a game: ");
    int choice = 0;
    const int MAX = 3; // TODO change to actual max number of saved games
    while(scanf("%d", &choice) != 1 || choice < 1 || choice > MAX) {
        while (getchar() != '\n');
        printf("Insert an action [1-%d]: ", MAX);
    }
    printf("\nSelect one of the following action: \n");
    printf("\n1. Load \n2. Delete \n");
    printf("\nInsert the action [1, 2]: ");
    while(scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)){
        while (getchar() != '\n');
        printf("\nChoose an action [1, 2]: ");
    }
    switch (choice) {
        case 1:
            printf("\n\nLoading Saved Game #%d...\n", choice);
            printf("\nGoing to Village\n");
            // TODO village_menu();
            break;
        case 2:
            printf("\nAre you sure you want to permanently delete the save? [Yes/No]: ");
            char is_delete[100];
            scanf("%s", is_delete);
            if (!((strcasecmp(is_delete, "yes")) && (strcasecmp(is_delete, "y")))) { // strcasecmp is a case-insensitive strcmp, eg "yes" == "YeS"
                printf("Saved Game #%d deleted.\n", choice);
                load_menu(); 
            //  TODO add delete_saved_game(choice);
            } else if (!((strcasecmp(is_delete, "no")) && (strcasecmp(is_delete, "n")))) {
                printf("\nDelete action cancelled.\n");
                load_menu(); 
            }
            else {
                printf("\nReturning to Saved Games\n");
                load_menu(); // go back to load menu
            }
        }
}