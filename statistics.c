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

int getDay(){
    int cache = 0;
    printf("\n› Digite o dia: ");
    if(scanf("%d", &cache) != 1){
        printf("%d", &cache);
        printf("\n› Selecione um valor inteiro!\n");
        system("pause");
        getDay();
    }
    return cache;
}

void getSellDay(){
    nodeClient *pointer = clients->head;
    int day = getDay();
    int count = 0;
    while(pointer != NULL){
        int cmp = strcmp(pointer->data.date[0]+pointer->data.date[1],(char)day);
        if(cmp == 0){
            count++;
        }
        pointer = pointer->next;
    }
    system("cls");
    printf("\n› Existem %d pedidos.\n", count);
    system("pause");
}


void menuStatistics(){
    int option = 0;
    while(option = 4){
        system("cls");
        printf("\n 1 - Tipologia com maior demanada.\n");
        printf(" 2 - Total de vendas realizadas num Dia.\n");
        printf(" 3 - Total de vendas realizadas num Mês.\n");
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
                break;
            case 4:
                break;
        }
    }
}