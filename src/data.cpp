#include "data.h"

#include <stdio.h>

void catatData(struct Data data) {
    FILE *file = fopen("data.dat", "wb");

    if (file != NULL) {
        fwrite(&data, sizeof(struct Data), 1, file);
        fclose(file);
    } else {
        printf("Gagal membuka file untuk penyimpanan data.\n");
    }
}