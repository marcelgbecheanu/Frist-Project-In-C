#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "clients.h"
#include "tables.h"

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
    printf("› Digite a data para a reserva: ");
    scanf("%s", &date);
    if(strlen(date) < 10 || date[2] != '/' || date[5] != '/') {
        printf("\n› A data é invalida utilize o seguinte formato dd/MM/yyyy!\n");
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
    printf("› Digite a hora da reserva: ");
    scanf("%s", &hour);
    if(strlen(hour) < 8 || hour[2] != ':' || hour[5] != ':') {
        printf("\n› A hora é invalida utilize o seguinte formato hh:mm:ss!\n");
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

int getAmountPeople(){
    int amount;
    system("cls");
    fflush(stdin);
    printf("› Número de Pessoas: ");
    if(scanf("%d",&amount) != 1){
        getAmountPeople();
    }
    return amount;
}

int getAbilityRS(nodeClient* pointer){
    int numTable=0;
    nodeClient* pClientSearchTable = clients->head;
    while (pClientSearchTable != NULL){
        if(pClientSearchTable->data.ability == 1){
            if(pClientSearchTable->data.table == pointer->data.table){
                int compare = strcmp(pClientSearchTable->data.date, pointer->data.date);
                if(compare == -1) {
                    int compare2 = strcmp(pClientSearchTable->data.hour[0] + "" + pClientSearchTable->data.hour[1], pointer->data.hour[0] + "" + pointer->data.hour[1]);
                    if(compare2 == 0) {
                        numTable++;
                    }
                }
            }
        }
        pClientSearchTable = pClientSearchTable->next;
    }


    if(pointer->data.table == 2){
        if(numTable < listTables.twoTable){
            return 1;
        }
    }else if(pointer->data.table == 4){
        if(numTable < listTables.fourTable){
            return 1;
        }
    }else if(pointer->data.table == 6){
        if(numTable < listTables.sixTable){
            return 1;
        }
    }
    return 0;
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
                return searchClientRS();
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

menu getMealRS(){
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

void getMealsRS(nodeClient *pointer){
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

            menu a = getMealRS();
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
    system("pause");
}


void initializeReservation(){
    dataClientRS searched = searchClientRS();
    if(searched.defined == 0){
        return;
    }

    // Temos o client;
    //Agora que sabemos quem é o cliente vamos procurar o ponteiro dele.
    nodeClient* pointer = clients->head;
    while (pointer != NULL){
        int compare = strcmp(pointer->data.id, searched.data.id);
        if(!(compare < 0) && !(compare>0)) {
            //Foi encontrado o cliente.
            //Agora vamos preencher os dados.
            pointer->data.typology = 'P'; // p -> presencial
            strcpy(pointer->data.date, getDateRS()); // data da marcação
            strcpy(pointer->data.hour, getHourRS()); // hora da marcação


            pointer->data.people = getAmountPeople();

            //Procurar se existe mesas livres
            pointer->data.ability = 0;

            //Procurando Mesa definido um tipo de mesa.
            pointer->data.table = 0;
            if(pointer->data.people <= 2){
                pointer->data.table = 2;
            }else if(pointer->data.people <= 4){
                pointer->data.table = 4;
            }else{
                pointer->data.table = 6;
            }


            // Vamos verificar a disponibilidade.

            pointer->data.ability = getAbilityRS(pointer);
            if(pointer->data.ability != 1){
                printf("\n> Não foi possivel realizar sua reserva.\n");
                system("pause");

                //tenho que limpar os dados do cliente;
                //Temos que testar

                pointer->data.typology = 'N'; // n -> Nao identificado
                strcpy(pointer->data.date, "NaN"); // data da marcação
                strcpy(pointer->data.hour, "NaN"); // hora da marcação


                pointer->data.people = 0;

                //Procurar se existe mesas livres
                pointer->data.ability = 0;

                //Procurando Mesa definido um tipo de mesa.
                pointer->data.table = 0;

                menu menuCache;
                menuCache.defined=0;
                for(int i=0; i<10; i++){
                    pointer->data.meal[i] = menuCache;
                }
                return;
            }

            // Preencher menus
            menu menuCache;
            menuCache.defined=0;
            for(int i=0; i<10; i++){
                pointer->data.meal[i] = menuCache;
            }
            getMealsRS(pointer);

            fflush(stdin);
            system("cls");
            printf("> Descrição do pedido: ");
            scanf("%[^\n]", pointer->data.detail);

            if(pointer->data.ability == 1){
                printf("\n> A sua reserva foi efetuada.\n");
                system("pause");
            }


        }else{
            //algum erro deve ter acontecido
            //fazer isto se tempo

        }
        pointer = pointer->next;
    }


}