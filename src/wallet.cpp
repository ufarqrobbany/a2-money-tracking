#include "wallet.h"

#include "common.h"

// Buat dompet awal/default
void buatDompetAwal(char username[20]) {
    FILE *file;
    char file_name[50];

    Wallet dompet;

    dompet.id = 1;
    strcpy(dompet.nama_dompet, "Dompet");
    dompet.saldo = 0;

    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);
    file = fopen(file_name, "wb");

    fwrite(&dompet, sizeof(struct Wallet), 1, file);
    fclose(file);
}

int getDompet(char username[20], bool display) {
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    int n = 0;

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("\nGagal membuka file\n");
        return 0;
    }

    if (display) {
        printf("Daftar Dompet:\n");
    }
    struct Wallet wallet;
    while (fread(&wallet, sizeof(struct Wallet), 1, file) == 1) {
        if (display) {
            printf("- %s, ", wallet.nama_dompet);
            formatRupiah(wallet.saldo);
            printf("\n");
        }
        n++;
    }

    fclose(file);

    return n;
}

int getSaldoDompet(char username[20], int id_dompet) {
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("\nGagal membuka file Username\n");
        return -1;
    }

    struct Wallet wallet;
    while (fread(&wallet, sizeof(struct Wallet), 1, file) == 1) {
        if (wallet.id == id_dompet) {
            fclose(file);
            return wallet.saldo;
        }
    }

    fclose(file);
    printf("\nDompet dengan ID '%d' tidak ditemukan\n", id_dompet);
    return -1;
}

int getTotalSaldo(char username[20]) {
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("\nGagal membuka file Username\n");
        return -1;
    }

    struct Wallet wallet;
    int totalSaldo = 0;
    while (fread(&wallet, sizeof(struct Wallet), 1, file) == 1) {
        totalSaldo += wallet.saldo;
    }

    fclose(file);
    return totalSaldo;
}

int tambahDompet(char username[20], char nama_dompet[20], int saldo_awal) {
    FILE *file;
    char file_name[50];
    Wallet dompet, rDompet;
    bool dompetNameExists = false;

    dompet.id = getDompet(username, false) + 1;
    strcpy(dompet.nama_dompet, nama_dompet);
    dompet.saldo = saldo_awal;

    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);
    file = fopen(file_name, "ab+");

    while (fread(&rDompet, sizeof(struct Wallet), 1, file) == 1) {
        if (strcmp(rDompet.nama_dompet, dompet.nama_dompet) == 0) {
            dompetNameExists = true;
            printf("\nNama dompet sudah ada\n");
            fclose(file);
            return 1;
        }
    }

    if (!dompetNameExists) {
        fseek(file, 0, SEEK_END);
        fwrite(&dompet, sizeof(struct Wallet), 1, file);
        printf("\nBerhasil menambah dompet baru\n");
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}