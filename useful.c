#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include "useful.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int generateRandomNumber()
{
    srand(time(NULL));
    int randomNumber = 100 + rand() % 900;
    return randomNumber;
}

void clear_screen()
{
    system("cls");
}
