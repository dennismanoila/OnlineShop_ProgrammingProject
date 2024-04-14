
#ifndef ONLINESHOPPP_USER_H
#define ONLINESHOPPP_USER_H

#include "order.h"

extern struct UserList globalUserList;

typedef struct{
    char *name;
    char *surname;
    Order *orders;
    char *password;
    unsigned int order_count;
}User;

struct UserNode{
    User user;
    struct UserNode *next;
};

struct UserList{
    struct UserNode *first;
    struct UserNode *last;
    int userList_len;
};

void initialize_globalUserList();
void loadUsersFromCSV();
User *create_user(char *name, char *surname, char *password, unsigned int order_count);
struct UserNode *make_userNode(User user);
struct UserList make_userList();
int searchUser(struct UserList userList, char name[20], char surname[20]);
void addToUserList(struct UserList *userList, User user);
void displayUserList(struct UserList userList);
void addUserToCSV(User *user);
void add_order_to_user(User *user, Order *order);
void view_orders(User *user);
void delete_user(struct UserNode *user);
void freeUserList(struct UserList *userList);


#endif //ONLINESHOPPP_USER_H
