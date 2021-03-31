#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "clients.h"

typedef struct dataClientRS{
    client data;
    int defined;
} dataClientRS;

int checkInvalidRS(char* string){
    for(int i=0; i<strlen(string); i++){
        if(string[i] == '*'){
            return 1;
        }else{
            return 0;
        }
    }
}
int checkInvalidNumberRS(char* string){
    for (int i=0; i<strlen(string); i++)
        if (!isdigit(string[i])) {
            return 1;
        }
    return 0;
}

char* getNifRS(){
    fflush(stdin);
    char nif[10];
    system("cls");
    printf("› Digite o NIF: ");
    scanf("%s", &nif);
    if(checkInvalidNumberRS(nif) != 1){
        char* p = nif;
        return p;
    }else{
        printf("\n› O nif não é valido.\n");
        system("pause");
        getNifRS();
    }
}


char* getDateRS(){
    system("cls");
    fflush(stdin);
    char date[10];
    printf("› Digite a data para levantamento: ");
    scanf("%s", &date);
    if(strlen(date) < 10 || date[2] != '/' || date[5] != '/') {
        printf("\n› A data é invalida utilize o seguinte formato dd/MM/yyyy!");
        system("pause");
        getDateRS();
    }
    char* p = date;
    return p;
}

char* getHourRS(){
    system("cls");
    fflush(stdin);
    char hour[8];
    printf("› Digite a hora do levantamento: ");
    scanf("%s", &hour);
    if(strlen(hour) < 8 || hour[2] != ':' || hour[5] != ':') {
        printf("\n› A hora é invalida utilize o seguinte formato hh:mm:ss!");
        system("pause");
        getHourRS();
    }
    char* p = hour;
    return p;
}

char* getNameRS(){
    system("cls");
    fflush(stdin);
    char name[50];
    printf("› Digite o nome completo: ");
    scanf("%[^\n]", &name);
    if(checkInvalidRS(name) == 0 && strlen(name) > 4 && name != NULL){
        char* p = name;
        return p;
    }else{
        printf("\n› O nome não é valido.\n");
        system("pause");
        getNameRS();
    }
}

dataClientRS registerClientRS(char *nif){
    dataClientRS client;
    strcpy(client.data.id, nif);
    strcpy(client.data.name, getNameRS());
    client.data.typology = 'u';
    strcpy(client.data.date, "NaN");
    strcpy(client.data.hour, "NaN");
    client.data.ability = 0;
    client.data.table = 0;
    client.data.people = 0;
    menu a;
    a.defined = 0;
    for(int i=0; i<10; i++){
        client.data.meal[i] = a;
    }
    strcpy(client.data.time, "NaN");
    strcpy(client.data.detail, "NaN");
    client.defined = 1;

    pushClient(clients, client);
    return client;

}


dataClientRS searchClientRS(){
    char NIF[10];
    strcpy(NIF, getNifRS());
    nodeClient *clientsList = clients->head;
    while(clientsList != NULL){
        int compare = strcmp(clientsList->data.id, NIF);
        if(!(compare < 0) && !(compare>0)) {
            dataClientRS data;
            data.data = clientsList->data;
            data.defined = 1;
            return data;
        }
        clientsList = clientsList->next;
    }
    int valid = 0;
    while (valid == 0){
        fflush(stdin);
        int option;
        system("cls");
        printf("› O NIF não existe na nossa base de dados.\n");
        printf("› Você deseja adicionar um novo cliente? ( 1 - Sim , 2 - Não, 3 - Cancelar)\n› Selecione:");
        if(scanf("%d", &option) != 1 || option < 1 || option > 3){
            printf("\n› Selecione uma opção de 1 a 3!\n");
            system("pause");
        }else{
            valid = 1;
            if(option == 1){
               return registerClientRS(NIF);
            }else if(option == 2){
                searchClientRS();
            }
            else{
                dataClientRS data;
                data.defined = 0;
                return data;
            }
            break;
        }
    }
}

void initializeReservation(){
    dataClientRS searched = searchClientRS();
    if(searched.defined == 0){
        return;
    }
    // Temos o client;
}