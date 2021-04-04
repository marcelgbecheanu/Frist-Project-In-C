#include <windows.h>
#include "menu.h"
#include "menus.h"
#include "clients.h"
#include "takeaway.h"
#include "reservations.h"
#include "tables.h"
#include "Payments.h"
#include "statistics.h"

int main(){
    setUTF8();

    loadMenus();
    loadClients();

    tables tablesCache;
    tablesCache.twoTable = 6;
    tablesCache.fourTable = 12;
    tablesCache.sixTable = 4;

    listTables = tablesCache;


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
                showPayment();
                break;
            case 5:
                menuStatistics();
                break;

        }
    }
    saveClients();

}