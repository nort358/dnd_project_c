#include "../include/tools.h"
#include <stdio.h>
#include <stdlib.h>
void safe_scanf(int *var){
if (scanf("%d", var) != 1) {
    printf("Invalid input!\n");

    int ch;
    while ((ch = getchar()) != '\n'); 
    *var = -1;
    return;
}
    int ch;
    while ((ch = getchar()) != '\n');  
}