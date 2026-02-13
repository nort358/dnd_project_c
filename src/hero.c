#include "../include/hero.h"
#include <sword.h>
#include <stdio.h>
int HERO_MAX_LIFE_POINTS = 20;
void Hero_coins_change(Hero *h, int coins)
{
    h->coins += coins;
}

void Hero_life_points_change(Hero *h, int life_points)
{
    h->life_points += life_points;
}
void Hero_equip_sword(Hero *h)
{
    printf("You bought a sword! Attack +1!\n");
    h->sword = USUAL_SWORD;
}
void Hero_equip_hero_sword(Hero *h)
{
    printf("You found the Hero's Sword! Attack +2!\n");
    h->sword = HERO_SWORD;
}

void Hero_equip_armor(Hero *h)
{
    printf("You bought armor! Damage -1!\n");
    h->armor = 1;
}


void Hero_complete_mission(Hero *h, int mission_number)
{
    h->mission_completed[mission_number] = 1;
    if (h->mission_completed[0] && h->mission_completed[1] && h->mission_completed[2])
    {
        h->final_mission_unlocked = 1;
    }
}