#ifndef MISSION_H
#define MISSION_H

#include <stdbool.h>
#include "dungeon_name.h"
#include "hero.h"

typedef enum
{
    NOT_STARTED,
    IN_PROGRESS,
    DONE
} MissionStatus;

typedef struct
{
    DUNGEON_NAME dungeon_name;
    MissionStatus status;
    char name[50];
    char objective[100];
    int objectives_completed;
    int objectives_required;
} Mission;

typedef struct
{
    Mission missions[4];
    int current_mission;
    int missions_completed;
    bool final_unlocked;
} MissionSystem;

void mission_init(MissionSystem *s);
int choose_mission(MissionSystem *s);
int mission_select(MissionSystem *s, int choice, Hero *h);
void mission_update_progress(MissionSystem *s, int add);

#endif