#include <time.h>
#include "../include/save.h"
#include "../include/hero.h"
#include <stdio.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "string.h"
#include <stdlib.h>
char save_folder[] = "saves";

int get_save_index(char *filename){
    int index = -1;
    sscanf(filename, "%d.save", &index);
    return index;
}

int generate_new_save_idx(){
    int save_number = 1;
    DIR *dir = opendir(save_folder);
    if (!dir) {
        printf("Empty dir");
        return -1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        int idx=get_save_index(entry->d_name);
        if (idx >= save_number) {
            save_number = idx + 1;
        }
    }
    closedir(dir);
    return save_number;
}

void save_game(Hero *hero){
    mkdir(save_folder, 0755);
    char path[256];
    int save_idx= generate_new_save_idx();
    snprintf(path, sizeof(path), "%s/%d.save", save_folder, save_idx);
    FILE *file =fopen(path,"wb");
    if (file==NULL){
        printf("File not exists");
        return;
    }
    time_t current_time = time(NULL);
    Save save = {current_time, save_idx, *hero};
    fwrite(&save,sizeof(save),1,file);
    fclose(file);
}
void delete_save(int save_idx){
    char path[256];
    snprintf(path, sizeof(path), "%s/%d.save", save_folder, save_idx);
    printf("Deleting save file: %s\n", path);
    remove(path);
}


Save load_save(char *filename)
{
    FILE *file =fopen(filename, "rb");
    if (file==NULL){
        printf("Save not exists");
        perror("fopen");
    }
    Save save;
    fread(&save,sizeof(save),1,file);
    fclose(file);
    return save;
}

int count_files(){
    DIR *dir = opendir(save_folder);
    if (!dir) {
        return 0;
    }
    struct dirent *entry;
    int n_files=0;

    while ((entry = readdir(dir)) != NULL) {
        char *filename = entry->d_name;
        size_t len = strlen(filename);
        if (!(len >= 5 && strcmp(filename + len - 5, ".save") == 0)) {
            continue;
        }
        n_files++;
    }
    closedir(dir);
    return n_files;
}

SaveList load_saves(){
    Save *saves;
    int count_saves=count_files();
    saves= malloc (count_saves*sizeof(Save));
    DIR *dir = opendir(save_folder);
    if (!dir) {
        return (SaveList){NULL, 0};
    }
    struct dirent *entry;

    int i = 0;
    while ((entry = readdir(dir)) != NULL) {
        char *filename = entry->d_name;
        size_t len = strlen(filename);
        if (!(len >= 5 && strcmp(filename + len - 5, ".save") == 0)) {
            continue;
        }
        char path[256];
        snprintf(path, sizeof(path), "%s/%s", save_folder, filename);
        saves[i]= load_save(path);
        i++;
    }
    closedir(dir);
    return (SaveList){saves, i};
};