
#ifndef ONLINESHOPPP_ORDER_H
#define ONLINESHOPPP_ORDER_H

#include "product.h"

extern struct OrderList globalOrderList;

typedef struct{
    unsigned int unique_code;
    char* surname;
    char* name;
    char* product;
    unsigned int buc;
    float total_price;
} Order;

struct OrderNode{
    Order order;
    struct OrderNode* next;
};

struct OrderList{
    struct OrderNode *first;
    struct OrderNode *last;
    int orderList_len;
};

void initialize_globalOrderList();
void loadOrdersFromCSV();
struct OrderNode* make_orderNode(Order order);
struct OrderList make_orderList();
Order* create_order(unsigned int id, char* name, char* surname, char* boughtProd, unsigned int buc, float price);
void displayOrderList(struct OrderList orderList);
void freeOrderList(struct OrderList* orderList);
void addToOrderList(struct OrderList* orderList, Order order);
void addOrderToCSV(Order *order);

#endif //ONLINESHOPPP_ORDER_H
