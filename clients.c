#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "clients.h"

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
        fprintf(file, "# -> Utilize está estrutura.\n# -> ID:NAME (MAX 30 CHARS):AMOUNT:PRICE");
        fclose(file);
    }
    file = NULL;
}
void loadClients(){
    createStorageIfNotExistClients();
    clients = createListClients();

    client clientCache;
    strcpy(clientCache.id, "23212121");
    strcpy(clientCache.name, "Marcel adawdaw");
    clientCache.typology = 'T';
    strcpy(clientCache.date, "21/02/2002");
    strcpy(clientCache.hour, "13/30/20");
    clientCache.ability = 1;
    clientCache.table = 2;
    clientCache.people = 2;
    clientCache.meal[0] = listMenus->head->data;
    clientCache.meal[1] = listMenus->head->next->data;
    strcpy(clientCache.time, "1:10:20");
    strcpy(clientCache.detail, "Não sei o que por{newline}nao sei o que por.");

    float value = 0.0f;
    for(int i=0; i<10; i++){
        if(clientCache.meal != NULL){
            value += clientCache.meal[i].price * clientCache.meal[i].amount;
        }
    }
    clientCache.total = value;
    pushClient(clients, clientCache);

    strcpy(clientCache.id, "232121111");
    strcpy(clientCache.name, "becheanu adawdaw");
    clientCache.typology = 'T';
    strcpy(clientCache.date, "21/02/2002");
    strcpy(clientCache.hour, "13/30/20");
    clientCache.ability = 1;
    clientCache.table = 2;
    clientCache.people = 2;
    clientCache.meal[0] = listMenus->head->data;
    clientCache.meal[1] = listMenus->head->next->data;
    strcpy(clientCache.time, "1:10:20");
    strcpy(clientCache.detail, "Não sei o que por{newline}nao sei o que por.");

    value = 0.0f;
    for(int i=0; i<10; i++){
        if(clientCache.meal != NULL){
            value += clientCache.meal[i].price * clientCache.meal[i].amount;
        }
    }
    clientCache.total = value;
    pushClient(clients, clientCache);

    strcpy(clientCache.id, "32323231");
    strcpy(clientCache.name, "dawdawa adawdaw");
    clientCache.typology = 'T';
    strcpy(clientCache.date, "21/02/2002");
    strcpy(clientCache.hour, "13/30/20");
    clientCache.ability = 1;
    clientCache.table = 2;
    clientCache.people = 2;
    clientCache.meal[0] = listMenus->head->data;
    clientCache.meal[1] = listMenus->head->next->data;
    strcpy(clientCache.time, "1:10:20");
    strcpy(clientCache.detail, "Não sei o que por{newline}nao sei o que por.");

    value = 0.0f;
    for(int i=0; i<10; i++){
        if(clientCache.meal != NULL){
            value += clientCache.meal[i].price * clientCache.meal[i].amount;
        }
    }
    clientCache.total = value;
    pushClient(clients, clientCache);
}

void saveClients(){
    createStorageIfNotExistClients();

    FILE *file;
    file = fopen(DIR_CLIENTS_STORAGE ,"w");

    nodeClient* pointer = clients->head;
    while(pointer != NULL){
        client c = pointer->data;
        fprintf(file,"%s*%s*%c*%s*%s*", c.id, c.name, c.typology, c.date, c.hour);

        printf("%s*%s*%c*%s", c.id, c.name, c.typology, c.date);
        system("pause");
        fprintf(file, "\n");
        pointer = pointer->next;
    }
    fclose(file);
    file = NULL;

}