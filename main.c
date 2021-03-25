#include <windows.h>
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
                break;

        }
    }

}