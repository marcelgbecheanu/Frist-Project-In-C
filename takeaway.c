#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clients.h"
#include "menus.h"
#include "clients.h"

int getOptionToSearchClient(){
    int option ;
    printf("\n > O NIF não pertence a nossa base de dados.");
    printf("\n > Pretende voltar a pesquisar ou criar um novo cliente.");
    printf("\n > 0 - Pesquisar por outro NIF \n 1 - Novo utilizador. \n");
    printf(" > Selecione: ");
    if (scanf("%d", &option) != 1) {
        getOptionToSearchClient();
    }
    return option;
}

client registerClient(char id[10], char name[50], char typology, char date[10], char hour[8], int ability, unsigned int table, unsigned int people, struct menu meal[10], char time[8], char detail[256], float total){
    client data;
    strcpy(data.id, id);
    strcpy(data.name, name);
    data.typology = typology;

    strcpy(data.date, "12/02/2020");

}


typedef struct dataClient {
    client user;
    int defined;
} dataClient;

dataClient getClient(){
    nodeClient *pointer = clients->head;
    char nif[10];
    system("cls");
    printf(" > Digite o NIF: ");
    scanf("%.10s", &nif);
    while (pointer != NULL){
        int compValue = strcmp(pointer->data.id,  nif);
        if(!(compValue < 0) && !(compValue>0)){
            dataClient data;
            data.user = pointer->data;
            data.defined = 1;
            return data;
        }
        pointer = pointer->next;
    }
    int option = getOptionToSearchClient();
    if(option == 1){
        //register client
        client c = registerClient();

        dataClient data;
        data.user = c;
        data.defined = 1;
        return data;

    }else if(option == 2){
        struct dataClient data;
        data.defined = 0;
    }
    system("pause");
}


void initializeTakeAway(){
    dataClient dataClient = getClient();
    if(dataClient.defined == 0){
        return;
    }



    system("pause");
}