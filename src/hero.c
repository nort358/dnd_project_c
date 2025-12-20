#include "../include/hero.h"

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

void Hero_coins_change(Hero* h, int coins) {
    h->coins += coins;
}

void Hero_life_points_change(Hero* h, int life_points) {
    h->life_points += life_points;
}
void Hero_equip_sword(Hero* h) {
    h->sword = 1;
}
void Hero_equip_armor(Hero* h) {
    h->armor = 1;
}

void Hero_add_health_potion(Hero* h) {
    h->health_potions++;
}

void Hero_use_health_potion(Hero* h) {
    if (h->health_potions > 0) {
        h->life_points += 6; 
        h->health_potions--;
    }
}

void Hero_complete_mission(Hero* h, int mission_number) {
    if (mission_number == 1) {
        h->first_mission_completed = 1;
    } else if (mission_number == 2) {
        h->second_mission_completed = 1;
    } else if (mission_number == 3) {
        h->third_mission_completed = 1;
    } else if (mission_number == -1) {
        h->final_mission_unlocked = 1;
    }
}