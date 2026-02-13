#ifndef HERO_H
#define HERO_H
#include "sword.h"
typedef struct {
    int life_points;  
    int coins;                 
    SwordType sword;                    
    int armor;      

    int mission_completed[3];  
    int final_mission_unlocked;   
} Hero;
extern int HERO_MAX_LIFE_POINTS;
void Hero_coins_change(Hero* h, int coins);
void Hero_life_points_change(Hero* h, int life_points);
void Hero_equip_sword(Hero* h);
void Hero_equip_hero_sword(Hero* h);
void Hero_equip_armor(Hero* h);
void Hero_complete_mission(Hero* h, int mission_number);

#endif 