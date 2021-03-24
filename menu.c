#include <stdio.h>
#include <windows.h>
#include "utils.h"

void setUTF8(){
    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);
}

int getOption(){
    int cache = 0;
    printf("\n› Selecione: ");
    if(scanf("%d", &cache) != 1 || cache < 1 || cache > 6){
        printf("\n› Selecione uma opção de 1 a 6!");
        system("pause");
        getOption();
    }
    return cache;
}

int showMenu(){
    printf("[!]=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+[!]\n");
    printf("[!]   Gestão de Clientes de um Restaurante   [!]\n");
    printf("[!]=+=+=+=+=+=+=+=+=[OPÇÕES]=+=+=+=+=+=+=+=+=[!]\n");
    printf("[!]                                          [!]\n");
    printf("[!] 1 - Visualizar Refeições.                [!]\n");
    printf("[!] 2 - Takeaway.                            [!]\n");
    printf("[!] 3 - Reservar no Restaurante.             [!]\n");
    printf("[!] 4 - Cobrar/Gerar fatura.                 [!]\n");
    printf("[!] 5 - Estatísticas.                        [!]\n");
    printf("[!] 6 - Finalizar.                           [!]\n");
    printf("[!]                                          [!]\n");
    printf("[!]=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+[!]\n");
    return getOption();
}