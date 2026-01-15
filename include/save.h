#ifndef SAVE_H
#define SAVE_H
#include <time.h>
#include "hero.h"

typedef struct
{
    time_t timestamp;
    int save_idx;
    Hero hero;
} Save;


typedef struct
{
    Save* saves;
    int count;
    
} SaveList;

void save_game(Hero *hero);
SaveList load_saves();
void delete_save(int save_idx);

#endif