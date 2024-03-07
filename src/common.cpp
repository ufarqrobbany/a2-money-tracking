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
    snprintf(str, sizeof(str), "%d", uang);

    int len = strlen(str);
    int i, j;

    for (i = len - 3; i > 0; i -= 3) {
        for (j = len; j > i; j--) {
            str[j] = str[j - 1];
        }
        str[i] = '.';
        len++;
    }

    for (i = 0; i < len; i++) {
        if (!(isdigit(str[i]) || str[i] == '.' || str[i] == 'R' || str[i] == 'p')) {
            str[i] = ' ';
        }
    }

    str[len] = '\0';

    printf("Rp%s", str);
}

int getLengthFormatRupiah(int uang) {
    char str[20];
    snprintf(str, sizeof(str), "%d", uang);

    int len = strlen(str);
    int i, j;

    for (i = len - 3; i > 0; i -= 3) {
        for (j = len; j > i; j--) {
            str[j] = str[j - 1];
        }
        str[i] = '.';
        len++;
    }

    for (i = 0; i < len; i++) {
        if (!(isdigit(str[i]) || str[i] == '.' || str[i] == 'R' || str[i] == 'p')) {
            str[i] = ' ';
        }
    }

    str[len] = '\0';

    // Return the length of the formatted string (excluding null terminator)
    return strlen(str);
}
