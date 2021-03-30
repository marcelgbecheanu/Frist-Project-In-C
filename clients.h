#pragma once

#include "menus.h"

typedef struct client {
    char id[10]; // NIF
    char name[50];
    char typology;
    char date[10];
    char hour[8];
    int ability;
    unsigned int table;
    unsigned int people;
    struct menu meal[10];
    char time[8];
    char detail[256];
    float total;
} client;

typedef struct nodeClient{
    client data;
    struct nodeClient* next;
} nodeClient;

typedef struct listClients{
    int size;
    nodeClient* head;
} listClients;

listClients* clients;

void loadClients();
void saveClients();
void pushClient();
void dataTestClient();