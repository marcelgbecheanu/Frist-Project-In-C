#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "clients.h"
#include "menus.h"

listClients* createListClients(){
    listClients* listCache = (listClients *) malloc(sizeof(listClients));

    listCache->size = 0;
    listCache->head = NULL;

    return listCache;
}

// ADICIONA UM CLIENTE A LISTA
void pushClient(listClients* listCache, client c){
    nodeClient* nodeCache = (nodeClient*) malloc(sizeof(nodeClient));

    nodeCache->data = c;
    nodeCache->next = listCache->head;
    listCache->head = nodeCache;
    listCache->size++;
}
void dataTestClient(){
    client clientCache;
    strcpy(clientCache.id, "23212121");
    strcpy(clientCache.name, "Marcel Becheanu");
    clientCache.typology = 'T';
    strcpy(clientCache.date, "16/06/2030");
    strcpy(clientCache.hour, "13/30/20");
    clientCache.ability = 1;
    clientCache.table = 2;
    clientCache.people = 2;

    menu a = listMenus->head->data;
    a.defined = 1;
    clientCache.meal[0] = a;

    menu b = listMenus->head->next->data;
    b.defined = 1;
    clientCache.meal[1] = b;

    strcpy(clientCache.time, "1:10:20");
    strcpy(clientCache.detail, "Não sei o que por{newline}nao sei o que por.");

    float value = 0.0;
    for(int i=0; i<10; i++){
        if(clientCache.meal[i].defined == 1){
            value += clientCache.meal[i].price * clientCache.meal[i].amount;
        }
    }
    clientCache.total = value;
    pushClient(clients, clientCache);
}
// VERIFICA SE EXISTE UM FICHEIRO DE ARMAZENAMENTO SE NÃO O CRIA E DEFINE ALGUNS PARAMETROS DEFAULT
void createStorageIfNotExistClients(){
    FILE *file;
    if (file = fopen(DIR_CLIENTS_STORAGE, "r"))
    {
        fclose(file);
    }
    else
    {
        file = fopen(DIR_CLIENTS_STORAGE ,"a");
        fclose(file);
    }
    file = NULL;
}

void loadClients(){
    createStorageIfNotExistClients();
    clients = createListClients();

    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];
    filePointer = fopen(DIR_CLIENTS_STORAGE, "r");
    while(fgets(buffer, bufferLength, filePointer)) {
        if(strstr(buffer, "#") == NULL){
            char *p = strtok(buffer, ",");
            if(p)
            {
                if(strstr(p, "client") != NULL){
                    char* piece = strtok(buffer, "*");

                    client clientCache;
                    piece = strtok(NULL, "*");
                    strcpy(clientCache.id, piece);

                    piece = strtok(NULL, "*");
                    strcpy(clientCache.name, piece);

                    piece = strtok(NULL, "*");
                    clientCache.typology = piece[0];

                    piece = strtok(NULL, "*");
                    strcpy(clientCache.date, piece);

                    piece = strtok(NULL, "*");
                    strcpy(clientCache.hour, piece);

                    piece = strtok(NULL, "*");
                    clientCache.ability = atoi(piece);

                    piece = strtok(NULL, "*");
                    clientCache.table = atoi(piece);

                    piece = strtok(NULL, "*");
                    clientCache.people = atoi(piece);

                    piece = strtok(NULL, "*");
                    strcpy(clientCache.time, piece);

                    piece = strtok(NULL, "*");
                    strcpy(clientCache.detail, piece);

                    piece = strtok(NULL, "*");
                    clientCache.total = atof(piece);

                    pushClient(clients, clientCache);
                }else if(strstr(p, "menu") != NULL){
                    char* piece = strtok(buffer, "*");

                    menu menuCache;

                    piece = strtok(NULL, "*");
                    char user[10];
                    strcpy(user, piece);

                    piece = strtok(NULL, "*");
                    menuCache.id = atoi(piece);

                    piece = strtok(NULL, "*");
                    strcpy(menuCache.name, piece);

                    piece = strtok(NULL, "*");
                    menuCache.amount = atoi(piece);

                    piece = strtok(NULL, "*");
                    menuCache.price = atof(piece);

                    menuCache.total = (float) (menuCache.price * menuCache.amount);
                    menuCache.defined = 1;

                    nodeClient* pointerClient = clients->head;
                    while (pointerClient != NULL){
                        int compValue = strcmp(pointerClient->data.id,  user);
                        if(!(compValue < 0) && !(compValue>0)){
                            for(int i=0; i<10; i++){
                                if(pointerClient->data.meal[i].defined != 1){
                                    pointerClient->data.meal[i] = menuCache;
                                    break;
                                }
                            }
                        }
                        pointerClient = pointerClient->next;
                    }
                }
            }
        }
    }
    fclose(filePointer);
}

void saveClients(){
    createStorageIfNotExistClients();

    FILE *file;
    file = fopen(DIR_CLIENTS_STORAGE ,"w");

    nodeClient* pointer = clients->head;
    while(pointer != NULL){
        fprintf(file, "client*%.10s*", pointer->data.id);
        fprintf(file, "%.50s*", pointer->data.name);
        fprintf(file, "%c*", pointer->data.typology);
        fprintf(file, "%.10s*", pointer->data.date);
        fprintf(file, "%.8s*", pointer->data.hour);
        fprintf(file, "%d*", pointer->data.ability);
        fprintf(file, "%d*", pointer->data.table);
        fprintf(file, "%d*", pointer->data.people);
        fprintf(file, "%.8s*", pointer->data.time);
        fprintf(file, "%.256s*", pointer->data.detail);
        fprintf(file, "%f*", pointer->data.total);

        for(int i=0; i<10; i++){
                    if(pointer->data.meal[i].defined == 1){
                        fprintf(file, "\nmenu*");
                        fprintf(file, "%.10s*", pointer->data.id);
                        fprintf(file, "%d*", pointer->data.meal[i].id);
                        fprintf(file, "%.30s*", pointer->data.meal[i].name);
                        fprintf(file, "%d*", pointer->data.meal[i].amount);
                        fprintf(file, "%f*", pointer->data.meal[i].price);
                        fprintf(file, "");
                    }
        }
        fprintf(file, "\n");
        pointer = pointer->next;
    }
    fclose(file);
    file = NULL;

}