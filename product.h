
#ifndef ONLINESHOPPP_PRODUCT_H
#define ONLINESHOPPP_PRODUCT_H

#include "order.h"

extern struct ProductList globalProductList;

typedef struct{
    char* name;
    unsigned int quantity;
    float price;
}Product;

struct ProductNode {
    Product product;
    struct ProductNode *next;
};

struct ProductList {
    struct ProductNode *first;
    struct ProductNode *last;
    int productList_len;
};

void initialize_globalProductList();
void loadProductsFromCSV();
Product *create_product(char *name, unsigned int quantity, float price);
struct ProductNode* make_productNode(Product product);
struct ProductList make_productList();
int searchProduct(struct ProductList productList, char* name);
void addToProductList(struct ProductList* productList, Product product);
void deleteProduct(struct ProductNode *product);
void addProductToCSV(Product *product);
void freeProductList(struct ProductList *productList);
int checkIfIDexists(int number, struct OrderList* orderList);
void displayProductList(struct ProductList productList);
void updateProductQuantityInCSV(struct ProductList* productList);


#endif //ONLINESHOPPP_PRODUCT_H
