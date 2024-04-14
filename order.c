#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "order.h"



struct OrderList globalOrderList;

void initialize_globalOrderList()
{
    globalOrderList = make_orderList();
}

struct OrderNode* make_orderNode(Order ord)
{
    struct OrderNode* temp = malloc(sizeof(struct OrderNode));
    temp->order.unique_code = ord.unique_code;
    temp->order.surname = malloc(strlen(ord.surname)+1);
    strcpy(temp->order.surname, ord.surname);
    temp->order.name = malloc(strlen(ord.name)+1);
    strcpy(temp->order.name, ord.name);
    temp->order.product = malloc(strlen(ord.product)+1);
    strcpy(temp->order.product, ord.product);
    temp->order.buc = ord.buc;
    temp->order.total_price = ord.total_price;
    temp->next = NULL;
    return temp;
}

struct OrderList make_orderList()
{
    struct OrderList orderList;
    orderList.first = orderList.last = NULL;
    orderList.orderList_len = 0;
    return orderList;
}

Order* create_order(unsigned int id, char* name, char* surname, char* boughtProd, unsigned int buc , float price)
{
    Order *temp = malloc(sizeof(Order));
    temp->unique_code = id;
    int length = strlen(name);
    temp->name = malloc(length+1);
    strcpy(temp->name, name);
    length = strlen(surname);
    temp->surname = malloc(length+1);
    strcpy(temp->surname, surname);
    length = strlen(boughtProd);
    temp->product = malloc(length+1);
    strcpy(temp->product, boughtProd);
    temp->buc = buc;
    temp->total_price = price;
    return temp;
}

void loadOrdersFromCSV() {
    FILE *file = fopen("C:\\Users\\Denis\\Desktop\\CLionProjects\\OnlineShopPP\\order.csv", "r");
    if (!file) {
        perror("Failed to open order.csv");
        return;
    }

    char line[1024];
    fgets(line, sizeof(line), file);
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';
        char *token = strtok(line, ",");
        if (!token) continue;
        unsigned int orderID = strtoul(token, NULL, 10);

        char *userSurname = strtok(NULL, ",");
        if (!userSurname) continue;

        char *userName = strtok(NULL, ",");
        if (!userName) continue;

        char *product = strtok(NULL, ",");
        if (!product) continue;

        token = strtok(NULL,",");
        if(!token) continue;
        unsigned int buc = strtoul(token,NULL,10);

        token = strtok(NULL, ",");
        if (!token) continue;
        float totalPrice = strtof(token, NULL);

        Order newOrder;
        newOrder.unique_code = orderID;
        newOrder.surname = userSurname;
        newOrder.name = userName;
        newOrder.product = product;
        newOrder.buc = buc;
        newOrder.total_price = totalPrice;

        struct OrderNode *newNode = make_orderNode(newOrder);
        if (globalOrderList.first == NULL) {
            globalOrderList.first = globalOrderList.last = newNode;
        } else {
            globalOrderList.last->next = newNode;
            globalOrderList.last = newNode;
        }
        globalOrderList.orderList_len++;
    }

    fclose(file);
}

void displayOrderList(struct OrderList orderList)
{
    struct OrderNode* current = orderList.first;
    while(current!=NULL)
    {
        printf("\n%u\n%s\n%s\n%s\n%.2f\n",current->order.unique_code, current->order.surname, current->order.name, current->order.product, current->order.total_price);
        current = current->next;
        printf("===============");
    }
}

void freeOrderList(struct OrderList* orderList)
{
    struct OrderNode* current = orderList->first;
    while(current!=NULL)
    {
        struct OrderNode* deleted = current;
        current = current->next;
        free(deleted);
    }
    free(current);
}

void addOrderToCSV(Order* order)
{
    FILE *file = fopen("C:\\Users\\Denis\\Desktop\\CLionProjects\\OnlineShopPP\\order.csv", "a");
    fprintf(file, "%u,%s,%s,%s,%u,%.2f\n",order->unique_code, order->name, order->surname, order->product, order->buc, order->total_price);
    fclose(file);
}

void addToOrderList(struct OrderList* orderList, Order order)
{
    struct OrderNode *orderNode = make_orderNode(order);
    if(orderList->first == NULL)
    {
        orderList->first = orderList->last = orderNode;
    }
    else{
        orderList->last->next = orderNode;
        orderList->last = orderNode;
    }
    orderList->orderList_len++;
}