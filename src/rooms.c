#include <rooms.h>
#include <dice.h>
#include <hero.h>
#include <sword.h>
#include <string.h>

int DUNGEON_TO_ROOM[3][6] = {{WILD_DOG,GOBLIN,SKELETON,ORC,POISONOUS_BOG,ORC_GENERAL},
{DARK_HATCH,BAT,ZOMBIE,PHANTOM,GREAT_VAMPHIRE,GURDIAN_DEMON},
{EMPTY_ROOM,FALLING_CRYSTALS,UNSAFE_BRIDGE,MYSTERIOUS_CHEST,STEEP_CLIFF,ANCIENT_DRAGON}};


char* DUNGEON_TO_NAME[18]={
    "Empty Room",
    "Wild Dog",
    "Goblin",
    "Skeleton",
    "Orc",
    "Poisonous Bog",
    "Orc General",
    "Dark Hatch",
    "Bat",
    "Zombie",
    "Phantom",
    "Great Vampire",
    "Gurdian Demon",
    "Falling Crystals",
    "Unsafe Bridge",
    "Mysterious Chest",
    "Steep Cliff",
    "Ancient Dragon"
};



Room generate_room(RoomName room_name,Hero* h)
{
    Room room;
    room.name=room_name;
    if (room_name == WILD_DOG)
    {
        room.type = ENEMY;
        room.fatal_strike = 2;
        room.damage = 1;
        room.reward_coins = 0;
    }
    else if (room_name == GOBLIN)
    {
        room.type = ENEMY;
        room.fatal_strike = 3;
        room.damage = 2;
        room.reward_coins = 2;
    }
    else if (room_name == SKELETON)
    {
        room.type = ENEMY;
        room.fatal_strike = 4;
        room.damage = 2;
        room.reward_coins = 4;
    }
    else if (room_name == ORC)
    {
        room.type = ENEMY;
        room.fatal_strike = 3; 
        room.damage = 4;
        room.reward_coins = 6;
    }
    else if (room_name == POISONOUS_BOG)
    {
        room.type = TRAP;
        room.fatal_strike = 0; 
        room.damage = roll_dice();
        room.reward_coins = 0;
    }
    else if (room_name == ORC_GENERAL)
    {
        room.type = ENEMY;
        if (h->sword==HERO_SWORD)
        {
            room.fatal_strike = 5; 
        }
        else
        room.fatal_strike = 6; 
        room.damage = 3;
        room.reward_coins = 12;
    }
    else if (room_name==DARK_HATCH)
    {
        room.type = TRAP;
        room.fatal_strike = 0; 
        room.damage = 3;
        room.reward_coins = 0;
    }
    else if (room_name==BAT)
    {
        room.type = ENEMY;
        room.fatal_strike = 2; 
        room.damage = 2;
        room.reward_coins = 1;
    }
    else if (room_name==ZOMBIE)
    {
        room.type = ENEMY;
        room.fatal_strike = 3; 
        room.damage = 2;
        room.reward_coins = 2;
    }
    else if (room_name==PHANTOM)
    {
        room.type = ENEMY;
        room.fatal_strike = 5; 
        room.damage = 2;
        room.reward_coins = 4;
    }
    else if (room_name==GREAT_VAMPHIRE)
    {
        room.type = ENEMY;
            room.fatal_strike = 4; 
            room.damage = 4;
            room.reward_coins = 7;
    }
    else if (room_name==GURDIAN_DEMON)
    {
        room.type = ENEMY;
        room.fatal_strike = 4; 
        room.damage = 6;
        room.reward_coins = 10;
    }
    else if (room_name==FALLING_CRYSTALS)
    {
        room.type = TRAP;
        room.fatal_strike = 0; 
        room.damage = 2;
        room.reward_coins = 0;
    }
    else if (room_name==UNSAFE_BRIDGE)
    {
        room.type = TRAP;
        room.fatal_strike = 0; 
        room.damage = 0;
        room.reward_coins = -3;
    }
    else if (room_name==MYSTERIOUS_CHEST)
    {
        room.type = TRAP;
        room.fatal_strike = 0; 
        room.damage = 0;//TODO
        room.reward_coins = 0;//TODO
    }
    else if (room_name==STEEP_CLIFF)
    {
        room.type = TRAP;
        room.fatal_strike = 0; 
        room.damage = roll_dice();
        room.reward_coins = 0;
    }
    else if (room_name==ANCIENT_DRAGON)
    {
        room.type = ENEMY;
            room.fatal_strike = 5; 
            room.damage = 10;
            room.reward_coins = 12;
    }
    else
    {
        room.type = EMPTY; 
        room.fatal_strike = 0;
        room.damage = 0;
        room.reward_coins = 0;
    }
    return room;
}