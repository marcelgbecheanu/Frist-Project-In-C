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
    system("cls");
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
    system("cls");
    fflush(stdin);
    char date[10];
    printf("› Digite a data para levantamento: ");
    scanf("%s", &date);
    if(strlen(date) < 10 || date[2] != '/' || date[5] != '/') {
        printf("\n› A data é invalida utilize o seguinte formato dd/MM/yyyy!");
        system("pause");
        getDate();
    }
    char* p = date;
    return p;
}

char* getHour(){
    system("cls");
    fflush(stdin);
    char hour[8];
    printf("› Digite a hora do levantamento: ");
    scanf("%s", &hour);
    if(strlen(hour) < 8 || hour[2] != ':' || hour[5] != ':') {
        printf("\n› A hora é invalida utilize o seguinte formato hh:mm:ss!");
        system("pause");
        getHour();
    }
    char* p = hour;
    return p;
}

dataClient registerClient(char *nif){
    dataClient client;
    strcpy(client.data.id, nif);
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
                return registerClient(NIF);
            }else if(option == 2){
                return searchClient();
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

menu getMeal(){
    int id = 0;
    printf("› Selecione o menu: ");
    scanf("%d", &id);
    nodeMenu* pointerMenu = listMenus->head;
    while (pointerMenu != NULL){
        if(pointerMenu->data.id == id) {

            int qnt = 0;
            printf("\n› Quantidade de menu: ");
            scanf("%d", &qnt);
            printf("\n› Valor Total do Menu: %f\n", qnt*pointerMenu->data.price);

            menu menuCache = pointerMenu->data;
            menuCache.amount = qnt;
            menuCache.total = qnt*menuCache.price;
            menuCache.defined = 1;

            return menuCache;

        }
        pointerMenu = pointerMenu->next;
    }
    menu menuCache;
    menuCache.defined = 0;
    printf("› Não foi possivel encontrar o menu selecionado.\n");
    system("pause");
    return menuCache;
}

void getMeals(nodeClient *pointer){
    fflush(stdin);
    int option = 0;
    for(int i=0; i<10; i++){
        if(option == 0){
            system("cls");

            nodeMenu* meal = listMenus->head;

            printf("[!]=+=+=+=+=+=+=+=[ MENUS ]=+=+=+=+=+=+=+=[!]\n");
            printf("\n");
            while (meal != NULL){
                printf(" > Número: %d", meal->data.id);
                printf(" Nome: %s\n", meal->data.name);
                printf("\n");
                meal = meal->next;
            }
            printf("[!]=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=[!]\n");

            menu a = getMeal();
            if(i >= 0 && a.defined != 1){
                i--;
            }else{
                pointer->data.meal[i] = a;
            }


            printf("› Deseja adicionar mais produtos: (0 - Sim : 1 - Não)\n› ");
            scanf("%d", &option);
        }
    }
    pointer->data.total = 0.0f;
    for(int i =0; i<10; i++){
        if(pointer->data.meal[i].defined == 1){
            pointer->data.total += pointer->data.meal[i].total;
        }
    }
    printf("› Valor Total: %f", pointer->data.total);
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
            strcpy(pointer->data.date, getDate());
            strcpy(pointer->data.hour, getHour());
            pointer->data.ability = 0;
            pointer->data.table = 0;
            pointer->data.people = 0;
            strcpy(pointer->data.time, "NaN");


            menu menuCache;
            menuCache.defined=0;
            for(int i=0; i<10; i++){
                pointer->data.meal[i] = menuCache;
            }
            getMeals(pointer);

            fflush(stdin);
            system("cls");
            printf("> Descrição do pedido: ");
            scanf("%[^\n]", pointer->data.detail);


        }else{
            //algum erro deve ter acontecido
            //fazer isto se tempo

        }
        pointer = pointer->next;
    }

}