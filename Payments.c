#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
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
            // Temos o cliente;

          /*  time_t now;
            struct tm *now_tm;
            int hour;
            int min;
            int sec;

            now = time(NULL);
            now_tm = localtime(&now);
            hour = now_tm->tm_hour;
            min = now_tm->tm_min;
            sec = now_tm->tm_sec;

            int hourIn = 0;
            char tempo[2] = {pointer->data.hour[0], pointer->data.hour[1]};
            hourIn = atoi(19);
*/
            char mins[2] = {pointer->data.hour[3], pointer->data.hour[4]};
        //    int minIn = atoi(30);
            fflush(stdout);
            fflush(stdin);
            fflush(stderr);
            setvbuf(stdout, NULL, _IONBF, 0);


            printf("%s", mins);
            system("pause");

/*
            printf("\nHora de Entrada: %2.d", hourIn);
            system("pause");


            printf("\nMin de Entrada: %2.d", minIn);
            system("pause");

*/

/*



            fflush(stdin);
            char secs[2] = {pointer->data.hour[6], pointer->data.hour[7]};
            int cache3 = 0;
            sscanf(secs, "%d", &cache3);
            sec -= cache3;


            char timp[8];
            sprintf(timp, "%d:%d:%d", hour, min, sec);
            strcpy(pointer->data.time, timp);

*/


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