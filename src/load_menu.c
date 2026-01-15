#include <stdio.h>
#include <stdlib.h>
#include "../include/load_menu.h"
#include <string.h>
#include "../include/save.h"
#include "../include/hero.h"
#include "../include/village_menu.h"

void print_saved_games(SaveList saves) {
    if (saves.saves == 0) {
        printf("No saved games found.\n");
        return;
    }
    printf("Saved Games:\n");
    for (int i = 0; i < saves.count; i++) { // TODO change 3 to actual number of saves
        printf("%d. Save #%d | Date: %s", i + 1, saves.saves[i].save_idx, ctime(&saves.saves[i].timestamp));
    }
}
void update_hero_by_id(SaveList saves, int save_idx, Hero* hero) {
    for (int i = 0; i < saves.count; i++) {
        if (saves.saves[i].save_idx == save_idx) {
            *hero = saves.saves[i].hero;
            return;
        }
    }
}

void load_menu(Hero* hero) {
    SaveList saves = load_saves();
    printf("\nSaved Games:\n\n");
    print_saved_games(saves);
    printf("\nSelect a game: ");
    int choice = 0;
    int save_idx=-1;
    while(scanf("%d", &choice) != 1 || choice < 1 || choice > saves.count) {
        while (getchar() != '\n');
        printf("Choose the game [1-%d]: ", saves.count);
    }    
    save_idx=choice;
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
            update_hero_by_id(saves, save_idx, hero);
            printf("\nGoing to Village\n");
            village_menu(hero);
            break;
        case 2:
            printf("\nAre you sure you want to permanently delete the save? [Yes/No]: ");
            char is_delete[100];
            scanf("%s", is_delete);
            if (!((strcasecmp(is_delete, "yes")) && (strcasecmp(is_delete, "y")))) { // strcasecmp is a case-insensitive strcmp, eg "yes" == "YeS"
                delete_save(save_idx);
                printf("Saved Game #%d deleted.\n", choice);
                load_menu(hero); 
            //  TODO add delete_saved_game(choice);
            } else if (!((strcasecmp(is_delete, "no")) && (strcasecmp(is_delete, "n")))) {
                printf("\nDelete action cancelled.\n");
                load_menu(hero); 
            }
            else {
                printf("\nReturning to Saved Games\n");
                load_menu(hero); // go back to load menu
            }
            break;
        }
}