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

void getDompet(char *namaFile) {
    FILE *file = fopen(namaFile, "rb");
    if (file == NULL) {
        printf("Gagal membuka file %s\n", namaFile);
        return;
    }

    printf("Daftar Saldo Dompet:\n");
    struct Wallet wallet;
    while (fread(&wallet, sizeof(struct Wallet), 1, file) == 1) {
        printf("ID Dompet: %d, Nama Dompet: %s, Saldo: %d\n", wallet.id, wallet.nama_dompet, wallet.saldo);
    }

    fclose(file);
}