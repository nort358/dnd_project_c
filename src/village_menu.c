#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/village_menu.h"
#include "../include/hero.h"
#include "../include/mission.h"
#include "../include/save.h"
#include "../include/dungeon.h"
#include "../include/dungeon_name.h"

void village_menu(Hero *hero)
{
    int what;
    char typed[100];

    while (1)
    {
        printf("\n");
        printf("***************\n");
        printf("VILLAGE SCREEN\n");
        printf("***************\n");
        printf("Hero: %d HP | Money: %d\n", hero->life_points, hero->coins);
        printf("***************\n");
        printf("1. GO ON MISSION\n");
        printf("2. SLEEP (get HP back to 20)\n");
        printf("3. SEE MY STUFF\n");
        printf("4. KEEP GAME\n");
        printf("5. BACK TO START\n");
        printf("***************\n");
        printf("Type 1 to 5: ");

        if (fgets(typed, sizeof(typed), stdin))
        {
            typed[strcspn(typed, "\n")] = 0;
            what = atoi(typed);

            switch (what)
            {
            case 1:
            {
                MissionSystem missions;
                mission_init(&missions);

                mission_display_menu(&missions);

                int pick;
                scanf("%d", &pick);

                int ok = mission_select(&missions, pick, hero);
                if (ok >= 0)
                {
                    printf("\n>>> GOING INTO DUNGEON <<<\n");

                    Dungeon d;
                    if (pick == 1)
                    {
                        d = generate_dungeon(hero, ROTTING_SWAMP);
                        printf("Made Rotting Swamp dungeon\n");
                    }
                    else if (pick == 2)
                    {
                        d = generate_dungeon(hero, HAUNTED_MANSION);
                        printf("Made Haunted Mansion dungeon\n");
                    }
                    else if (pick == 3)
                    {
                        d = generate_dungeon(hero, CRYSTAL_CAVE);
                        printf("Made Crystal Cave dungeon\n");
                    }
                    else if (pick == 4)
                    {
                        d = generate_dungeon(hero, DARK_LORD_CASTLE);
                        printf("Made Dark Lord Castle dungeon\n");
                    }

                    printf("Dungeon has 10 rooms.\n");
                    printf("Room 1 is: ");
                    if (d.rooms[0].type == 1)
                    {
                        printf("BAD GUY\n");
                    }
                    else if (d.rooms[0].type == 2)
                    {
                        printf("TRAP!\n");
                    }
                    else
                    {
                        printf("nothing\n");
                    }

                    mission_update_progress(&missions, 1);
                }
                break;
            }

            case 2:
                printf("\nSleeping...\n");
                hero->life_points = 20;
                printf("HP is 20 now!\n");
                break;

            case 3:
                printf("\n=== MY STUFF ===\n");
                printf("HP: %d\n", hero->life_points);
                printf("Money: %d\n", hero->coins);
                printf("Sword? %s\n", hero->sword ? "YES" : "NO");
                printf("Armor? %s\n", hero->armor ? "YES" : "NO");
                printf("Health drinks: %d\n", hero->health_potions);
                printf("Missions done: %d/3\n",
                       (hero->first_mission_completed +
                        hero->second_mission_completed +
                        hero->third_mission_completed));
                break;

            case 4:
                save_game(hero);
                break;

            case 5:
                printf("\nGoing back to start...\n");
                return;

            case 9:
                hero->coins = hero->coins + 1000;
                printf("\nCHEAT! +1000 coins!\n");
                break;

            default:
                printf("\nWrong number! Use 1 to 5\n");
            }
        }

        printf("\nPress ENTER to go on...\n");
        getchar();
    }
}