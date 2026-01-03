#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/village_menu.h"
#include "../include/hero.h"

void village_menu(Hero *hero)
{
    int choice;
    char input[100];

    while (1)
    {
        printf("\n");
        printf("***************\n");
        printf("VILLAGE MENU\n");
        printf("***************\n");
        printf("Hero Status: %d HP | %d coins\n", hero->life_points, hero->coins);
        printf("***************\n");
        printf("1. START A MISSION\n");
        printf("2. REST (Restore HP to 20)\n");
        printf("3. INVENTORY\n");
        printf("4. SAVE THE GAME\n");
        printf("5. EXIT TO MAIN MENU\n");
        printf("***************\n");
        printf("Choose an action [1-5]: ");

        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            input[strcspn(input, "\n")] = '\0';
            choice = atoi(input);

            switch (choice)
            {
            case 1:
                printf("\nSTARTING A MISSION...\n");
                printf("MISSION SYSTEM COMING SOON! :)\n");
                break;

            case 2:
                printf("\nResting at the village...\n");
                hero->life_points = 20;
                printf("HP restored to 20!\n");
                break;

            case 3:
                printf("\n***** INVENTORY *****\n");
                printf("Life Points: %d\n", hero->life_points);
                printf("Coins: %d\n", hero->coins);
                printf("Sword: %s\n", hero->sword ? "YES" : "NO");
                printf("Armor: %s\n", hero->armor ? "YES" : "NO");
                printf("Health Potions: %d\n", hero->health_potions);
                printf("Missions: %d/%d\n",
                       (hero->first_mission_completed +
                        hero->second_mission_completed +
                        hero->third_mission_completed),
                       3);
                break;

            case 4:
                printf("\nSaving the game...\n");
                printf("(Save system coming soon!)\n");
                break;

            case 5:
                printf("\nReturning to Main Menu...\n");
                return;

            default:
                printf("\nInvalid choice! Please enter 1-5\n");
            }
        }

        printf("\nPress Enter to continue...");
        getchar();
    }
}