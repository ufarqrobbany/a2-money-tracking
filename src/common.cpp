// File umum yang mungkin berisi definisi konstanta, dan fungsi utilitas yang digunakan secara global di proyek.
#include "common.h"
#include <stdio.h>
#include <stdlib.h> // Include for malloc and free
#include <string.h>

// gotoxy, untuk mengatur lokasi kursor
// https://www.quora.com/Why-am-I-not-able-to-use-a-gotoxy-statement-in-C-while-working-in-Code-Blocks
void gotoxy(int x, int y) {
    printf("%c[%d;%df", 0x1B, y, x);
}

void clearScreen() {
    system("cls");
}

char* formatUang(char *uang) {
    int len = strlen(uang);
    int i, j;

    // Add separator dots every 3 digits from the end
    for (i = len - 3; i > 0; i -= 3) {
        for (j = len; j > i; j--) {
            uang[j] = uang[j - 1];
        }
        uang[i] = '.';
        len++;
    }

    // Add "Rp " and ",00" to the formatted string
    char* formatted = (char*)malloc(strlen(uang) + 6); // Allocate memory for the formatted string
    if (formatted == NULL) {
        printf("Memory allocation failed\n");
        exit(1); // Exit the program if memory allocation fails
    }
    strcpy(formatted, "Rp "); // Add "Rp "
    strcat(formatted, uang); // Concatenate the formatted string
    strcat(formatted, ",00"); // Add ",00"

    return formatted;
}

//int main() {
//    char a[10] = "100000000";
//
//    // Format a
//    char* formatted = formatUang(a);
//
//    // Print the formatted string
//    printf("%s\n", formatted);
//
//    // Free dynamically allocated memory
//    free(formatted);
//
//    return 0;
//}

