#ifndef SAVE_H
#define SAVE_H
#include <time.h>
#include "hero.h"

typedef struct
{
    time_t timestamp;
    Hero hero;
} Save;

#endif