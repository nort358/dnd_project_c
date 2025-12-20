#include <time.h>
#include "../include/save.h"
#include <hero.h>

typedef struct {
    time_t timestamp;
    Hero hero;   
} Save;

static int count_completed_missions_from_hero(const Hero *h) {
    int completed = 0;
    completed += (h->first_mission_completed != 0);
    completed += (h->second_mission_completed != 0);
    completed += (h->third_mission_completed != 0);
    completed += (h->final_mission_unlocked != 0);
    return completed;
}

static int count_items_from_hero(const Hero *h) {
    int items = 0;
    items += (h->sword != 0);
    items += (h->armor != 0);
    items += h->health_potions;
    return items;
}


// typedef struct SaveNode {
//     Save save;
//     struct SaveNode *next;
// } SaveNode;

// SaveNode addSave(SaveNode *head, Hero hero) {
//     SaveNode *node = malloc(sizeof(SaveNode));
//     if (!node) {
//         printf("Memory allocation failed!\n");
//         return head;
//     }

//     node->save.hero = hero;
//     node->save.timestamp = time(NULL);

//     node->next = NULL;

//     if (head == NULL) {
//         return node;
//     }

//     // add to end of list
//     SaveNode *cur = head;
//     while (cur->next != NULL) {
//         cur = cur->next;
//     }
//     cur->next = node;

//     return head;
// }

// void printSaveList(SaveNode *head) {
//     int index = 1;
//     SaveNode *cur = head;

//     while (cur != NULL) {
//         struct tm *t = localtime(&cur->save.timestamp);

//         int completedCount = 0;
//         for (int i = 0; i < NUM_MISSIONS; i++) {
//             completedCount += cur->save.missions.completed[i];
//         }

//         printf("%d. %02d-%02d-%04d %02d:%02d:%02d , "
//                "%d L. POINTS , %d COINS , %d ITEMS , %d COMPLETED MISSIONS\n",
//                index,
//                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
//                t->tm_hour, t->tm_min, t->tm_sec,
//                cur->save.hero.hp,
//                cur->save.hero.coins,
//                cur->save.hero.numItems,
//                completedCount);

//         cur = cur->next;
//         index++;
//     }
// }
