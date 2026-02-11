#ifndef MISSION_H
#define MISSION_H

#include <stdbool.h>
#include "dungeon_name.h"
#include "hero.h"

typedef enum
{
    MISSION_NOT_STARTED,
    MISSION_IN_PROGRESS,
    MISSION_COMPLETED
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
} MissionSystem; // <-- MissionSystem is now defined here

// Function prototypes – ALL placed AFTER the struct definition
void mission_init(MissionSystem *system);
void mission_display_menu(MissionSystem *system);
int mission_select(MissionSystem *system, int choice, Hero *hero); // <-- 3 parameters!
void mission_update_progress(MissionSystem *system, int progress);
void mission_inside_menu(MissionSystem *system, Hero *hero); // if you use it

#endif