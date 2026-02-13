#include "hero.h"
#include "mission.h"
#include "cheats.h"
#include "load_menu.h"
#include "tools.h"
#include <stdio.h>
#include <village_menu.h>
void cheat_menu(Hero* hero, MissionSystem* ms){

    printf("FIRSTLY LOAD SAVE:\n");
    load_menu(hero, ms, 1);
    while (1){
        printf("1. ADD LIFE POINTS\n");
        printf("2. ADD COINS\n");
        printf("3. UNLOCK LAST BOSS\n");
        printf("4. GO TO VILLAGE WITH UPDATED STATS\n");
        printf("5. EXIT\n");
        
        int choice;
        printf("Choose: ");

        safe_scanf(&choice);

        switch (choice){
            case 1:
                printf("Enter amount of life points to add: ");
                int hp;
                safe_scanf(&hp);
                Hero_life_points_change(hero, hp);
                break;
            case 2:
                printf("Enter amount of coins to add: ");
                int coins;
                safe_scanf(&coins);
                Hero_coins_change(hero, coins);
                break;
            case 3:
                ms->final_unlocked=1;
                ms->missions[0].status = DONE;
                ms->missions[1].status = DONE;
                ms->missions[2].status = DONE;
                hero->final_mission_unlocked=1;
                hero->mission_completed[0]=1;
                hero->mission_completed[1]=1;
                hero->mission_completed[2]=1;
                printf("Last boss unlocked!\n");
                break;
            case 4:
                village_menu(hero, ms);
                return;
            case 5:
                return;
            default:
                printf("Invalid choice!\n");
    }
    }
};
