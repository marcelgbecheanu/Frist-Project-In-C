#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clients.h"

int getOptionSS(){
    int cache = 0;
    printf("\n› Selecione: ");
    if(scanf("%d", &cache) != 1 || cache < 1 || cache > 4){
        printf("%d", &cache);
        printf("\n› Selecione uma opção de 1 a 4!\n");
        system("pause");
        getOptionSS();
    }
    return cache;
}

void getBestType(){
    int takeaway = 0;
    int notTakeAway = 0;
    nodeClient *pointer = clients->head;
    while(pointer != NULL){
        if(pointer->data.typology == 'P'){
            notTakeAway++;
        }else if(pointer->data.typology == 'T'){
            takeaway++;
        }
        pointer = pointer->next;
    }
    printf("\n\n› Takeaway: %d", takeaway);
    printf("\n› Restaurante: %d\n", notTakeAway);
    if(takeaway>notTakeAway){
        printf("› O tipo com mais demanada é takeaway.\n");
    }else{
        printf("› O tipo com mais demanada é comer no restaurante.\n");
    }
    system("pause");
}


void getSellDay(){
    fflush(stdin);
    fflush(stdout);
    char date[10];
    printf("› Digite o dia para a pesquisa: ");
    scanf("%s", &date);
    if(strlen(date) < 10 || date[2] != '/' || date[5] != '/') {
        printf("\n› A data é invalida utilize o seguinte formato dd/MM/yyyy!");
        system("pause");
        getSellDay();
    }

    int count = 0;
    nodeClient *pointer = clients->head;
    while(pointer != NULL){
        if(pointer->data.date[0] == date[0] && pointer->data.date[1] == date[1] && pointer->data.date[2] == date[2] && pointer->data.date[3] == date[3] && pointer->data.date[4] == date[4] && pointer->data.date[5] == date[5] && pointer->data.date[6] == date[6] && pointer->data.date[7] == date[7] && pointer->data.date[8] == date[8] && pointer->data.date[9] == date[9]){
            count++;
        }
        pointer = pointer->next;
    }
    printf("\n› Existem %d pedidos no dia %.10s.\n", count, date);
    system("pause");
}



void getSellMonth(){
    fflush(stdin);
    fflush(stdout);
    char date[7];
    printf("› Digite o Mês para a pesquisa: ");
    scanf("%s", &date);
    if(strlen(date) < 7 || date[2] != '/') {
        printf("\n› A data é invalida utilize o seguinte formato MM/yyyy!");
        system("pause");
        getSellMonth();
    }

    int count = 0;
    nodeClient *pointer = clients->head;
    while(pointer != NULL){
        if(pointer->data.date[2+1] == date[0] && pointer->data.date[2+2] == date[1] && pointer->data.date[2+3] == date[2] && pointer->data.date[2+4] == date[3] && pointer->data.date[2+5] == date[4] && pointer->data.date[2+6] == date[5] && pointer->data.date[2+7] == date[6]){
            count++;
        }
        pointer = pointer->next;
    }
    printf("\n› Existem %d pedidos no Mês %.7s.\n", count, date);
    system("pause");
}


void menuStatistics(){
    int option = 0;
    while(option != 4){
        system("cls");
        printf("\n 1 - Tipologia com maior demanda.\n");
        printf(" 2 - Total de vendas realizadas num Dia.\n");
        printf(" 3 - Total de vendas realizadas num Mês.\n");
        printf(" 4 - Voltar.\n");

        printf("\n");
        option = getOptionSS();
        switch(option){
            case 1:
                getBestType();
                break;
            case 2:
                getSellDay();
                break;
            case 3:
                getSellMonth();
                break;
            case 4:
                option = 4;
                break;
        }
    }
}