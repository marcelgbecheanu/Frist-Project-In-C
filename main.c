#include <windows.h>
#include <stdio.h>
#include "menu.h"
#include "menus.h"
#include "clients.h"

int main(){
    setUTF8();

    loadMenus();
    loadClients();

    int option = 0;
    while(option != 6){
        system("cls");
        option = showMenu();
        switch(option){
            case 1:
                showMenus();
                system("pause");
                break;
            case 2:
                saveClients();
                break;
            case 3:
                printf("%s\n",clients->head->data.id);
                printf("%s\n",clients->head->next->data.id);
                printf("%s\n",clients->head->next->next->data.id);

                system("pause");
                break;

        }
    }

}