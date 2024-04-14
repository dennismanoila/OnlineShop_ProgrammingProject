#include <stdio.h>
#include <stdlib.h>
#include "store.h"
#include "user.h"
#include "product.h"
#include "store.h"
#include "order.h"
#include "useful.h"

int main() {

    initialize_store();
    initialize_globalUserList();
    initialize_globalProductList();
    initialize_globalOrderList();
    loadUsersFromCSV();
    loadProductsFromCSV();
    loadOrdersFromCSV();
    int user_input;
    while(1) {
        scanf("%d", &user_input);
        if(user_input == 1) {
            clear_screen();
            createUserTab();
        }
        else if(user_input == 2) {
            clear_screen();
            user_login();
        }
        else if(user_input == 3) {
            clear_screen();
            printf("We hope you will be back soon! Goodbye!");
            break;
        }
        else
            printf("\nPlease provide a valid input!\n->");
        }

    freeUserList(&globalUserList);
    freeProductList(&globalProductList);
    freeOrderList(&globalOrderList);

    return 0;
}

