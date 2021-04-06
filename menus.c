#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "menus.h"

listMenu* createListMenu(){
    listMenu* listCache = (listMenu *) malloc(sizeof(listMenu));

    listCache->size = 0;
    listCache->head = NULL;

    return listCache;
}

// ADICIONA UM MENU A LISTA
void pushMenu(listMenu* listCache, menu m){
    nodeMenu* nodeCache = (nodeMenu*) malloc(sizeof(nodeMenu));

    nodeCache->data = m;
    nodeCache->next = listCache->head;
    listCache->head = nodeCache;
    listCache->size++;
}

//IMPRIME A LISTA
void printListMenu(listMenu* l){
    nodeMenu* pointer = l->head;

    system("cls");
    printf("[!]=+=+=+=+=+=+=[ MENUS ]=+=+=+=+=+=+=[!]\n");
    while (pointer != NULL){
        printf("\n");
        printf(" > Número: %d\n", pointer->data.id);
        printf(" > Nome: %s\n", pointer->data.name);
        printf(" > Preço: %.2f €\n", pointer->data.price);
        printf(" > Quantidade: %d\n", pointer->data.amount);
        printf("\n");
        pointer = pointer->next;
    }
    printf("[!]=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=[!]\n");
}

// VERIFICA SE EXISTE UM FICHEIRO DE ARMAZENAMENTO SE NÃO O CRIA E DEFINE ALGUNS PARAMETROS DEFAULT
void createStorageIfNotExistMenus(){
    FILE *file;
    if (file = fopen(DIR_MENUS_STORAGE, "r"))
    {
        fclose(file);
    }
    else
    {
        file = fopen(DIR_MENUS_STORAGE ,"a");
        fprintf(file, "# -> Utilize está estrutura.\n# -> ID:NAME (MAX 30 CHARS):AMOUNT:PRICE");
        fprintf(file, "\n0:BATATA FRITA:1:2.5");
        fclose(file);
    }
    file = NULL;
}

//CARREGA DO FICHEIRO PARA A LISTA DINAMICA OS VALORES
void loadMenus(){
    createStorageIfNotExistMenus();
    listMenus = createListMenu();

    FILE* filePointer;
    int bufferLength = 255;
    char buffer[bufferLength];
    filePointer = fopen(DIR_MENUS_STORAGE, "r");
    while(fgets(buffer, bufferLength, filePointer)) {
        if(strstr(buffer, "#") == NULL){
            char *p = strtok(buffer, ",");
            if(p)
            {
                char* piece = strtok(buffer, ":");

                menu m;

                m.id = atoi(piece);

                piece = strtok(NULL, ":");
                strcpy(m.name, piece);

                piece = strtok(NULL, ":");
                m.amount = atoi(piece);

                piece = strtok(NULL, ":");
                m.price = atof(piece);

                m.total = (m.amount * m.price);

                m.defined = 0;

                pushMenu(listMenus, m);
            }
        }
    }
    fclose(filePointer);

}
//IMPRIME A LISTA
void showMenus(){
    printListMenu(listMenus);
}