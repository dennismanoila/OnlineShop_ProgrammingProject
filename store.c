#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "product.h"
#include "order.h"
#include "user.h"
#include "store.h"
#include "useful.h"
#include <windows.h>

void initialize_store()
{
    printf("Welcome to our store!\n");
    printf("1.Sign Up\n2.Login\n3.Exit\n");
    printf("Please choose one of the following options!\n->");
}

void display_main_menu(char name[20], char surname[20]) {
    while (1) {
        printf("\n\n\n\n\n\n");
        clear_screen();
        printf("Welcome %s! We are glad to see you! ", surname);
        printf("How can we help you today?\n");
        printf("1.Place Order\n2.Sell Product\n3.View Placed Orders\n4.Search Products\n5.Exit\n->");
        int decision;
        scanf("%d", &decision);
        clear_input_buffer();
        if (decision == 1) {
            int finished = 0;
            while (!finished) {
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                clear_screen();
                printf("What would you like to buy?\n->");
                char userProduct[256];
                fgets(userProduct, sizeof(userProduct), stdin);
                size_t len = strlen(userProduct);
                if (len > 0 && userProduct[len - 1] == '\n') {
                    userProduct[len - 1] = '\0';
                }
                int pos = searchProduct(globalProductList, userProduct);
                if (pos != -1) {
                    int orderPlaced = 0;
                    while (!orderPlaced) {
                        printf("How many pieces of this product do you want?\n->");
                        int userProductQuan;
                        scanf("%d", &userProductQuan);
                        clear_input_buffer();
                        int cnt = 0;
                        struct ProductNode *current = globalProductList.first;
                        while (cnt < pos)
                            current = current->next, cnt++;
                        if (current->product.quantity >= userProductQuan) {
                            int number = generateRandomNumber();
                            number = checkIfIDexists(number, &globalOrderList);
                            Order *newOrd = create_order(number, name, surname, current->product.name, userProductQuan,
                                                         current->product.price * (float) userProductQuan);
                            addOrderToCSV(newOrd);
                            current->product.quantity -= userProductQuan;
                            updateProductQuantityInCSV(&globalProductList);
                            addToOrderList(&globalOrderList, *newOrd);
                            printf("\n\n\n\n\n\n\n\n");
                            clear_screen();
                            printf("Order successfully placed!\n");
                            printf("Your total is: %.2f\nWould you like to place another order?\n",
                                   current->product.price * (float) userProductQuan);
                            printf("Type '1' if so, else type '2'.\n->");
                            int userDec;
                            while (1) {
                                scanf("%d", &userDec);
                                clear_input_buffer();
                                if (userDec == 1) {
                                    orderPlaced = 1;
                                    break;
                                } else if (userDec == 2) {
                                    printf("Redirecting to the main menu...");
                                    Sleep(3000);
                                    finished = 1;
                                    orderPlaced = 1;
                                    break;
                                } else printf("Please type a valid input!\n->");
                            }
                        }
                        else {
                            printf("Unfortunately, we don't have that much stock available! Would you like to buy less pieces of this product?\n");
                            printf("Type '1' if yes, else type '2' and you'll be redirected to the menu.\n->");
                            int userInput;
                            while (1) {
                                scanf("%d", &userInput);
                                clear_input_buffer();
                                if (userInput == 1) {
                                    //printf("\n\n\n\n\n");
                                    clear_screen();
                                    break;
                                }
                                else if (userInput == 2) {
                                    printf("Redirecting to the main menu...");
                                    Sleep(3000);
                                    finished = 1;
                                    orderPlaced = 1;
                                    break;
                                } else printf("Please type a valid input!\n->");
                            }

                        }
                    }
                } else {
                    printf("\nSorry we don't have this product!\nDo you want to buy something else?\n");
                    printf("Type '1' if yes, else type '2'.\n->");
                    int userDec;
                    while (1) {
                        scanf("%d", &userDec);
                        clear_input_buffer();
                        if (userDec == 1)
                            break;
                        else if (userDec == 2) {
                            finished = 1;
                            break;
                        } else printf("Please provide a valid input!\n->");

                    }
                }
            }


        }
        else if (decision == 2) {
            int cancel = 0;
            while (!cancel) {
                printf("\n\n\n\n\n\n\n\n");
                clear_screen();
                printf("What product are you selling?\n->");
                char product_name[256];
                fgets(product_name, sizeof(product_name), stdin);
                size_t len = strlen(product_name);
                if (len > 0 && product_name[len - 1] == '\n') {
                    product_name[len - 1] = '\0';
                }
                if (searchProduct(globalProductList, product_name) == -1) {
                    printf("How many pieces of your product do you sell?\n->");
                    unsigned int product_quantity;
                    scanf("%u", &product_quantity);
                    clear_input_buffer();
                    printf("What is the price/piece?\n->");
                    float product_price;
                    scanf("%f", &product_price);
                    clear_input_buffer();
                    Product *product = create_product(product_name, product_quantity, product_price);
                    addProductToCSV(product);
                    addToProductList(&globalProductList, *product);
                    clear_screen();
                    printf("Product uploaded successfully! Waiting for customers!");
                    printf("\nDo you want to go back to the menu or do you want to exit?\n");
                    printf("Type '1' to go back to the menu, or '2' to exit.\n");
                    while (1) {
                        int dec;
                        scanf("%d", &dec);
                        clear_input_buffer();
                        if (dec == 1) {
                            cancel = 1;
                            break;
                        } else if (dec == 2) {
                            clear_screen();
                            printf("We hope you will be back soon! Goodbye!");
                            Sleep(3000);
                            freeProductList(&globalProductList);
                            freeUserList(&globalUserList);
                            freeOrderList(&globalOrderList);
                            exit(0);
                        } else {
                            printf("Please provide a valid input!\n->");
                        }
                    }
                }
                else {
                    printf("This product is already in stock, would you like to sell something else?");
                    printf("\nType '1' if so, else type '2'.");
                    int can = 0;
                    while (!can) {
                        int decide;
                        scanf("%d", &decide);
                        if (decide == 1) {
                            clear_input_buffer();
                            break;
                        } else if (decide == 2) {
                            printf("\nDo you want to go back to the menu or do you want to exit?\n");
                            printf("Type '1' to go back to the menu, or '2' to exit.\n");
                            int Cancel = 0;
                            while (!Cancel) {
                                int dec;
                                scanf("%d", &dec);
                                if (dec == 1) {
                                    cancel = 1;
                                    Cancel = 1;
                                    can = 1;
                                } else if (dec == 2) {
                                    freeUserList(&globalUserList);
                                    freeProductList(&globalProductList);
                                    freeOrderList(&globalOrderList);
                                    printf("We hope you will be back soon! Goodbye!");
                                    Sleep(3000);
                                    exit(0);
                                } else {
                                    printf("Please provide a valid input!\n->");
                                }
                            }
                        } else printf("Please provide a valid input!\n->");
                    }
                }
            }


        }
        else if (decision == 3) {
            printf("\n\n\n\n\n\n\n\n\n\n");
            clear_screen();
            printf("Below you can see all of your orders:\n-------------------------------------");
            printf("\n//id, name, surname, product, quantity, total price\n-------------------------------------");
            struct OrderNode *current = globalOrderList.first;
            int ordersPlaced = 0;
            while (current != NULL) {
                if (strcmp(current->order.name, surname) == 0 && strcmp(current->order.surname, name) == 0) {
                    ordersPlaced = 1;
                    printf("\n->%u, %s, %s, %s, %u, %.2f", current->order.unique_code, current->order.surname,
                           current->order.name, current->order.product, current->order.buc,
                           current->order.total_price);
                }
                else if(strcmp(current->order.name, name) == 0 && strcmp(current->order.surname, surname) == 0)
                {
                    ordersPlaced = 1;
                    printf("\n->%u, %s, %s, %s, %u, %.2f", current->order.unique_code, current->order.name,
                           current->order.surname, current->order.product, current->order.buc,
                           current->order.total_price);
                }
                current = current->next;
            }

            if (!ordersPlaced)
                printf("\nIt seems like you haven't placed any order yet!");
            printf("\n-------------------------------------\n");
            printf("\n\nDo you want to go back to the main menu?\n");
            printf("Type '1' if yes, or type '2' to exit.\n->");
            int userDec;
            while (1) {
                scanf("%d", &userDec);
                clear_input_buffer();
                if (userDec == 1)
                    break;
                else if (userDec == 2) {
                    printf("\n\n\n\n\n\n\n\n\n");
                    clear_screen();
                    printf("We hope you will be back soon! Goodbye!");
                    freeUserList(&globalUserList);
                    freeProductList(&globalProductList);
                    freeOrderList(&globalOrderList);
                    Sleep(3000);
                    exit(0);
                } else printf("Please type a valid input!\n->");
            }
        }
        else if (decision == 4) {
            printf("\n\n\n\n\n\n\n\n\n\n\n");
            clear_screen();
            printf("Are you looking for a specific product?\n");
            printf("Or are you looking for products in a certain price range?\n");
            printf("Type '1' for the first option, or type '2' for the second one.\n->");
            int userDec;
            while (1) {
                scanf("%d", &userDec);
                clear_input_buffer();
                if (userDec == 1 || userDec == 2)
                    break;
                else printf("Please provide a valid input!\n->");
            }
            if (userDec == 1) {
                printf("\n\n\n\n\n\n");
                clear_screen();
                printf("What product are you looking for?\n->");
                char searchedProd[256];
                fgets(searchedProd, sizeof(searchedProd), stdin);
                size_t len = strlen(searchedProd);
                if (len > 0 && searchedProd[len - 1] == '\n') {
                    searchedProd[len - 1] = '\0';
                }
                struct ProductNode *current = globalProductList.first;
                int count = 0;
                while (current != NULL) {
                    char lowerProd1[strlen(current->product.name) + 1];
                    char lowerProd2[strlen(searchedProd) + 1];

                    for (int i = 0; current->product.name[i]; i++) {
                        lowerProd1[i] = tolower((unsigned char) current->product.name[i]);
                    }
                    lowerProd1[strlen(current->product.name)] = '\0';

                    for (int i = 0; searchedProd[i]; i++) {
                        lowerProd2[i] = tolower((unsigned char) searchedProd[i]);
                    }
                    lowerProd2[strlen(searchedProd)] = '\0';

                    if (strstr(lowerProd1, lowerProd2) != NULL)
                        printf("\nproduct:%s\nprice:%.2f\nstock:%u\n", current->product.name, current->product.price,
                               current->product.quantity), count++;
                    current = current->next;
                }
                printf("\nWe have found %d products similar with your input!", count);
                printf("\nGo back to the menu and place an order while the stock is still available!\n");
                printf("Press any key to get back to the menu:");
                int key;
                scanf("%d", &key);
                clear_input_buffer();
                printf("Redirecting to the menu...");
                Sleep(3000);
            }
            else {
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                clear_screen();
                printf("What is the minimum price?\n->");
                float userMinPrice;
                scanf("%f", &userMinPrice);
                if(userMinPrice<1)
                    userMinPrice = 1;
                printf("\nWhat is the maximum price?\n->");
                float userMaxPrice;
                scanf("%f", &userMaxPrice);
                if (userMinPrice > userMaxPrice) {
                    float aux = userMinPrice;
                    userMinPrice = userMaxPrice;
                    userMaxPrice = aux;
                }
                printf("\n\n\n\n\n\n\n\n\n\n\n");
                clear_screen();
                printf("Are you looking for a specific product in this range?\n");
                printf("Or are you looking for products of any kind that fit in this range?\n");
                printf("Type '1' for the first option, else type '2' for the second one.\n->");
                int userD;
                while (1) {
                    scanf("%d", &userD);
                    if (userD == 1 || userD == 2)
                        break;
                    else printf("Please provide a valid input!\n->");
                }
                if (userD == 1) {
                    clear_input_buffer();
                    printf("\n\n\n\n\n\n");
                    clear_screen();
                    printf("What product are you looking for?\n->");
                    char searchedProd[256];
                    fgets(searchedProd, sizeof(searchedProd), stdin);
                    size_t len = strlen(searchedProd);
                    if (len > 0 && searchedProd[len - 1] == '\n') {
                        searchedProd[len - 1] = '\0';
                    }
                    struct ProductNode *current = globalProductList.first;
                    int cnt = 0;
                    while (current != NULL) {
                        char lowerProd1[strlen(current->product.name) + 1];
                        char lowerProd2[strlen(searchedProd) + 1];

                        for (int i = 0; current->product.name[i]; i++) {
                            lowerProd1[i] = tolower((unsigned char) current->product.name[i]);
                        }
                        lowerProd1[strlen(current->product.name)] = '\0';

                        for (int i = 0; searchedProd[i]; i++) {
                            lowerProd2[i] = tolower((unsigned char) searchedProd[i]);
                        }
                        lowerProd2[strlen(searchedProd)] = '\0';

                        if (strstr(lowerProd1, lowerProd2) != NULL)
                            if (current->product.price <= userMaxPrice && current->product.price >= userMinPrice)
                                printf("\nproduct:%s\nprice:%.2f\nstock:%u\n", current->product.name,
                                       current->product.price, current->product.quantity), cnt++;
                        current = current->next;
                    }
                    printf("\nWe have found %d products similar with your input!", cnt);
                    printf("\nGo back to the menu and place an order while the stock is still available!\n");
                    printf("Press any key to get back to the menu:");
                    int key;
                    scanf("%d", &key);
                    clear_input_buffer();
                    clear_screen();
                    printf("Redirecting to the menu...");
                    Sleep(3000);
                }
                else
                {
                    printf("\n\n\n\n\n\n\n");
                    clear_screen();
                    char searchedProd[256];
                    fgets(searchedProd, sizeof(searchedProd), stdin);
                    size_t len = strlen(searchedProd);
                    if (len > 0 && searchedProd[len - 1] == '\n') {
                        searchedProd[len - 1] = '\0';
                    }
                    struct ProductNode *current = globalProductList.first;
                    int cnt = 0;
                    while (current != NULL) {
                        char lowerProd1[strlen(current->product.name) + 1];
                        char lowerProd2[strlen(searchedProd) + 1];

                        for (int i = 0; current->product.name[i]; i++) {
                            lowerProd1[i] = tolower((unsigned char) current->product.name[i]);
                        }
                        lowerProd1[strlen(current->product.name)] = '\0';

                        for (int i = 0; searchedProd[i]; i++) {
                            lowerProd2[i] = tolower((unsigned char) searchedProd[i]);
                        }
                        lowerProd2[strlen(searchedProd)] = '\0';

                        if (strstr(lowerProd1, lowerProd2) != NULL)
                            if (current->product.price <= userMaxPrice && current->product.price >= userMinPrice)
                                printf("\nproduct:%s\nprice:%.2f\nstock:%u\n", current->product.name,
                                       current->product.price, current->product.quantity), cnt++;
                        current = current->next;
                    }
                    printf("\nWe have found %d products similar with your input!", cnt);
                    printf("\nGo back to the menu and place an order while the stock is still available!\n");
                    printf("Press any key to get back to the menu:");
                    int key;
                    scanf("%d", &key);
                    clear_input_buffer();
                    printf("Redirecting to the menu...");
                    Sleep(3000);
                }
            }
        }
        else if (decision == 5)
        {
            printf("\n\n\n\n\n\n\n\n\n\n");
            clear_screen();
            printf("We hope you will be back soon! Goodbye!");
            freeUserList(&globalUserList);
            freeProductList(&globalProductList);
            freeOrderList(&globalOrderList);
            Sleep(3000);
            exit(0);
        }
    }
}


void createUserTab() {
    while(1) {
        printf("\n\n\n\n\n\n");
        clear_screen();
        printf("Please enter your name:");
        char name[256];
        scanf("%255s", name);
        clear_input_buffer();
        printf("Please enter your surname:");
        char surname[256];
        scanf("%255s", surname);
        clear_input_buffer();
        printf("Please enter your password:");
        char password[256];
        scanf("%255s", password);
        clear_input_buffer();

        int found = 0;
        struct UserNode *temp = globalUserList.first;
        while(temp!=NULL)
        {
            if(strcmp(name, temp->user.name)==0 && strcmp(surname, temp->user.surname)==0)
            {
                found = 1;
                break;
            }
            temp = temp->next;
        }

        if (found == 0) {
            create_user(name, surname, password, 0);
            break;
        }
        else{
            clear_screen();
            printf("A user called %s %s already exists!", name, surname);
            printf("\nDo you want to try again?\n");
            printf("If your answer is 'yes', type '1'.\n");
            printf("If your answer is 'no', type '2' and you'll be redirected to the initial page.\n->");
            int decision;
            int cancel = 0;
            while(1)
            {
                scanf("%d", &decision);
                clear_input_buffer();
                if (decision == 1) {
                    break;
                } else if (decision == 2) {
                    printf("\nRedirecting...");
                    Sleep(3000);
                    clear_screen();
                    initialize_store();
                    cancel = 1;
                    break;
                } else {
                    printf("Please provide a valid input!\n->");
                }
            }
            if(cancel == 1)
                break;
        }
    }
}

void user_login()
{
    printf("\n\n\n\n\n\n\n");
    clear_screen();
    printf("Please type your name:");
    char name[20];
    scanf("%20s", name);
    clear_input_buffer();
    printf("Please type your surname:");
    char surname[20];
    scanf("%20s", surname);
    clear_input_buffer();

    if(searchUser(globalUserList, name, surname) != -1) {
        printf("Please type your password:");
        char password[20];
        scanf("%20s", password);
        clear_input_buffer();
        int position = 0;
        struct UserNode *current = globalUserList.first;
        while(position!= searchUser(globalUserList, name, surname)) {
            current = current->next;
            position++;
        }
        if(strcmp(password, current->user.password)==0)
            display_main_menu(current->user.name, current->user.surname);
        else
        {
            printf("Wrong password! Would you like to try again?\n");
            printf("If the answer is 'yes', type '1'.\n");
            printf("If the answer is 'no', type '2' and you'll be redirected to the initial page.\n->");
            while(1)
            {
                int decision;
                scanf("%d", &decision);
                clear_input_buffer();
                if (decision == 1) {
                    int attempts = 0;
                    int logged = 0;
                    printf("\n\n\n\n\n\n");
                    clear_screen();
                    printf("Please type your password!");
                    while (attempts < 3) {
                        printf("\n->");
                        scanf("%20s", password);
                        clear_input_buffer();
                        if (strcmp(password, current->user.password) == 0) {
                            logged = 1;
                            break;
                        } else {
                            attempts++;
                            printf("\n\n\n\n\n\n");
                            clear_screen();
                            printf("Wrong, you have %d attempts left!", 3 - attempts);
                        }

                    }
                    printf("\n");
                    if (logged)
                        display_main_menu(current->user.name, current->user.surname);
                    else {
                        printf("\n\n\n\n\n\n\n");
                        clear_screen();
                        printf("You have tried to many times! Come back later!\n\n\n\n\n\n\n\n");
                        initialize_store();
                    }
                    break;
                } else if (decision == 2) {
                    printf("\n\n\n\n\n\n");
                    clear_screen();
                    initialize_store();
                    break;
                } else {
                    printf("Please provide a valid input!\n->");
                }

            }
        }
    }
    else if(searchUser(globalUserList, name, surname) == -1) {
        printf("User not found! Redirecting...\n\n\n\n\n\n");
        Sleep(3000);
        clear_screen();
        initialize_store();
    }
}