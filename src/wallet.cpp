#include "wallet.h"

<<<<<<< HEAD
#include "common.h"
=======
#include "account.h"
>>>>>>> a63855bc2837ff11ce0946f82ad3e64b233a7955

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
<<<<<<< HEAD

    int n = 0;
=======
>>>>>>> a63855bc2837ff11ce0946f82ad3e64b233a7955

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
        if (strcmp(wallet.nama_dompet, "") != 0) {
            if (display) {
                printf("- %s, ", wallet.nama_dompet);
                formatRupiah(wallet.saldo);
                printf("\n");
            }
            n++;
        }
    }

    fclose(file);

    return n;
}

int getSaldoDompet(char username[20], int id_dompet) {
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("\nGagal membuka file dompet\n");
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

char *getNamaDompet(char username[20], int id_dompet) {
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("\nGagal membuka file dompet\n");
        exit(1);
    }

    struct Wallet wallet;
    while (fread(&wallet, sizeof(struct Wallet), 1, file) == 1) {
        if (wallet.id == id_dompet) {
            fclose(file);

            // Alokasi memori baru untuk menyimpan nama_dompet
            char *nama_dompet = (char *)malloc(strlen(wallet.nama_dompet) + 1);

            if (nama_dompet == NULL) {
                printf("\nGagal melakukan alokasi memori\n");
                exit(1);
            }

            // Salin nama_dompet ke memori yang dialokasikan
            strcpy(nama_dompet, wallet.nama_dompet);

            return nama_dompet;
        }
    }

    fclose(file);
    printf("\nDompet dengan ID '%d' tidak ditemukan\n", id_dompet);
    return NULL;  // Kembalikan NULL jika dompet tidak ditemukan
}

int getLastIDDompet(char username[20]) {
    char file_name[50];
    int id;
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("\nGagal membuka file dompet\n");
        return -1;
    }

    struct Wallet wallet;
    while (fread(&wallet, sizeof(struct Wallet), 1, file) == 1) {
        id = wallet.id;
    }

    fclose(file);
    return id;
}

int getFirstNonEmptyID(int idKosong[], int kosong, int lastID) {
    int i, j;

    for (i = 1; i <= lastID; ++i) {
        int found = 0;

        for (j = 0; j < kosong; ++j) {
            if (i == idKosong[j]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            return i;
        }
    }

    return 0;
}

int getTotalSaldo(char username[20]) {
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("\nGagal membuka file dompet\n");
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

int isIdInKosong(int id, int idKosong[], int kosong) {
    for (int i = 0; i < kosong; i++) {
        if (id == idKosong[i]) {
            return 1;
        }
    }
    return 0;
}

int tambahDompet(char username[20], char nama_dompet[20], int saldo_awal) {
    FILE *file;
    char file_name[50];
    Wallet dompet, rDompet;
    bool dompetNameExists = false;

    dompet.id = getLastIDDompet(username) + 1;
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

int hapusDompet(char username[20], int id_dompet) {
    FILE *file;
    char file_name[50];
    Wallet rDompet;
    bool dompetFound = false;

    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);
    file = fopen(file_name, "rb+");

    if (file == NULL) {
        printf("\nGagal membuka file dompet\n");
        return 1;
    }

    while (fread(&rDompet, sizeof(struct Wallet), 1, file) == 1) {
        if (rDompet.id == id_dompet) {
            dompetFound = true;
            printf("\nDompet %s berhasil dihapus\n", getNamaDompet(username, id_dompet));

            // Menggeser posisi file untuk menimpa data dompet yang akan dihapus
            long position = ftell(file) - sizeof(struct Wallet);
            fseek(file, position, SEEK_SET);

            // Menulis data kosong untuk menghapus dompet
            Wallet emptyDompet = {id_dompet, "", 0};
            fwrite(&emptyDompet, sizeof(struct Wallet), 1, file);

            fclose(file);
            return 0;
        }
    }

    if (!dompetFound) {
        printf("\nDompet tidak ditemukan\n", id_dompet);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 1;
}

int ubahNamaDompet(char username[20], int id_dompet, char namabaru[20]) {
    FILE *file;
    char file_name[50];
    Wallet rDompet;
    bool dompetFound = false;
    char namalama[21];
    strcpy(namalama, getNamaDompet(username, id_dompet));

    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);
    file = fopen(file_name, "rb+");

    if (file == NULL) {
        printf("\nGagal membuka file dompet\n");
        return 1;
    }

    while (fread(&rDompet, sizeof(struct Wallet), 1, file) == 1) {
        if (strcmp(rDompet.nama_dompet, namabaru) == 0) {
            printf("\nNama dompet \"%s\" sudah ada\n", namabaru);
            fclose(file);
            return 1;
        }
    }

    fseek(file, 0, SEEK_SET);

    while (fread(&rDompet, sizeof(struct Wallet), 1, file) == 1) {
        if (rDompet.id == id_dompet) {
            dompetFound = true;
            printf("\nDompet \"%s\" berhasil diubah nama menjadi \"%s\"\n", namalama, namabaru);

            // Menggeser posisi file untuk menimpa data dompet yang akan diubah namanya
            long position = ftell(file) - sizeof(struct Wallet);
            fseek(file, position, SEEK_SET);

            // Ubah nama dompet
            Wallet editDompet = {id_dompet};
            strcpy(editDompet.nama_dompet, namabaru);
            editDompet.saldo = getSaldoDompet(username, id_dompet);
            fwrite(&editDompet, sizeof(struct Wallet), 1, file);

            fclose(file);
            return 0;
        }
    }

    if (!dompetFound) {
        printf("\nDompet tidak ditemukan\n", id_dompet);
        fclose(file);
        return 1;
    }

    fclose(file);
    return 1;
}
