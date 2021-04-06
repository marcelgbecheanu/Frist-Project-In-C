#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "clients.h"

int checkInvalidNumberPS(char* string){
    for (int i=0; i<strlen(string); i++)
        if (!isdigit(string[i])) {
            return 1;
        }
    return 0;
}


char* getNifPS(){
    fflush(stdin);
    char nif[10];
    system("cls");
    printf("› Digite o NIF: ");
    scanf("%s", &nif);
    if(checkInvalidNumberPS(nif) != 1){
        char* p = nif;
        return p;
    }else{
        printf("\n› O nif não é valido.\n");
        system("pause");
        getNifPS();
    }
}

void showPayment(){
    nodeClient *pointer = clients->head;
    char nif[10];
    strcpy(nif, getNifPS());
    while (pointer != NULL){
        if(strcmp(pointer->data.id, nif) == 0){

            fflush(stdin);
            fflush(stdout);
            fflush(NULL);
            fseek(stdin,0,SEEK_END);

            time_t now;
            struct tm *now_tm;
            int hour;
            int min;
            int sec;

            now = time(NULL);
            now_tm = localtime(&now);

            hour = now_tm->tm_hour;
            min = now_tm->tm_min;
            sec = now_tm->tm_sec;

            char tempoCache[2] = {pointer->data.hour[0], pointer->data.hour[1]};
            int hourInCache;
            sscanf(tempoCache, "%d", &hourInCache);

            char minsCache[2] = {pointer->data.hour[3], pointer->data.hour[4]};
            int minInCache;
            sscanf(minsCache, "%d", &minInCache);

            char secsCache[2] = {pointer->data.hour[6], pointer->data.hour[7]};
            int secInCache;
            sscanf(secsCache, "%d", &secInCache);

            //Agora vamos converter para segundos
            int secTimeIn = (hourInCache * 3600) + (minInCache * 60) + secInCache;
            int secTimeOut = (hour * 3600) + (min * 60) + sec;

            //Realizamos o calculo tempo final - tempo inicial
            int finalTime = (secTimeOut-secTimeIn);

            // voltamos a converter para o formato hh:mm:ss
            int hh, mm, ss;
            hh = finalTime/3600;
            mm = (finalTime - hh*3600)/60;
            ss = finalTime - hh*3600 - mm*60;


            char timp[8];
            sprintf(timp, "%d:%d:%d", hh, mm, ss);
            strcpy(pointer->data.time, timp);

            system("cls");
            printf(" Cliente: %.50s\n", pointer->data.name);
            printf(" NIF: %.10s\n", pointer->data.id);
            printf("\n Conteudo Discriminado: \n");
            for(int i = 0; i<10; i++){
                if(pointer->data.meal[i].defined == 1){
                    menu mn = pointer->data.meal[i];
                    printf("\n %.30s %.2f €", mn.name, mn.price);
                    printf("\n %d * %.2f = %.2f\n", mn.amount, mn.price, mn.total);
                }
            }
            printf("\n Descrição do Pedido: \n");
            printf(" %.256s\n", pointer->data.detail);
            printf("\n Duração: %s", pointer->data.time);
            printf("\n Valor Total: %.2f\n", pointer->data.total);
            system("pause");
            return;
        }
        pointer = pointer->next;
    }
    system("cls");
    printf("Não foi possivel encontrar o cliente.\n");
    system("pause");

}