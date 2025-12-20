#ifndef SAVE_H
#define SAVE_H
#include <time.h>
#include "hero.h"

typedef struct {
    time_t timestamp;
    Hero hero;   
} Save;

int count_completed_missions_from_hero(const Hero *h);
int count_items_from_hero(const Hero *h);
#endif