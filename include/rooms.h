#ifndef ROOMS_H
#define ROOMS_H
#include "hero.h"
typedef enum
{
    EMPTY = 0,
    ENEMY = 1,
    TRAP = 2,
} RoomType;

typedef enum{
EMPTY_ROOM=0,
WILD_DOG=1,
GOBLIN=2,
SKELETON=3,
ORC=4,
POISONOUS_BOG=5,
ORC_GENERAL=6,
DARK_HATCH=7,
BAT=8,
ZOMBIE=9,
PHANTOM=10,
GREAT_VAMPHIRE=11,
GURDIAN_DEMON=12,
FALLING_CRYSTALS=13,
UNSAFE_BRIDGE=14,
MYSTERIOUS_CHEST=15,
STEEP_CLIFF=16,
ANCIENT_DRAGON=17
}RoomName;


extern int DUNGEON_TO_ROOM[3][6];

// char* ROOM_TO_NAME[18] = {"Empty Room","Wild Dog","Goblin","Skeleton","Orc","Poisonous Bog","Orc General",
// "Dark Hatch","Bat","Zombie","Phantom","Great Vampyre","Guardian Demon",
// "Falling Crystals","Unsafe Bridge","Mysterious Chest","Steep Cliff","Ancient Dragon"};

typedef struct
{
    RoomType type;
    RoomName name;
    int fatal_strike;
    int damage;
    int reward_coins;
} Room;
#endif 

Room generate_room(RoomName room_name,Hero* h);