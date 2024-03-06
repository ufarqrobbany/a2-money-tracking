// File umum yang mungkin berisi definisi konstanta, dan fungsi utilitas yang digunakan secara global di proyek.
#include "common.h"

// gotoxy, untuk mengatur lokasi kursor
// https://www.quora.com/Why-am-I-not-able-to-use-a-gotoxy-statement-in-C-while-working-in-Code-Blocks
void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

void clearScreen() {
    system("cls");
}

void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

char* formatRupiah(int value) {
    char buffer[20];
    sprintf(buffer, "%d", value);
    int length = strlen(buffer);
    reverse(buffer, length);
    char formatted[50];
    int j = 0;
    formatted[j++] = 'R';
    formatted[j++] = 'p';
    formatted[j++] = ' ';
    for (int i = 0; i < length; i++) {
        if (i > 0 && i % 3 == 0) {
            formatted[j++] = '.';
        }
        formatted[j++] = buffer[i];
    }
    formatted[j] = '\0';
    reverse(formatted, j);
    strcat(formatted, ",00");
    return strdup(formatted);
}
