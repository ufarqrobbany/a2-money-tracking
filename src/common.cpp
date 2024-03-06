#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    for (int i = 0; i < length; i++) {
        if (i > 0 && i % 3 == 0) {
            formatted[j++] = '.';
        }
        formatted[j++] = buffer[i];
    }
    formatted[j] = '\0';
    reverse(formatted, j);
    strcat(formatted, ",00");
    strcat(formatted, " Rp");
    return strdup(formatted);
}
