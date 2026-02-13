#include "mission.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/tools.h"

void mission_init(MissionSystem *s)
{
    s->missions[0].dungeon_name = ROTTING_SWAMP;
    s->missions[0].status = 0;
    strcpy(s->missions[0].name, "Rotting Swamp");
    strcpy(s->missions[0].objective, "Kill 3 Orc Generals");
    s->missions[0].objectives_completed = 0;
    s->missions[0].objectives_required = 3;

    s->missions[1].dungeon_name = HAUNTED_MANSION;
    s->missions[1].status = 0;
    strcpy(s->missions[1].name, "Haunted Mansion");
    strcpy(s->missions[1].objective, "Get key and kill Vampire");
    s->missions[1].objectives_completed = 0;
    s->missions[1].objectives_required = 2;

    s->missions[2].dungeon_name = CRYSTAL_CAVE;
    s->missions[2].status = 0;
    strcpy(s->missions[2].name, "Crystal Cave");
    strcpy(s->missions[2].objective, "Find Hero's Sword");
    s->missions[2].objectives_completed = 0;
    s->missions[2].objectives_required = 1;

    s->missions[3].dungeon_name = DARK_LORD_CASTLE;
    s->missions[3].status = 0;
    strcpy(s->missions[3].name, "Dark Lord Castle");
    strcpy(s->missions[3].objective, "Beat the Dark Lord");
    s->missions[3].objectives_completed = 0;
    s->missions[3].objectives_required = 1;

    s->current_mission = -1;
    s->missions_completed = 0;
    s->final_unlocked = 0;
}

int choose_mission(MissionSystem *s)
{
    printf("\n=== MISSIONS ===\n");

    int map[4];
    int shown = 0;

    for (int i = 0; i < 3; i++) {
        if (s->missions[i].status == DONE) continue;

        map[shown] = i;
        printf("%d. %s\n", shown + 1, s->missions[i].name);
        printf("   %s\n\n", s->missions[i].objective);
        shown++;
    }
    if (s->final_unlocked) {
        map[shown] = 3;
        printf("%d. %s\n", shown + 1, s->missions[3].name);
        printf("   %s\n", s->missions[3].objective);
        printf("   He is waiting you\n");
        shown++;
    }
    printf("\n0. Back\nPick [0-%d]: ", shown);

    int pick;
    safe_scanf(&pick);
    if ((pick == 0)||(pick==-1)) return -1;
    if (pick < 1 || pick > shown) {
        printf("Invalid choice!\n");
        return -1;
    }

    return map[pick - 1];
}


int mission_select(MissionSystem *s, int ch, Hero *h)
{
    (void)h;
    if(ch<0||ch>4) { printf("Wrong\n"); return -1; }
    int idx = ch;
    if(idx==3 && !s->final_unlocked) { printf("Do 3 first\n"); return -1; }
    s->missions[idx].status = 1;
    s->current_mission = idx;
    printf("\n--- %s ---\n", s->missions[idx].name);
    printf("Goal: %s\n", s->missions[idx].objective);
    return idx;
}

void mission_update_progress(MissionSystem *s, int add)
{
    int n = s->current_mission;
    if(n<0) return;
    s->missions[n].objectives_completed += add;
    printf("Progress: %d/%d\n", s->missions[n].objectives_completed, s->missions[n].objectives_required);
    if(s->missions[n].objectives_completed >= s->missions[n].objectives_required)
    {
        s->missions[n].status = DONE;
        s->missions_completed++;
        s->current_mission = -1;
        printf("\n*** MISSION DONE! ***\n");
        if(n<3 && s->missions_completed >= 3)
        {
            s->final_unlocked = 1;
            printf("Final boss unlocked!\n");
        }
    }
}