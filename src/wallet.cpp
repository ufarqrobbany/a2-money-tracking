#include "wallet.h"

// Buat dompet awal/default
void buatDompetAwal(char username[20]) {
    FILE *file;
    char file_name[50];

    Wallet dompet;

    dompet.id = 1;
    strcpy(dompet.nama_dompet, "Dompet");
    dompet.saldo = 0;

    sprintf(file_name, "data/wallets/wallet_%s.dat", username);
    file = fopen(file_name, "wb");

    if (file != NULL) {
        fwrite(&dompet, sizeof(struct Wallet), 1, file);
        fclose(file);
    } else {
        printf("Gagal membuka file\n");
    }
}