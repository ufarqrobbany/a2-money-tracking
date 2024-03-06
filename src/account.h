#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int id;
    char nama[20];
    char username[20];
    char password[20];
};

int login(char username[20], char password[20]);
int daftar(char nama[20], char username[20], char password[20], char re_password[20]);