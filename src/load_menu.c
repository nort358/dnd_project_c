#include <stdio.h>
#include <string.h>
#include "../include/load_menu.h"
#include "../include/save.h"
#include "../include/hero.h"
#include "../include/village_menu.h"

void load_menu(Hero* hero)
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
    scanf("%d", &pick);
    getchar();
    
    if(pick < 1 || pick > saves.count)
    {
        printf("Wrong number.\n");
        return;
    }
    
    int save_num = saves.saves[pick-1].save_idx;
    

    int act;
    printf("\n1. Load\n2. Delete\nChoose: ");
    scanf("%d", &act);
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
        printf("Loading...\n");
        village_menu(hero);
    }
    else if(act == 2)
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
        load_menu(hero);
    }
    else
    {
        printf("Invalid.\n");
    }
}