#pragma once

typedef struct menu{
    int id;
    char name[30];
    int amount;
    float price;
    float total;
} menu;

typedef struct node{
    menu data;
    struct node* next;
} node;

typedef struct list{
    int size;
    node *head;
} list;

list* l;

void loadMenus();
void showMenus();