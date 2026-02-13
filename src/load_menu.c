#include <stdio.h>
#include <string.h>
#include "../include/load_menu.h"
#include "../include/save.h"
#include "../include/hero.h"
#include "../include/village_menu.h"
#include "../include/mission.h"
#include "../include/tools.h"

void load_menu(Hero* hero, MissionSystem *ms, int from_cheats)
{
    SaveList saves = load_saves();
    
    if(saves.count == 0)
    {
        printf("No saved games.\n");
        return;
    }
    printf("Saved Games:\n");
    for(int i = 0; i < saves.count; i++)
    {
        printf("%d. Save #%d | %s", i+1, saves.saves[i].save_idx, ctime(&saves.saves[i].timestamp));
    }
    
    int pick;
    printf("\nPick a game [1-%d]: ", saves.count);
    safe_scanf(&pick);
    
    if(pick < 1 || pick > saves.count)
    {
        printf("Wrong number.\n");
        return;
    }
    
    int save_num = saves.saves[pick-1].save_idx;
    

    int act;
    printf("\n1. Load\n");
    if (!from_cheats){
    printf("2. Delete\n");
    }
    printf("Choose: ");
    safe_scanf(&act);
    getchar();
    
    if(act == 1)
    {
        
        for(int i = 0; i < saves.count; i++)
        {
            if(saves.saves[i].save_idx == save_num)
            {
                *hero = saves.saves[i].hero;
                break;
            }
        }
        ms->missions_completed = hero->mission_completed[0]+hero->mission_completed[1]+hero->mission_completed[2];
        ms->final_unlocked = hero->final_mission_unlocked;
        ms->missions[0].status = hero->mission_completed[0] ? DONE : NOT_STARTED;
        ms->missions[1].status = hero->mission_completed[1] ? DONE : NOT_STARTED;
        ms->missions[2].status = hero->mission_completed[2] ? DONE : NOT_STARTED;
        ms->missions[3].status = hero->final_mission_unlocked ? DONE : NOT_STARTED;
        printf("Loading...\n");
        if (!from_cheats)
        {
            village_menu(hero,ms);
        }
    }
    else if(act == 2&&!from_cheats)
    {
        
        printf("Delete save? (yes/no): ");
        char ans[10];
        scanf("%s", ans);
        getchar();
        if(strcmp(ans, "yes") == 0 || strcmp(ans, "y") == 0)
        {
            delete_save(save_num);
            printf("Deleted.\n");
        }
        else
        {
            printf("Cancel.\n");
        }
        load_menu(hero,ms, from_cheats);
    }
    else
    {
        printf("Invalid.\n");
    }
}