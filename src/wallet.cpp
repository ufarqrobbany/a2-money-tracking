#include "account.h"
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

void showDompet(char username[20]) {
    char file_name[50];
    sprintf(file_name, "data/wallets/wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Gagal membuka file\n");
        return;
    }

    printf("Daftar Saldo Dompet:\n");
    struct Wallet wallet;
    while (fread(&wallet, sizeof(struct Wallet), 1, file) == 1) {
        printf("ID Dompet: %d, Nama Dompet: %s, Saldo: %d\n", wallet.id, wallet.nama_dompet, wallet.saldo);
    }

    fclose(file);
}

int getSaldoDompet(char username[20], int id_dompet) {
    char file_name[50];
    sprintf(file_name, "data/wallets/wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Gagal membuka file Username\n");
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
    printf("Dompet dengan ID '%d' tidak ditemukan\n", id_dompet);
    return -1;
}

int getTotalSaldo(char username[20]) {
    char file_name[50];
    sprintf(file_name, "data/wallets/wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("Gagal membuka file Username\n");
        return -1;
    }

    struct Account account;
    struct Wallet wallet;
    int totalSaldo = 0;
    while (fread(&account, sizeof(struct Account), 1, file) == 1) {
        if (strcmp(account.username, username) == 0) {
            while (fread(&wallet, sizeof(struct Wallet), 1, file) == 1) {
                totalSaldo += wallet.saldo;
            }
            break;
        }
    }

    fclose(file);
    return totalSaldo;
}