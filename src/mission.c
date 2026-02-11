#include "mission.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mission_init(MissionSystem *system)
{
    // Mission 1: Rotting Swamp
    system->missions[0].dungeon_name = ROTTING_SWAMP;
    system->missions[0].status = 0; // 0 = it means not started yet!
    strcpy(system->missions[0].name, "Rotting Swamp");
    strcpy(system->missions[0].objective, "Kill 3 Orc Generals");
    system->missions[0].objectives_completed = 0;
    system->missions[0].objectives_required = 3;

    // Mission 2: Haunted Mansion
    system->missions[1].dungeon_name = HAUNTED_MANSION;
    system->missions[1].status = 0;
    strcpy(system->missions[1].name, "Haunted Mansion");
    strcpy(system->missions[1].objective, "Get key and kill Vampire");
    system->missions[1].objectives_completed = 0;
    system->missions[1].objectives_required = 2;

    // Mission 3: Crystal Cave
    system->missions[2].dungeon_name = CRYSTAL_CAVE;
    system->missions[2].status = 0;
    strcpy(system->missions[2].name, "Crystal Cave");
    strcpy(system->missions[2].objective, "Find Hero's Sword");
    system->missions[2].objectives_completed = 0;
    system->missions[2].objectives_required = 1;

    // Mission 4: Dark Lord (final boss)
    system->missions[3].dungeon_name = DARK_LORD_CASTLE;
    system->missions[3].status = 0;
    strcpy(system->missions[3].name, "Dark Lord Castle");
    strcpy(system->missions[3].objective, "Beat the Dark Lord");
    system->missions[3].objectives_completed = 0;
    system->missions[3].objectives_required = 1;

    system->current_mission = -1;
    system->missions_completed = 0;
    system->final_unlocked = 0;
}

// it was buggy before
void mission_display_menu(MissionSystem *system)
{
    printf("\n=== MISSION LIST ===\n");

    for (int i = 0; i < 3; i++)
    {
        printf("%d. %s\n", i + 1, system->missions[i].name);

        if (system->missions[i].status == 0)
        {
            printf("   Status: NOT STARTED\n");
        }
        else if (system->missions[i].status == 1)
        {
            printf("   Status: IN PROGRESS (%d/%d)\n",
                   system->missions[i].objectives_completed,
                   system->missions[i].objectives_required);
        }
        else
        {
            printf("   Status: DONE!\n");
        }

        printf("   Goal: %s\n\n", system->missions[i].objective);
    }

    printf("4. %s\n", system->missions[3].name);
    if (system->final_unlocked == 1)
    {
        printf("   Status: READY TO PLAY\n");
    }
    else
    {
        printf("   Status: LOCKED (finish 3 missions first)\n");
    }

    printf("\n0. Back to village\n");
    printf("Pick one [0-4]: ");
}

// This function was hard , had to fix it 3 times :>!
int mission_select(MissionSystem *system, int choice, Hero *hero)
{
    (void)hero;
    if (choice == 0)
        return -1; // going back

    if (choice < 1 || choice > 4)
    {
        printf("WRONG NUMBER!\n");
        return -1;
    }

    int idx = choice - 1; // array starts at 0

    // Check if final mission is locked
    if (idx == 3 && system->final_unlocked == 0)
    {
        printf("Hey! Finish 3 missions first!\n");
        return -1;
    }

    // Start the mission
    system->missions[idx].status = 1;
    system->current_mission = idx;

    printf("\n  Starting Mission   \n");
    printf("Mission: %s\n", system->missions[idx].name);
    printf("Goal: %s\n", system->missions[idx].objective);
    printf("Good luck!\n");

    return idx;
}

void mission_update_progress(MissionSystem *system, int add_progress)
{
    int now = system->current_mission;
    if (now < 0)
        return;

    // Add progress
    system->missions[now].objectives_completed += add_progress;

    printf("Progress update: %d/%d\n",
           system->missions[now].objectives_completed,
           system->missions[now].objectives_required);

    // Check if mission is done
    if (system->missions[now].objectives_completed >=
        system->missions[now].objectives_required)
    {

        system->missions[now].status = 2;
        system->missions_completed++;
        system->current_mission = -1;

        printf("\n*** CONGRATS! MISSION COMPLETE! ***\n");

        // Unlock final mission if 3 are done
        if (now < 3 && system->missions_completed >= 3)
        {
            system->final_unlocked = 1;
            printf(" FINAL MISSION UNLOCKED! \n");
            printf("You can now fight the Dark Lord :)!\n");
        }
    }
}
void mission_inside_menu(MissionSystem *system, Hero *hero)
{
    int choice;
    char input[100];

    while (1)
    {
        printf("\n");
        printf("===============================\n");
        printf("      MISSION MENU\n");
        printf("===============================\n");
        printf("Mission: %s\n", system->missions[system->current_mission].name);
        printf("Objective: %s\n", system->missions[system->current_mission].objective);
        printf("Progress: %d/%d\n",
               system->missions[system->current_mission].objectives_completed,
               system->missions[system->current_mission].objectives_required);
        printf("===============================\n");
        printf("1. Explore Dungeon Room\n");
        printf("2. Shop\n");
        printf("3. Show Inventory\n");
        printf("4. Return to Village\n");
        printf("===============================\n");
        printf("Your choice (1-4): ");

        fgets(input, 100, stdin);
        if (strlen(input) > 0)
        {
            input[strlen(input) - 1] = '\0';
        }
        choice = atoi(input);

        if (choice == 1)
        {
            printf("\nExploring room...\n");
            printf("Dungeon system not ready yet!\n");

            mission_update_progress(system, 1);
        }
        else if (choice == 2)
        {
            printf("\nOpening shop...\n");
            printf("Shop system not ready yet!\n");
        }
        else if (choice == 3)
        {
            printf("\n--- INVENTORY ---\n");
            printf("HP: %d\n", hero->life_points);
            printf("Coins: %d\n", hero->coins);
            printf("Sword: %s\n", hero->sword ? "YES" : "NO");
            printf("Armor: %s\n", hero->armor ? "YES" : "NO");
            printf("Health Potions: %d\n", hero->health_potions);
        }
        else if (choice == 4)
        {
            printf("\nReturning to village...\n");

            if (system->missions[system->current_mission].status != MISSION_COMPLETED)
            {
                printf("Mission not completed! Pay 50 coins to leave?\n");
                printf("You have %d coins. (y/n): ", hero->coins);

                char answer[10];
                fgets(answer, 10, stdin);
                answer[strlen(answer) - 1] = '\0';

                if ((answer[0] == 'y' || answer[0] == 'Y') && hero->coins >= 50)
                {
                    hero->coins -= 50;
                    printf("Paid 50 coins. Returning to village.\n");
                    break;
                }
                else if (hero->coins < 50)
                {
                    printf("Not enough coins! You need 50, but have %d.\n", hero->coins);
                    printf("You must complete the mission first.\n");
                }
                else
                {
                    printf("Staying in mission.\n");
                    continue;
                }
            }
            else
            {
                printf("Mission completed! Returning to village.\n");
                break;
            }
        }
        else
        {
            printf("\nWrong choice! Please enter 1-4.\n");
        }
    }
}