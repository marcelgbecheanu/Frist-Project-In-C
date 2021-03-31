#include <windows.h>
#include <stdio.h>
#include "menu.h"
#include "menus.h"
#include "clients.h"
#include "takeaway.h"
#include "reservations.h"

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
                initializeTakeAway();
                break;
            case 3:
                initializeReservation();
                break;
            case 4:
                break;

        }
    }
    saveClients();

}