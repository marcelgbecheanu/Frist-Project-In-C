#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    printf("\n[!]=+=+=+=+=+=+=[ RECIBO ]=+=+=+=+=+=+=[!]");
    nodeClient *pointer = clients->head;
    char nif[10];
    strcpy(nif, getNifPS());
    while (pointer != NULL){
        if(strcmp(pointer->data.id, nif) == 0){
            // Temos o cliente;

            system("cls");
            printf(" Cliente: %.50s\n", pointer->data.name);
            printf(" NIF: %.10s\n", pointer->data.id);

            printf("\n Conteudo Discriminado: \n");
            for(int i = 0; i<10; i++){
                if(pointer->data.meal[i].defined == 1){
                    menu mn = pointer->data.meal[i];
                    printf("\n %.30s %f €", mn.name, mn.price);
                    printf("\n %d * %f = %f\n", mn.amount, mn.price, mn.total);
                }
            }
            printf("\n Valor Total: %f\n", pointer->data.total);


            system("pause");
            return;
        }
        pointer = pointer->next;
    }
    //Não temos o cliente.
    system("cls");
    printf("Não foi possivel encontrar o cliente.\n");
    system("pause");

}