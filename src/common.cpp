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

void formatRupiah(int uang) {
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


    // Replace characters that are not digits, separators, or currency symbol with a space
    for (i = 0; i < len; i++) {
        if (!(isdigit(str[i]) || str[i] == '.' || str[i] == 'R' || str[i] == 'p')) {
            str[i] = ' ';
        }
    }

    // Null-terminate the string
    str[len] = '\0';

    // Print the formatted string directly
    printf("Rp%s", str);
}
