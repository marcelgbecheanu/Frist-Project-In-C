#pragma once

typedef struct menu{
    int id;
    char name[30];
    int amount;
    float price;
    float total;
} menu;

typedef struct nodeMenu{
    menu data;
    struct nodeMenu* next;
} nodeMenu;

typedef struct listMenu{
    int size;
    nodeMenu *head;
} listMenu;

listMenu* l;

void loadMenus();
void showMenus();