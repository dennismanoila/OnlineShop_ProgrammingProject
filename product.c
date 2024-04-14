#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "product.h"
#include "useful.h"

struct ProductList globalProductList;

void initialize_globalProductList() {
    globalProductList = make_productList();
}

void loadProductsFromCSV() {
    FILE *file = fopen("C:\\Users\\Denis\\Desktop\\CLionProjects\\OnlineShopPP\\product.csv", "r");

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        char *name = strtok(line, ",");
        char *quantityStr = strtok(NULL, ",");
        char *priceStr = strtok(NULL, ",");

        if (name && quantityStr && priceStr) {
            unsigned int quantity = (unsigned int) strtoul(quantityStr, NULL, 10);
            float price = strtof(priceStr, NULL);

            Product newProduct;
            newProduct.name = malloc(strlen(name)+1);
            if(newProduct.name)
                strcpy(newProduct.name, name);
            newProduct.quantity = quantity;
            newProduct.price = price;

            addToProductList(&globalProductList, newProduct);
        }
    }

    fclose(file);
}

Product *create_product(char *name, unsigned int quantity, float price)
{
    Product *temp = malloc(sizeof(Product));
    unsigned int length = strlen(name);
    temp->name = malloc(length+1);
    strcpy(temp->name, name);
    temp->quantity = quantity;
    temp->price = price;
    return temp;
}

struct ProductNode *make_productNode(Product product)
{
    struct ProductNode *temp;
    temp = malloc(sizeof(struct ProductNode));
    temp->product.name = malloc(strlen(product.name)+1);
    strcpy(temp->product.name, product.name);
    temp->product.quantity = product.quantity;
    temp->product.price = product.price;
    temp->next = NULL;
    return temp;
}

struct ProductList make_productList()
{
    struct ProductList productList;
    productList.first = productList.last = NULL;
    productList.productList_len = 0;
    return productList;
}

int searchProduct(struct ProductList productList, char* name)
{
    struct ProductNode *current = productList.first;
    int position = 0;
    while(current != NULL)
    {
        if(strstr(current->product.name, name)!=NULL)
            if(strlen(current->product.name)==strlen(name)) {
                return position;
            }
        current = current->next;
        position++;
    }
    return -1;
}

void deleteProduct(struct ProductNode *product) {
    if (product != NULL) {
        if (product->product.name) {
            free(product->product.name);
        }
        free(product);
    }
}

void addProductToCSV(Product *product) {
    FILE *file = fopen("C:\\Users\\Denis\\Desktop\\CLionProjects\\OnlineShopPP\\product.csv", "a");
    fprintf(file, "%s,%d,%.2f\n", product->name, product->quantity, product->price);
    fclose(file);
}

void addToProductList(struct ProductList* productList, Product product)
{
    struct ProductNode *productNode = make_productNode(product);
    if(productList->first == NULL)
    {
        productList->first = productList->last = productNode;
    }
    else{
        productList->last->next = productNode;
        productList->last = productNode;
    }
    productList->productList_len++;
}

void freeProductList(struct ProductList *productList)
{
    struct ProductNode *current = productList->first;
    struct ProductNode *next;

    while (current != NULL) {
        next = current->next;
        deleteProduct(current);
        current = next;
    }

    productList->first = NULL;
    productList->last = NULL;
    productList->productList_len = 0;
}

int checkIfIDexists(int number, struct OrderList* orderList)
{
    while(1) {
        struct OrderNode *current = orderList->first;
        int found = 0;
        while(current!=NULL)
        {
            if(current->order.unique_code == number) {
                found = 1;
            }
            if(found)
            {
                number = generateRandomNumber();
                break;
            }
            else current = current->next;
        }
        if(!found)
            return number;
    }
}


void updateProductQuantityInCSV(struct ProductList* productList)
{
    FILE *file = fopen("C:\\Users\\Denis\\Desktop\\CLionProjects\\OnlineShopPP\\product.csv", "w");
    if (!file) {
        perror("Error opening product.csv");
        return;
    }
    fprintf(file,"ProductName,Quantity,Price\n");
    fclose(file);

    file = fopen("C:\\Users\\Denis\\Desktop\\CLionProjects\\OnlineShopPP\\product.csv", "a");
    if (!file) {
        perror("Error reopening product.csv");
        return;

    }
    struct ProductNode *current = productList->first->next;
    while (current != NULL) {
        fprintf(file, "%s,%u,%.2f\n", current->product.name, current->product.quantity, current->product.price);
        current = current->next;
    }
    fclose(file);

}



void displayProductList(struct ProductList productList)
{
    struct ProductNode* current = productList.first;
    while(current!=NULL)
    {
        printf("\n%s\n%u\n%.2f\n",current->product.name, current->product.quantity, current->product.price);
        current = current->next;
        printf("===============");
    }
}