#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/village_menu.h"
#include "../include/hero.h"
#include "../include/mission.h"
#include "../include/save.h"
#include "../include/dungeon.h"
#include "../include/dungeon_name.h"

// 1 = win, 0 = hero dies:)
int fight_enemy(Hero *h, Room *r)
{
    printf("\n--- FIGHT! ---\n");
    printf("Enemy: %d (need %d+ to hit)\n", r->name, r->fatal_strike); // %d, not %s

    while (h->life_points > 0)
    {
        int attack = rand() % 6 + 1;
        if (h->sword)
            attack += 1;

        printf("You roll %d", attack - (h->sword ? 1 : 0));
        if (h->sword)
            printf(" +1 sword = %d", attack);
        printf("\n");

        if (attack >= r->fatal_strike)
        {
            printf("*** VICTORY! ***\n");
            h->coins += r->reward_coins;
            printf("You got %d coins! (now %d)\n", r->reward_coins, h->coins);
            return 1;
        }
        else
        {
            int dmg = r->damage;
            if (h->armor)
                dmg -= 1;
            if (dmg < 1)
                dmg = 1;
            h->life_points -= dmg;
            printf("Enemy hits for %d damage! You have %d HP left.\n", dmg, h->life_points);

            if (h->life_points <= 0)
            {
                printf("\n*** YOU DIED... GAME OVER ***\n");
                return 0;
            }
        }
    }
    return 0;
}

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

            switch (what) // <-- braces must be here!
            {
            case 1:
            {
                // --- Mission menu ---
                MissionSystem missions;
                mission_init(&missions);
                mission_display_menu(&missions);

                int pick;
                scanf("%d", &pick);

                int mission_index = mission_select(&missions, pick, hero);
                if (mission_index >= 0)
                {
                    printf("\n=== ENTERING DUNGEON ===\n");

                    // --- Generate correct dungeon ---
                    Dungeon d;
                    if (pick == 1)
                        d = generate_dungeon(hero, ROTTING_SWAMP);
                    else if (pick == 2)
                        d = generate_dungeon(hero, HAUNTED_MANSION);
                    else if (pick == 3)
                        d = generate_dungeon(hero, CRYSTAL_CAVE);
                    else if (pick == 4)
                        d = generate_dungeon(hero, DARK_LORD_CASTLE);

                    printf("Dungeon has 10 rooms.\n\n");

                    // --- Objective counter for Rotting Swamp ---
                    int generals_killed = 0;

                    // --- Go through each room ---
                    for (int i = 0; i < 10; i++)
                    {
                        printf("--- Room %d/%d ---\n", i + 1, 10);
                        printf("You see: %d\n", d.rooms[i].name); // %d, not %s

                        // --- EMPTY ---
                        if (d.rooms[i].type == 0)
                        {
                            printf("Nothing here. You move on.\n");
                        }
                        // --- ENEMY ---
                        else if (d.rooms[i].type == 1)
                        {
                            int win = fight_enemy(hero, &d.rooms[i]);
                            if (win == 0)
                            {
                                printf("\nReturning to main menu...\n");
                                return; // hero dead → back to main menu
                            }

                            // --- Check if enemy is an Orc General ---
                            if (d.rooms[i].name == ORC_GENERAL)
                            {
                                generals_killed++;
                                printf("Orc Generals defeated: %d/3\n", generals_killed);

                                if (generals_killed >= 3)
                                {
                                    printf("\n*********************************\n");
                                    printf("*** ROTTING SWAMP COMPLETE! ***\n");
                                    printf("*********************************\n");
                                    hero->first_mission_completed = 1;
                                    break;
                                }
                            }
                        }
                        // --- TRAP ---
                        else if (d.rooms[i].type == 2)
                        {
                            int dmg = d.rooms[i].damage;

                            if (d.rooms[i].damage == 0)
                                dmg = rand() % 6 + 1;

                            hero->life_points -= dmg;
                            printf("TRAP! You lose %d HP. (HP now %d)\n", dmg, hero->life_points);

                            if (hero->life_points <= 0)
                            {
                                printf("\n*** YOU DIED... GAME OVER ***\n");
                                return;
                            }
                        }

                        printf("\nPress Enter to continue...");
                        getchar();
                        getchar();
                    }

                    printf("\nYou return to the village.\n");
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