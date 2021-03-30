#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "clients.h"
#include "menus.h"

typedef struct dataClient{
    client data;
    int defined;
} dataClient;

int checkInvalid(char* string){
    for(int i=0; i<strlen(string); i++){
        if(string[i] == '*'){
            return 1;
        }else{
            return 0;
        }
    }
}
int checkInvalidNumber(char* string){
    for (int i=0; i<strlen(string); i++)
        if (!isdigit(string[i])) {
            return 1;
        }
    return 0;
}

char* getNif(){
    fflush(stdin);
    char nif[10];
    system("cls");
    printf("› Digite o NIF: ");
    scanf("%s", &nif);
    if(checkInvalidNumber(nif) != 1){
        char* p = nif;
        return p;
    }else{
        printf("\n› O nif não é valido.\n");
        system("pause");
        getNif();
    }
}

char* getName(){
    fflush(stdin);
    char name[50];
    printf("› Digite o nome completo: ");
    scanf("%[^\n]", &name);
    if(checkInvalid(name) == 0 && strlen(name) > 4 && name != NULL){
        char* p = name;
        return p;
    }else{
        printf("\n› O nome não é valido.\n");
        system("pause");
        getName();
    }
}

char* getDate(){
    char name[50];
    printf("› Digite a completo: ");
    scanf("%s", &name);
}

dataClient registerClient(){
    dataClient client;
    strcpy(client.data.id, getNif());
    strcpy(client.data.name, getName());
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

dataClient searchClient(){
    char NIF[10];
    strcpy(NIF, getNif());
    nodeClient *clientsList = clients->head;
    while(clientsList != NULL){
        int compare = strcmp(clientsList->data.id, NIF);
        if(!(compare < 0) && !(compare>0)) {
            dataClient data;
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
                return registerClient();
            }else if(option == 2){
                searchClient();
            }
            else{
                dataClient data;
                data.defined = 0;
                return data;
            }
            break;
        }
    }
}

void initializeTakeAway(){
    dataClient searched = searchClient();
    if(searched.defined == 0){
        return;
    }
    //Agora que sabemos quem é o cliente vamos procurar o ponteiro dele.
    nodeClient* pointer = clients->head;
    while (pointer != NULL){
        int compare = strcmp(pointer->data.id, searched.data.id);
        if(!(compare < 0) && !(compare>0)) {
            //Foi encontrado o cliente.
            //Agora vamos preencher os dados.
            pointer->data.typology = 'T';



        }else{
            //algum erro deve ter acontecido
            //fazer isto se tempo

        }
        pointer = pointer->next;
    }

}