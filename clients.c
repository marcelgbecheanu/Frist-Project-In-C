#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "clients.h"

listClients* createList(){
    listClients* listCache = (listClients *) malloc(sizeof(listClients));

    listCache->size = 0;
    listCache->head = NULL;

    return listCache;
}

// ADICIONA UM CLIENTE A LISTA
void push(listClients* listCache, client c){
    nodeClient* nodeCache = (nodeClient*) malloc(sizeof(nodeClient));

    nodeCache->data = c;
    nodeCache->next = listCache->head;
    listCache->head = nodeCache;
    listCache->size++;
}

// VERIFICA SE EXISTE UM FICHEIRO DE ARMAZENAMENTO SE NÃO O CRIA E DEFINE ALGUNS PARAMETROS DEFAULT
void createStorageIfNotExistMenus(){
    FILE *file;
    if (file = fopen(DIR_CLIENTS_STORAGE, "r"))
    {
        fclose(file);
    }
    else
    {
        file = fopen(DIR_CLIENTS_STORAGE ,"a");
        fprintf(file, "# -> Utilize está estrutura.\n# -> ID:NAME (MAX 30 CHARS):AMOUNT:PRICE");
        fprintf(file, "\n0:BATATA FRITA:1:2.5");
        fclose(file);
    }
    file = NULL;
}