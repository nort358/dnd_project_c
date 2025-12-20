#ifndef HERO_H
#define HERO_H

typedef struct {
    int life_points;  
    int coins;                 
    int sword;                    
    int armor;      
    int health_potions;            

    int first_mission_completed;  
    int second_mission_completed; 
    int third_mission_completed; 
    int final_mission_unlocked;   
} Hero;

void Hero_coins_change(Hero* h, int coins);
void Hero_life_points_change(Hero* h, int life_points);
void Hero_equip_sword(Hero* h);
void Hero_equip_armor(Hero* h);
void Hero_complete_mission(Hero* h, int mission_number);
void Hero_add_health_potion(Hero* h);
void Hero_use_health_potion(Hero* h);

#endif 
