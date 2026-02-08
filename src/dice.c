#include "dice.h"
#include <stdlib.h>
#include <time.h>
int roll_dice()
{
    return rand_int(1,6);//TODO
}

int rand_int(int min,int max)
{
    srand(time(NULL));
    return rand()%(max-min+1)+min;
}