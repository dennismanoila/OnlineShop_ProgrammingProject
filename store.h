
#ifndef ONLINESHOPPP_STORE_H
#define ONLINESHOPPP_STORE_H

#include "product.h"
#include "order.h"
#include "user.h"


void initialize_store();
void createUserTab();
void shutdown_store();
void display_main_menu(char name[20], char surname[20]);
void user_login();
void user_logout();

#endif //ONLINESHOPPP_STORE_H
