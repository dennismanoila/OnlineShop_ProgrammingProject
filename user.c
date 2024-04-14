#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "user.h"
#include "store.h"
#include "useful.h"

struct UserList globalUserList;

void initialize_globalUserList() {
    globalUserList = make_userList();
}

void loadUsersFromCSV() {
    FILE *file = fopen("C:\\Users\\Denis\\Desktop\\CLionProjects\\OnlineShopPP\\user.csv", "r");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *name = strtok(line, ",");
        char *surname = strtok(NULL, ",");
        char *password = strtok(NULL, ",");

        if (name && surname && password) {
            User newUser;
            newUser.name = malloc(strlen(name) + 1);
            if (newUser.name)
                strcpy(newUser.name, name);
            newUser.surname = malloc(strlen(surname) + 1);
            if (newUser.surname)
                strcpy(newUser.surname, surname);
            newUser.password = malloc(strlen(password) + 1);
            if (newUser.password)
                strcpy(newUser.password, password);

            addToUserList(&globalUserList, newUser);
        }
    }
    fclose(file);
}

void delete_user(struct UserNode *user) {
    if (user != NULL) {
        if (user->user.name) {
            free(user->user.name);
        }
        if (user->user.surname) {
            free(user->user.surname);
        }
        if (user->user.password) {
            free(user->user.password);
        }
        free(user);
    }
}

int searchUser(struct UserList userList, char name[20], char surname[20]) {
    struct UserNode *current = userList.first;
    int position = 0;
    while (current != NULL) {
        if (strcmp(current->user.name, name) == 0 && strcmp(current->user.surname, surname) == 0)
            return position;
        current = current->next;
        position++;
    }
    return -1;
}

struct UserNode *make_userNode(User user) {
    struct UserNode *temp;
    temp = malloc(sizeof(struct UserNode));
    temp->user.name = malloc(strlen(user.name) + 1);
    temp->user.surname = malloc(strlen(user.surname) + 1);
    temp->user.password = malloc(strlen(user.password) + 1);
    strcpy(temp->user.name, user.name);
    strcpy(temp->user.surname, user.surname);
    strcpy(temp->user.password, user.password);
    temp->user.order_count = 0;
    temp->next = NULL;
    return temp;
}

struct UserList make_userList() {
    struct UserList userList;
    userList.first = userList.last = NULL;
    userList.userList_len = 0;
    return userList;
}

void displayUserList(struct UserList userList) {
    struct UserNode *p = userList.first;
    while (p != NULL) {
        printf("\n%s\n%s\n%s\n", p->user.name, p->user.surname, p->user.password);
        p = p->next;
        printf("============");
    }
}

void addToUserList(struct UserList *userList, User user) {
    struct UserNode *userNode = make_userNode(user);
    if (userList->first == NULL) {
        userList->first = userList->last = userNode;
    } else {
        userList->last->next = userNode;
        userList->last = userNode;
    }
    userList->userList_len++;
}

User *create_user(char *name, char *surname, char *password, unsigned int order_count) {
    User *temp = malloc(sizeof(User));
    unsigned int length = strlen(name);
    temp->name = malloc(length + 1);
    strcpy(temp->name, name);
    length = strlen(surname);
    temp->surname = malloc(length + 1);
    strcpy(temp->surname, surname);
    length = strlen(password);
    temp->password = malloc(length + 1);
    strcpy(temp->password, password);
    temp->order_count = order_count;
    addToUserList(&globalUserList, *temp);
    addUserToCSV(temp);
    clear_screen();
    printf("Your account has successfully been created! Do you also want to log in?\n");
    printf("If the answer is 'yes', type '1'.\n");
    printf("If the answer is 'no', type '2' and you will be redirected to the initial page.\n->");
    int decision;
    while (1) {
        scanf("%d", &decision);
        if (decision == 1) {
            display_main_menu(temp->name, temp->surname);
            printf("ok\n");
            break;
        } else if (decision == 2) {
            clear_screen();
            initialize_store();
            break;
        } else {
            printf("Please provide a valid input!\n->");
        }
    }
    return temp;
}

void addUserToCSV(User *user) {
    FILE *file = fopen("C:\\Users\\Denis\\Desktop\\CLionProjects\\OnlineShopPP\\user.csv", "a");
    fprintf(file, "%s,%s,%s\n", user->name, user->surname, user->password);
    fclose(file);
}

void freeUserList(struct UserList *userList) {
    struct UserNode *current = userList->first;
    struct UserNode *next;

    while (current != NULL) {
        next = current->next;
        delete_user(current);
        current = next;
    }

    userList->first = NULL;
    userList->last = NULL;
    userList->userList_len = 0;
}
