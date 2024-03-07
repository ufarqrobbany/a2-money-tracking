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

char* formatRupiah(int uang) {
    char str[20];
    // Using snprintf to convert integer to string
    snprintf(str, sizeof(str), "%d", uang);

    int len = strlen(str);
    int i, j;

    // Add separator dots every 3 digits from the end
    for (i = len - 3; i > 0; i -= 3) {
        for (j = len; j > i; j--) {
            str[j] = str[j - 1];
        }
        str[i] = '.';
        len++;
    }

    // Add "Rp " and ",00" to the formatted string
    char* formatted = (char*)malloc(strlen(str) + 6);  // Allocate memory for the formatted string
    if (formatted == NULL) {
        printf("Memory allocation failed\n");
        exit(1);  // Exit the program if memory allocation fails
    }
    strcpy(formatted, "Rp ");  // Add "Rp "
    strcat(formatted, str);    // Concatenate the formatted string
    strcat(formatted, ",00");  // Add ",00"

    return formatted;
}
