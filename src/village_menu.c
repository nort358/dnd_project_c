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
#include "../include/dice.h"
#include "../include/sword.h"
#include "../include/rps.h"
#include "../include/tools.h"
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
        safe_scanf(&c);

        if (c == 1 && h->coins >= 4)
        {
            h->coins -= 4;
            int additional_hp = roll_dice();
            
            if (h->life_points>HERO_MAX_LIFE_POINTS)
            {
                printf("CHEATER IS CAUGHT. YOUR HP IS 1 NOW. YOU ARE FEELING LIKE YOU ARE PRESENTING A PROJECT TO YOUR PROFESSOR\n");
                h->life_points = 1;
                continue;
            }
            else{
                if(additional_hp==1){
                printf("OHH THE POITION IS VERY BAD. IT RESTORES ONLY 1 HP. YOU ARE SO DEPREESED NOW\n");
            }
            else if (additional_hp==6){
                printf("WOW THE POITION IS VERY VERY COOOL. IT RESTORES 6 HP. YOU START FLEEXING NEAR THE MERCHANT\n");
            }
            else {
                printf("THE POITION RESTORES %d HP. NOT BAD\n", additional_hp);
            }
            if (h->life_points + additional_hp > HERO_MAX_LIFE_POINTS)
                h->life_points = HERO_MAX_LIFE_POINTS;
            else{
                h->life_points += additional_hp;
            }  
            }
                      
            printf("Health restored, now %d\n", h->life_points);
        }
        else if (c == 2 && !h->sword && h->coins >= 5)
        {
            h->coins -= 5;
            Hero_equip_sword(h);
        }
        else if (c == 3 && !h->armor && h->coins >= 10)
        {
            h->coins -= 10;
            Hero_equip_armor(h);
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
    printf("\nThe hero encounters a %s and the fight begins.\n", DUNGEON_TO_NAME[r->name]);

    while (h->life_points > 0)
    {
        printf("\nA dice is rolled to determine the hero's attack\n");

        int dice = roll_dice();
        int attack = dice;
        if (h->sword)
            attack++;

        printf("The result: %d.\n", dice);

        if (attack > r->fatal_strike)
        {
            printf("Attack enough to defeat the %s (%d > Fatal Strike=%d).\n",
                   DUNGEON_TO_NAME[r->name], attack, r->fatal_strike);
            printf("The %s is defeated. ", DUNGEON_TO_NAME[r->name]);
            printf("The hero remains with %d life points, and receives %d coins.\n",
                   h->life_points, r->reward_coins);
            h->coins += r->reward_coins;
            return 1; // victory
        }
        else
        {
            printf("Attack not enough to defeat the %s (%d < Fatal Strike=%d).\n",
                   DUNGEON_TO_NAME[r->name], attack, r->fatal_strike);

            int damage = r->damage;
            if (h->armor)
                damage--;
            if (damage < 1)
                damage = 1;

            printf("The %s deals %d damage to the hero. ", DUNGEON_TO_NAME[r->name], damage);
            h->life_points -= damage;
            printf("The hero remains with %d life points.\n", h->life_points);

            if (h->life_points <= 0)
            {
                printf("\n*** GAME OVER ***\n");
                printf("You have been defeated!\n");
                return 0;
            }
        }
    }
    return 0;
}



int fight_dragon(Hero *h, Room *r)
{
    printf("\nThe hero encounters a %s and the fight begins.\n", DUNGEON_TO_NAME[r->name]);

    while (h->life_points > 0)
    {
        printf("\nA dice is rolled to determine the hero's attack\n");

        int dice = roll_dice();
        int attack = dice;
        if (h->sword)
            attack++;

        printf("The result: %d.\n", dice);

        if (attack > r->fatal_strike)
        {
            printf("Attack enough to defeat the %s (%d > Fatal Strike=%d).\n",
                   DUNGEON_TO_NAME[r->name], attack, r->fatal_strike);
            printf("The %s is defeated. ", DUNGEON_TO_NAME[r->name]);
            printf("The hero remains with %d life points, and receives %d coins.\n",
                   h->life_points, r->reward_coins);
            h->coins += r->reward_coins;
            return 1; // victory
        }
        else
        {
            printf("Attack not enough to defeat the %s (%d < Fatal Strike=%d).\n",
                   DUNGEON_TO_NAME[r->name], attack, r->fatal_strike);

            int damage = r->damage;
            if (h->armor)
                damage--;
            if (damage <0)
                damage = 0;

            int num = rand_int(1,500);
            printf("\nThe Dragon asks you: Is %d a Padovan number? (y/n): ", num);

            char ans[10];
            fgets(ans, 10, stdin);
            ans[strcspn(ans, "\n")] = 0;

            int is_pad = isPadovan(num);

            if ((ans[0] == 'y' || ans[0] == 'Y') && is_pad)
            {
                printf("Correct! The dragon spares you. No damage this round.\n");
                continue;
                }
            else if ((ans[0] == 'n' || ans[0] == 'N') && !is_pad)
            {
                printf("Correct! The dragon spares you. No damage this round.\n");
                continue;
            }
            else
            {
                printf("Wrong answer! The dragon attacks with full force!\n");
            }

            printf("The %s deals %d damage to the hero. ", DUNGEON_TO_NAME[r->name], damage);
            h->life_points -= damage;
            printf("The hero remains with %d life points.\n", h->life_points);

            if (h->life_points <= 0)
            {
                printf("\n*** GAME OVER ***\n");
                printf("You have been defeated!\n");
                return 0;
            }
        }
    }
    return 0;
}
// final boss
int final_boss_fight()
{
    printf("\n----DARK LORD----\n");
    printf("Rock Paper Scissors, best of 5\n");
    printf("1=Shield 2=Magic 3=Sword\n");
    printf("Enter to start...");
    getchar();

    int p = 0, d = 0, r = 1;
    while (p < 3 && d < 3 && r <= 6)
    {
        printf("\nRound %d: You %d VS Dark %d\n", r, p, d);
        printf("Your move: ");
        int m;
        safe_scanf(&m);
        if (m < 1 || m > 3)
        {
            printf("invalid, you lose round\n");
            d++;
            r++;
            continue;
        }
        int bm = rand_int(1, 3);
        switch (m-1)
        {
        case SHIELD:
            switch (bm-1)
            {
            case SHIELD:
                printf("BOTH OF YOU JUST TRYED TO PROTECT, HOW BORING\n");
                break;
            case MAGIC:
                printf("YOU ARE TRYING TO BLOCK MAGIC WITH A SHIELD! UNFORUNATELY IT DOES NOT WORK AND YOU ARE DAMAGED!\n");
                d++;
                break;
            case SWORD:
                printf("YOU BLOCK THE SWORD WITH YOUR SHIELD AND COUNTERATTACK HIM! NICE!\n");
                p++;
                break;
            default:
                break;
            }
            break;
        
        case MAGIC:
            switch (bm-1)
            {
            case SHIELD:
                printf("THE STUPID DARK LORD TRYING TO PROTECT HIMSELF WITH A SHIELD! BUT IT CANT PROTECT HIM FROM YOUR MAGIC POWER! NICE!\n");
                p++;
                break;
            case MAGIC:
                printf("BOTH OF YOU CAST MAGIC! BUT YOURS MAGIC POWER ARE SAME!HOW BORING!\n");
                break;
            case SWORD:
                printf("YOU CAST MAGIC WHILE THE DARK LORD ATTACK YOU WITH A SWORD! HE IS STRONGER AND YOU ARE DAMAGED!\n");
                d++;
                break;
            default:
                break;
            }
            break;
        case SWORD:
            switch (bm-1)
            {
            case SHIELD:
                printf("YOU ARE TRYING TO ATTACK THE DARK LORD WITH A SWORD WHILE HE IS PROTECTING HIMSELF WITH A SHIELD! HE BLOCKS AND COUNTERATTACK YOU!\n");
                d++;
                break;
            case MAGIC:
                printf("YOU CAST SWORD WHILE THE DARK LORD CAST MAGIC! YOUR ARE STRONGER THAN HIS MAGIC POWER!\n");
                p++;
                break;
            case SWORD:
                printf("BOTH OF YOU TRY TO ATACK EACH OTHER WITH A SWORD!BUT AFTER A HOURS OF FIGHTS YOU BOTH ARE TIRED!HOW BORING!\n");
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
    if (p >= 3)
    {
        printf("\nYOU CAST MAGIC, THEN ATTACK HIM WITH A SWORD AND PUT SHIELD ON HIS BLOODY HEAD\n");
        printf("YOU WIN! Dark Lord dead\n");
        return 1;
    }
    r++;
}
    printf("\nDark Lord CAST MAGIC, THEN HE ATTACK YOU WITH A SWORD AND PUT HIS SHIELD ON YOUR BLOODY HEAD\n");
    printf("YOU LOSE... GAME OVER\n");
    return 0;
    
}

// village menu
void village_menu(Hero *hero, MissionSystem *ms)
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
            int pick=choose_mission(ms);
            if (pick < 0) continue;
            int m = mission_select(ms, pick, hero);
            if (m >= 0)
            {
                if (pick == 3) // final
                {
                    printf("\nFINAL MISSION\n");
                    if (final_boss_fight())
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
                d = generate_dungeon(hero, pick);

                printf("10 rooms\n\n");
                int current_room = 0;
                int gen = 0, vamp = 0, key = 0;
                int mission_active = 1;

                while (mission_active && current_room < 10)
                {
                    printf("\n=== MISSION MENU ===\n");
                    printf("1. Explore Dungeon Room (Room %d/10)\n", current_room + 1);
                    printf("2. Shop\n");
                    printf("3. Inventory\n");
                    printf("4. Return to Village\n");
                    printf("Choose [1-4]: ");

                    int menu_choice;
                    safe_scanf(&menu_choice);

                    if (menu_choice == 1) // Explore
                    {
                        printf("\n-- Room %d/10 --\n", current_room + 1);
                        printf("see: %s\n", DUNGEON_TO_NAME[d.rooms[current_room].name]);

                        // Handle room based on type
                        if (d.rooms[current_room].type == 0) // Empty
                        {
                            printf("empty\n");
                        }
                        else if (d.rooms[current_room].type == 1) // Enemy
                        {
                            // Padovan question for Ancient Dragon
                            int w;
                            if (d.rooms[current_room].name == ANCIENT_DRAGON)
                            {
                                w=fight_dragon(hero, &d.rooms[current_room]);
                            }else{
                                w=fight_enemy(hero, &d.rooms[current_room]);
                            }

                            if (w == 0)
                            {
                                printf("\nback to main\n");
                                return;
                            }

                            // Track mission progress
                            if (d.rooms[current_room].name == ORC_GENERAL)
                            {
                                if (gen<3){
                                mission_update_progress(ms, 1);
                                gen++;
                                printf("Orc generals %d/3\n", gen);
                            }
                                if (gen == 3)
                                {
                                    if (!(hero->mission_completed[pick])) {
                                    printf("*** ROTTING SWAMP DONE ***\n");
                                    Hero_complete_mission(hero, pick);
                                    }
                                }
                            }
                            if (d.rooms[current_room].name == ANCIENT_DRAGON)
                            {
                                if(!(hero->mission_completed[pick])){
                                Hero_equip_hero_sword(hero);
                                mission_update_progress(ms, 1);
                                printf("Ancient Dragon killed\n");
                                printf("CRYSTAL CAVE DONE\n");
                                Hero_complete_mission(hero, pick);
                                }
                            }
                            if (d.rooms[current_room].name == GREAT_VAMPHIRE)
                            {
                                if (vamp==0){
                                vamp++;
                                printf("Vampire killed \n");
                                mission_update_progress(ms, 1);
                                }
                            }
                            if (d.rooms[current_room].name == GURDIAN_DEMON)
                            {
                                if (key==0){
                                key = 1;
                                printf("Key got\n");
                                mission_update_progress(ms, 1);
                            }
                            }
                            if (pick == HAUNTED_MANSION && vamp >= 1 && key)
                            {
                                if (!(hero->mission_completed[HAUNTED_MANSION])) {
                                printf("*** HAUNTED MANSION DONE ***\n");
                                Hero_complete_mission(hero, pick);
                            }
                            }
                        }
                        else if (d.rooms[current_room].type == 2) // Trap
                        {
                            int dmg = d.rooms[current_room].damage;
                            if (dmg == 0)
                                dmg = roll_dice();
                            hero->life_points -= dmg;
                            printf("trap -%d HP (now %d)\n", dmg, hero->life_points);
                            if (hero->life_points <= 0)
                            {
                                printf("*** GAME OVER ***\n");
                                return;
                            }
                        }

                        current_room++; // Move to next room
                        printf("Press Enter...");
                        getchar();
                    }
                    else if (menu_choice == 2) // Shop
                    {
                        shop_menu(hero);
                    }
                    else if (menu_choice == 3) // Inventory
                    {
                        printf("\nHP: %d\nCoins:%d\n", hero->life_points, hero->coins);
                        printf("Sword: %s\n", hero->sword ? "Y" : "N");
                        printf("Armor: %s\n", hero->armor ? "Y" : "N");
                    }
                    else if (menu_choice == 4) // Return to Village
                    {
                        // Check if mission is complete
                        if (
                            (hero->mission_completed[pick]))
                        {
                            printf("Mission complete! Returning to village.\n");
                            mission_active = 0;
                        }
                        else
                        {
                            printf("Mission not complete! Pay 50 coins? (y/n): ");
                            char ans[10];
                            fgets(ans, 10, stdin);
                            ans[strcspn(ans, "\n")] = 0;

                            if ((ans[0] == 'y' || ans[0] == 'Y') && hero->coins >= 50)
                            {
                                hero->coins -= 50;
                                printf("Paid 50 coins. Returning to village.\n");
                                mission_active = 0;
                            }
                            else if (hero->coins < 50)
                            {
                                printf("Not enough coins! You need 50!\n");
                            }
                            else
                            {
                                printf("Staying in dungeon.\n");
                            }
                        }
                    }
                    else
                    {
                        printf("Invalid choice! Choose 1-4.\n");
                    }
                }

                printf("\nback to village\n");
            }
            break;
        }

        case 2:
            hero->life_points = HERO_MAX_LIFE_POINTS;
            printf("HP restored to %d\n", HERO_MAX_LIFE_POINTS);
            break;
        case 3:
            printf("\nHP: %d\nCoins:%d\n", hero->life_points, hero->coins);
            printf("Sword: %s\n", SWORDS[hero->sword]);
            printf("Armor: %s\n", hero->armor ? "Y" : "N");
            printf("Missions: %d/3\n", hero->mission_completed[0] + hero->mission_completed[1] + hero->mission_completed[2]);
            break;
        case 4:
            save_game(hero);
            break;
        case 5:
            printf("bye bye :)\n");
            return;
        // case 9:
        //     hero->coins += 1000;
        //     Hero_complete_mission(hero, 0);
        //     Hero_complete_mission(hero, 1);
        //     printf("cheat +1000 coins, missions 1&2 done\n");
        //     break;
        default:
            printf("wrong input!!\n");
        }
        printf("Press Enter...");
        getchar();
    }
    printf("\nback to village\n");
}