#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/village_menu.h"
#include "../include/hero.h"
#include "../include/mission.h"
#include "../include/save.h"
#include "../include/dungeon.h"
#include "../include/dungeon_name.h"

void shop_menu(Hero *h)
{
    int cho;
    while (1)
    {
        printf("\n=== SHOP ===\n");
        printf("Your coins: %d\n", h->coins);
        printf("1. Health Potion  -  4 coins\n");
        printf("2. Sword          -  5 coins\n");
        printf("3. Armor          - 10 coins\n");
        printf("4. Exit shop\n");
        printf("Choose: ");
        scanf("%d", &cho);
        getchar();

        switch (cho)
        {
        case 1:
            if (h->coins >= 4)
            {
                h->coins -= 4;
                h->health_potions++;
                printf("Bought Health Potion! You have %d now.\n", h->health_potions);
            }
            else
                printf("Not enough coins! (need 4)\n");
            break;
        case 2:
            if (h->sword)
                printf("You already have a Sword!\n");
            else if (h->coins >= 5)
            {
                h->coins -= 5;
                h->sword = 1;
                printf("Bought Sword! +1 attack now.\n");
            }
            else
                printf("Not enough coins! (need 5)\n");
            break;
        case 3:
            if (h->armor)
                printf("You already have Armor!\n");
            else if (h->coins >= 10)
            {
                h->coins -= 10;
                h->armor = 1;
                printf("Bought Armor! -1 damage taken.\n");
            }
            else
                printf("Not enough coins! (need 10)\n");
            break;
        case 4:
            printf("Leaving shop...\n");
            return;
        default:
            printf("Invalid choice.\n");
        }
    }
}

// COMBAT
int fight_enemy(Hero *h, Room *r)
{
    printf("\n--- FIGHT! ---\n");
    printf("Enemy: %d (need %d+ to hit)\n", r->name, r->fatal_strike);

    while (h->life_points > 0)
    {
        int att = rand() % 6 + 1;
        if (h->sword)
            att += 1;

        printf("You roll %d", att - (h->sword ? 1 : 0));
        if (h->sword)
            printf(" +1 sword = %d", att);
        printf("\n");

        if (att >= r->fatal_strike)
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

//  FINAL BOSS – rock paper scissors
int final_boss_fight(Hero *hero)
{
    printf("\n");
    printf("     DARK LORD CASTLE - FINAL BOSS\n");
    printf("You face the Dark Lord! Best of 5 rounds.\n");
    printf("Shield beats Sword, Sword beats Magic, Magic beats Shield.\n");
    printf("Press Enter to start...");
    getchar();
    getchar();

    int h_score = 0;
    int b_score = 0;
    int rnd = 1;

    while (h_score < 3 && b_score < 3 && rnd <= 5)
    {
        printf("\n--- Round %d ---\n", rnd);
        printf("You: %d  |  Dark Lord: %d\n", h_score, b_score);
        printf("1. Shield\n2. Magic\n3. Sword\n");
        printf("Your move: ");
        int hm;
        scanf("%d", &hm);
        getchar();

        if (hm < 1 || hm > 3)
        {
            printf("Wrong move! You lose the round.\n");
            b_score++;
            rnd++;
            continue;
        }

        int bm = rand() % 3 + 1;

        printf("You chose: ");
        if (hm == 1)
            printf("Shield\n");
        else if (hm == 2)
            printf("Magic\n");
        else
            printf("Sword\n");

        printf("Dark Lord chose: ");
        if (bm == 1)
            printf("Shield\n");
        else if (bm == 2)
            printf("Magic\n");
        else
            printf("Sword\n");

        if (hm == bm)
        {
            printf("No winner.\n");
        }
        else if ((hm == 1 && bm == 3) ||
                 (hm == 2 && bm == 1) ||
                 (hm == 3 && bm == 2))
        {
            printf(" YOU WIN THE ROUND! \n");
            h_score++;
        }
        else
        {
            printf(" DARK LORD WINS THE ROUND!\n");
            b_score++;
        }
        rnd++;
    }

    if (h_score >= 3)
    {
        printf("🎉 YOU DEFEATED THE DARK LORD! :)🎉\n");
        printf("The kingdom is saved!\n");
        hero->third_mission_completed = 1; // final mission done
        return 1;
    }
    else
    {
        printf("💀 The Dark Lord defeated you :(( ... GAME OVER 💀\n");
        return 0;
    }
}

//  VILLAGE MENU
void village_menu(Hero *hero)
{
    int act;
    char inp[100];

    while (1)
    {
        printf("\n");
        printf("***************\n");
        printf("VILLAGE SCREEN\n");
        printf("***************\n");
        printf("Hero: %d HP | Money: %d\n", hero->life_points, hero->coins);
        printf("***************\n");
        printf("1. GO ON MISSION\n");
        printf("2. SLEEP Zzz ( you cam get HP back to 20)\n");
        printf("3. SEE MY STUFF\n");
        printf("4. KEEP GAME\n");
        printf("5. BACK TO START\n");
        printf("***************\n");
        printf("Type 1 to 5: ");

        if (fgets(inp, sizeof(inp), stdin))
        {
            inp[strcspn(inp, "\n")] = 0;
            act = atoi(inp);

            switch (act)
            {
            case 1:
            {
                MissionSystem ms;
                mission_init(&ms);
                mission_display_menu(&ms);

                int pick;
                scanf("%d", &pick);

                int midx = mission_select(&ms, pick, hero);
                if (midx >= 0)
                {
                    // FINAL MISSION
                    if (pick == 4)
                    {
                        printf("\n=== FINAL MISSION: DARK LORD CASTLE ===\n");
                        int win = final_boss_fight(hero);
                        if (win)
                        {
                            printf("Congratulations! You won the game!\n");
                            return;
                        }
                        else
                        {
                            printf("You were defeated... Returning to main menu.\n");
                            return;
                        }
                    }

                    // NORMAL MISSIONS (1,2,3)
                    printf("\n=== ENTERING DUNGEON ===\n");
                    Dungeon d;
                    if (pick == 1)
                        d = generate_dungeon(hero, ROTTING_SWAMP);
                    else if (pick == 2)
                        d = generate_dungeon(hero, HAUNTED_MANSION);
                    else if (pick == 3)
                        d = generate_dungeon(hero, CRYSTAL_CAVE);

                    printf("Dungeon has 10 rooms.\n\n");

                    // SHOP before fighting
                    shop_menu(hero);

                    // mission counters
                    int gen_kill = 0;
                    int vamp_kill = 0;
                    int key_get = 0;

                    for (int i = 0; i < 10; i++)
                    {
                        printf("--- Room %d/%d ---\n", i + 1, 10);
                        printf("You see: %d\n", d.rooms[i].name);

                        // EMPTY
                        if (d.rooms[i].type == 0)
                        {
                            printf("Nothing here.\n");
                        }
                        // ENEMY
                        else if (d.rooms[i].type == 1)
                        {
                            int w = fight_enemy(hero, &d.rooms[i]);
                            if (w == 0)
                            {
                                printf("\nReturning to main menu...\n");
                                return;
                            }

                            // Rotting Swamp
                            if (d.rooms[i].name == ORC_GENERAL)
                            {
                                gen_kill++;
                                printf("Orc Generals: %d/3\n", gen_kill);
                                if (gen_kill >= 3)
                                {
                                    printf("\n*** ROTTING SWAMP COMPLETE! ***\n");
                                    hero->first_mission_completed = 1;
                                    mission_update_progress(&ms, 1);
                                    break;
                                }
                            }

                            // Haunted Mansion
                            if (d.rooms[i].name == GREAT_VAMPHIRE)
                            {
                                vamp_kill = 1;
                                printf("Greater Vampire killed! 1/2\n");
                                mission_update_progress(&ms, 1);
                            }
                            if (d.rooms[i].name == GURDIAN_DEMON)
                            {
                                key_get = 1;
                                printf("Guardian Demon killed! Got the key! 1/2\n");
                                mission_update_progress(&ms, 1);
                            }

                            if (pick == 2 && vamp_kill && key_get)
                            {
                                printf("\n*** HAUNTED MANSION COMPLETE! ***\n");
                                hero->second_mission_completed = 1;
                                break;
                            }
                        }
                        // TRAP
                        else if (d.rooms[i].type == 2)
                        {
                            int dmg = d.rooms[i].damage;
                            if (d.rooms[i].damage == 0)
                                dmg = rand() % 6 + 1;
                            hero->life_points -= dmg;
                            printf("TRAP! -%d HP (HP now %d)\n", dmg, hero->life_points);
                            if (hero->life_points <= 0)
                            {
                                printf("\n*** GAME OVER ***\n");
                                return;
                            }
                        }

                        printf("\nPress Enter...");
                        getchar();
                        getchar();
                    }
                    printf("\nYou return to the village.\n");
                }
                break;
            }

            case 2:
                printf("\nZzz... HP restored to 20!\n");
                hero->life_points = 20;
                break;

            case 3:
                printf("\nMY STUFF\n");
                printf("HP: %d\n", hero->life_points);
                printf("Money: %d\n", hero->coins);
                printf("Sword: %s\n", hero->sword ? "YES" : "NO");
                printf("Armor: %s\n", hero->armor ? "YES" : "NO");
                printf("Health potions: %d\n", hero->health_potions);
                printf("Missions done: %d/3\n",
                       (hero->first_mission_completed +
                        hero->second_mission_completed +
                        hero->third_mission_completed));
                break;

            case 4:
                save_game(hero);
                break;

            case 5:
                printf("Bye Bye:)! Back to main menu.\n");
                return;

            case 9: // cheat
                hero->coins += 1000;
                hero->first_mission_completed = 1;
                hero->second_mission_completed = 1;
                printf("\nCHEAT! +1000 coins, first 2 missions done.\n");
                break;

            default:
                printf("Wrong input! 1-5 only!!.\n");
            }
        }

        printf("\nPress ENTER to continue...");
        getchar();
    }
}