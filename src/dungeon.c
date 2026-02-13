#include "dungeon.h"
#include <stdio.h>
#include <dice.h>
#include<rooms.h>
void test_dungeon()
{
    printf("Dungeon system is ready!\n");
}


Dungeon generate_dungeon(Hero *h, DUNGEON_NAME dungeon_name)
{

    Dungeon dungeon;
    for (int i=0;i<10;i++){
        int dice_res=roll_dice();
        dungeon.rooms[i] = generate_room(DUNGEON_TO_ROOM[dungeon_name][dice_res-1],h);
    }
    if (dungeon_name==ROTTING_SWAMP)
    {
        int count_generals=0;
        for (int i=0;i<10;i++){
            if (dungeon.rooms[i].name == ORC_GENERAL)
            {
                count_generals++;
            }
        }
        if (count_generals<3)
        { while (count_generals<3)
            {
                int index=rand_int(0,9);
                if (dungeon.rooms[index].name != ORC_GENERAL)
                {
                    dungeon.rooms[index] = generate_room(ORC_GENERAL,h);
                    count_generals++;
                }
        }    
        }}
    else if (dungeon_name==HAUNTED_MANSION)
    {
        int count_of_great_vampires=0;
        int count_of_guardian_demons=0;
        for (int i=0;i<10;i++){
            if (dungeon.rooms[i].name == GREAT_VAMPHIRE)
            {
                count_of_great_vampires++;}
            if (dungeon.rooms[i].name == GURDIAN_DEMON)
            {
                count_of_guardian_demons++;}}
        if (count_of_great_vampires<1 || count_of_guardian_demons<1)
        {
             while (count_of_great_vampires<1 || count_of_guardian_demons<1)
            {
                int index=rand_int(0,9);
                if (dungeon.rooms[index].name == GREAT_VAMPHIRE){
                    if (count_of_great_vampires>1){
                        dungeon.rooms[index] = generate_room(GURDIAN_DEMON,h);
                        count_of_guardian_demons++;
                        count_of_great_vampires--;
                    }
                }
                else if (dungeon.rooms[index].name == GURDIAN_DEMON){
                    if (count_of_guardian_demons>1){
                        dungeon.rooms[index] = generate_room(GREAT_VAMPHIRE,h);
                        count_of_great_vampires++;
                        count_of_guardian_demons--;
                    }
                }
                else{
                    if (count_of_great_vampires<1){
                        dungeon.rooms[index] = generate_room(GREAT_VAMPHIRE,h);
                        count_of_great_vampires++;
                    }
                    else if (count_of_guardian_demons<1){
                        dungeon.rooms[index] = generate_room(GURDIAN_DEMON,h);
                        count_of_guardian_demons++;
                    }
                }
        }
    }
    }
    else if (dungeon_name==CRYSTAL_CAVE)
    {
        int count_of_ancient_dragons=0;
        for (int i=0;i<10;i++){
            if (dungeon.rooms[i].name == ANCIENT_DRAGON)
            {
                count_of_ancient_dragons++;}
        }
        if (count_of_ancient_dragons<1)
        {
            int index=rand_int(0,9);
            if (dungeon.rooms[index].name != ANCIENT_DRAGON){
                dungeon.rooms[index] = generate_room(ANCIENT_DRAGON,h);
            }
        
    }}
    
    return dungeon;
}
