#ifndef DUNGEON_H
#define DUNGEON_H
#include "rooms.h"
#include "dungeon_name.h"

typedef struct
{
    Room rooms[10];
} Dungeon;
Dungeon generate_dungeon(Hero* h,DUNGEON_NAME dungeon_name);
#endif



