#include "mission.h"
#include <stdio.h>
#include <string.h>

// Made by Mahsa
void mission_init(MissionSystem *system)
{
    // Mission 1: Rotting Swamp
    system->missions[0].type = 1;   // 1 = Rotting Swamp
    system->missions[0].status = 0; // 0 = it means not started yet!
    strcpy(system->missions[0].name, "Rotting Swamp");
    strcpy(system->missions[0].objective, "Kill 3 Orc Generals");
    system->missions[0].objectives_completed = 0;
    system->missions[0].objectives_required = 3;

    // Mission 2: Haunted Mansion
    system->missions[1].type = 2;
    system->missions[1].status = 0;
    strcpy(system->missions[1].name, "Haunted Mansion");
    strcpy(system->missions[1].objective, "Get key and kill Vampire");
    system->missions[1].objectives_completed = 0;
    system->missions[1].objectives_required = 2;

    // Mission 3: Crystal Cave
    system->missions[2].type = 3;
    system->missions[2].status = 0;
    strcpy(system->missions[2].name, "Crystal Cave");
    strcpy(system->missions[2].objective, "Find Hero's Sword");
    system->missions[2].objectives_completed = 0;
    system->missions[2].objectives_required = 1;

    // Mission 4: Dark Lord (final boss)
    system->missions[3].type = 4;
    system->missions[3].status = 0;
    strcpy(system->missions[3].name, "Dark Lord Castle");
    strcpy(system->missions[3].objective, "Beat the Dark Lord");
    system->missions[3].objectives_completed = 0;
    system->missions[3].objectives_required = 1;

    system->current_mission = -1; // -1 means no mission active
    system->missions_completed = 0;
    system->final_unlocked = 0; // 0 = locked!!
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
int mission_select(MissionSystem *system, int choice)
{
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
    system->missions[idx].status = 1; // 1 = in progress
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
        return; // no active mission

    // Add progress
    system->missions[now].objectives_completed += add_progress;

    printf("Progress update: %d/%d\n",
           system->missions[now].objectives_completed,
           system->missions[now].objectives_required);

    // Check if mission is done
    if (system->missions[now].objectives_completed >=
        system->missions[now].objectives_required)
    {

        system->missions[now].status = 2; // 2 = completed
        system->missions_completed++;
        system->current_mission = -1; // reset current mission

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