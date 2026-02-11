#ifndef HERO_H
#define HERO_H

typedef struct
{
    int hp;
    int money;
    int sword;
    int armor;
    int potions;
    int m1;
    int m2;
    int m3;
    int final;
} Hero;

void Hero_coins_change(Hero *h, int coins);
void Hero_life_points_change(Hero *h, int life_points);
void Hero_equip_sword(Hero *h);
void Hero_equip_hero_sword(Hero *h);
void Hero_equip_armor(Hero *h);
void Hero_complete_mission(Hero *h, int mission_number);
void Hero_add_health_potion(Hero *h);
void Hero_use_health_potion(Hero *h);

#endif
