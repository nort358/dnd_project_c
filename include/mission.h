#ifndef MISSION_H
#define MISSION_H
#include <stdbool.h>

typedef enum
{
    MISSION_NOT_STARTED,
    MISSION_IN_PROGRESS,
    MISSION_COMPLETED
} MissionStatus;

typedef enum
{
    MISSION_ROTTING_SWAMP = 1,
    MISSION_HAUNTED_MANSION = 2,
    MISSION_CRYSTAL_CAVE = 3,
    MISSION_DARK_LORD_CASTLE = 4
} MissionType;

typedef struct
{
    MissionType type;
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

void mission_init(MissionSystem *system);
void mission_display_menu(MissionSystem *system);
int mission_select(MissionSystem *system, int choice);
void mission_update_progress(MissionSystem *system, int progress);

#endif