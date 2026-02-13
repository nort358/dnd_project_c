#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/village_menu.h"
#include "../include/hero.h"
#include "../include/mission.h"
#include "../include/save.h"
#include "../include/dungeon.h"
#include "../include/dungeon_name.h"
#include "../include/padovan.h"

// shop
void shop_menu(Hero *h)
{
    int c;
    while (1)
    {
        printf("\n=== SHOP ===\n");
        printf("Coins: %d\n", h->coins);
        printf("1. Potion (4)  +1-6 HP\n");
        printf("2. Sword (5)  +1 att\n");
        printf("3. Armor (10) -1 dmg\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &c);
        getchar();

        if (c == 1 && h->coins >= 4)
        {
            h->coins -= 4;
            h->health_potions++;
            printf("Got potion! now %d\n", h->health_potions);
        }
        else if (c == 2 && !h->sword && h->coins >= 5)
        {
            h->coins -= 5;
            h->sword = 1;
            printf("Got sword! +1 attack\n");
        }
        else if (c == 3 && !h->armor && h->coins >= 10)
        {
            h->coins -= 10;
            h->armor = 1;
            printf("Got armor! -1 damage\n");
        }
        else if (c == 4)
        {
            printf("bye\n");
            return;
        }
        else
            printf("cant buy\n");
    }
}

// fight
int fight_enemy(Hero *h, Room *r)
{
    printf("\n--- FIGHT ---\n");
    printf("The hero encounters %s and the fight begins .\n", DUNGEON_TO_NAME[r->name]);
    while (h->life_points > 0)
    {
        int a = rand() % 6 + 1;
        if (h->sword)
            a++;
        printf("roll %d", a - (h->sword ? 1 : 0));
        if (h->sword)
            printf("+1 = %d", a);
        printf("\n");
        if (a >= r->fatal_strike)
        {
            printf("VICTORY!\n");
            h->coins += r->reward_coins;
            printf("+%d coins (now %d)\n", r->reward_coins, h->coins);
            return 1;
        }
        else
        {
            int d = r->damage;
            if (h->armor)
                d--;
            if (d < 1)
                d = 1;
            h->life_points -= d;
            printf("hit -%d HP (left %d)\n", d, h->life_points);
            if (h->life_points <= 0)
            {
                printf("GAME OVER\n");
                return 0;
            }
        }
    }
    return 0;
}

// final boss
int final_boss_fight(Hero *h)
{
    printf("\n----DARK LORD----\n");
    printf("Rock Paper Scissors, best of 5\n");
    printf("1=Shield 2=Magic 3=Sword\n");
    printf("Enter to start...");
    getchar();
    getchar();

    int p = 0, d = 0, r = 1;
    while (p < 3 && d < 3 && r <= 5)
    {
        printf("\nRound %d: You %d - Dark %d\n", r, p, d);
        printf("Your move: ");
        int m;
        scanf("%d", &m);
        getchar();
        if (m < 1 || m > 3)
        {
            printf("invalid, you lose round\n");
            d++;
            r++;
            continue;
        }
        int bm = rand() % 3 + 1;
        printf("You: %d, Dark: %d\n", m, bm);
        if (m == bm)
            printf("tie\n");
        else if ((m == 1 && bm == 3) || (m == 2 && bm == 1) || (m == 3 && bm == 2))
        {
            printf("you win round\n");
            p++;
        }
        else
        {
            printf("dark wins round\n");
            d++;
        }
        r++;
    }
    if (p >= 3)
    {
        printf("YOU WIN! Dark Lord dead\n");
        h->third_mission_completed = 1;
        return 1;
    }
    else
    {
        printf("YOU LOSE... GAME OVER\n");
        return 0;
    }
}

// village menu
void village_menu(Hero *hero)
{
    int act;
    char buf[100];
    while (1)
    {

        printf("***************\n");
        printf("VILLAGE\n");
        printf("***************\n");
        printf("HP:%d Coins:%d\n\n", hero->life_points, hero->coins);
        printf("1. Start a mission\n");
        printf("2. Rest\n");
        printf("3. Inventory\n");
        printf("4. Save\n");
        printf("5. Exit\n");
        printf("\n> ");
        fgets(buf, sizeof(buf), stdin);
        buf[strcspn(buf, "\n")] = 0;
        act = atoi(buf);

        switch (act)
        {
        case 1:
        {
            MissionSystem ms;
            mission_init(&ms);
            mission_display_menu(&ms);

            int pick;
            scanf("%d", &pick);
            getchar();

            int m = mission_select(&ms, pick, hero);
            if (m >= 0)
            {
                if (pick == 4) // final
                {
                    printf("\nFINAL MISSION\n");
                    if (final_boss_fight(hero))
                    {
                        printf("You won! congrats!\n");
                        return;
                    }
                    else
                    {
                        printf("You died... back to menu\n");
                        return;
                    }
                }

                printf("\n=== DUNGEON ===\n");
                Dungeon d;
                if (pick == 1)
                    d = generate_dungeon(hero, ROTTING_SWAMP);
                else if (pick == 2)
                    d = generate_dungeon(hero, HAUNTED_MANSION);
                else
                    d = generate_dungeon(hero, CRYSTAL_CAVE);

                printf("10 rooms\n\n");
                shop_menu(hero);

                int gen = 0, vamp = 0, key = 0;

                for (int i = 0; i < 10; i++)
                {
                    printf("-- Room %d/10 --\n", i + 1);
                    printf("see: %s\n", DUNGEON_TO_NAME[d.rooms[i].name]);

                    if (d.rooms[i].type == 0)
                        printf("empty\n");
                    else if (d.rooms[i].type == 1)
                    {
                        if (d.rooms[i].name == ANCIENT_DRAGON)
                        {
                            int num = rand() % 500 + 1;
                            printf("\nThe Dragon asks you: Is %d a Padovan number? (y/n): ", num);

                            char ans[10];
                            fgets(ans, 10, stdin);
                            ans[strcspn(ans, "\n")] = 0;

                            int is_pad = isPadovan(num);

                            if ((ans[0] == 'y' || ans[0] == 'Y') && is_pad)
                            {
                                printf("Correct! The dragon spares you. No damage this round.\n");
                                d.rooms[i].damage = 0;
                            }
                            else if ((ans[0] == 'n' || ans[0] == 'N') && !is_pad)
                            {
                                printf("Correct! The dragon spares you. No damage this round.\n");
                                d.rooms[i].damage = 0;
                            }
                            else
                            {
                                printf("Wrong answer! The dragon attacks with full force!\n");
                            }
                        }
                        int w = fight_enemy(hero, &d.rooms[i]);
                        if (w == 0)
                        {
                            printf("\nback to main\n");
                            return;
                        }

                        if (d.rooms[i].name == ORC_GENERAL)
                        {
                            gen++;
                            printf("Orc generals %d/3\n", gen);
                            if (gen >= 3)
                            {
                                printf("*** ROTTING SWAMP DONE ***\n");
                                hero->first_mission_completed = 1;
                                mission_update_progress(&ms, 1);
                                break;
                            }
                        }
                        if (d.rooms[i].name == GREAT_VAMPHIRE)
                        {
                            vamp = 1;
                            printf("Vampire killed (1/2)\n");
                            mission_update_progress(&ms, 1);
                        }
                        if (d.rooms[i].name == GURDIAN_DEMON)
                        {
                            key = 1;
                            printf("Key got (1/2)\n");
                            mission_update_progress(&ms, 1);
                        }
                        if (pick == 2 && vamp && key)
                        {
                            printf("*** HAUNTED MANSION DONE ***\n");
                            hero->second_mission_completed = 1;
                            break;
                        }
                    }
                    else if (d.rooms[i].type == 2)
                    {
                        int dmg = d.rooms[i].damage;
                        if (dmg == 0)
                            dmg = rand() % 6 + 1;
                        hero->life_points -= dmg;
                        printf("trap -%d HP (now %d)\n", dmg, hero->life_points);
                        if (hero->life_points <= 0)
                        {
                            printf("*** GAME OVER ***\n");
                            return;
                        }
                    }

                    printf("Press Enter...");
                    getchar();
                    getchar();
                }
                printf("\nback to village\n");
            }
            break;
        }

        case 2:
            hero->life_points = 20;
            printf("HP 20\n");
            break;
        case 3:
            printf("\nHP:%d\nCoins:%d\n", hero->life_points, hero->coins);
            printf("Sword:%s\n", hero->sword ? "Y" : "N");
            printf("Armor:%s\n", hero->armor ? "Y" : "N");
            printf("Potions:%d\n", hero->health_potions);
            printf("Missions:%d/3\n", hero->first_mission_completed + hero->second_mission_completed + hero->third_mission_completed);
            break;
        case 4:
            save_game(hero);
            break;
        case 5:
            printf("bye\n");
            return;
        case 9:
            hero->coins += 1000;
            hero->first_mission_completed = 1;
            hero->second_mission_completed = 1;
            printf("cheat +1000 coins, missions 1&2 done\n");
            break;
        default:
            printf("wrong input!!\n");
        }
        printf("Press Enter...");
        getchar();
    }
    printf("\nback to village\n");
}