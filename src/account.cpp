#include "account.h"

#include "activity.h"
#include "wallet.h"

int login(char username[20], char password[20]) {
    FILE *file = fopen("data\\akun.dat", "rb");
    struct Account akun;
    bool usernameExists = false;
    bool passwordValid = false;

    while (fread(&akun, sizeof(struct Account), 1, file) == 1) {
        if (strcmp(akun.username, username) == 0) {
            usernameExists = true;
            if (strcmp(akun.password, password) == 0) {
                passwordValid = true;
                printf("\nBerhasil login                    \n");
                fclose(file);
                return 0;
            }
        }
    }

    fclose(file);

    if (!usernameExists) {
        printf("\nUsername tidak ditemukan                   \n");
        return 1;
    }

    if (!passwordValid) {
        printf("\nPassword salah                                 \n");
        return 1;
    }

    return 1;
}

int daftar(char nama[20], char username[20], char password[20], char re_password[20]) {
    if (strcmp(password, re_password) != 0) {
        printf("\nPassword tidak sama                       \n");
        return 1;
    }

    FILE *file = fopen("data\\akun.dat", "ab+");

    struct Account akun;
    bool usernameExists = false;

    while (fread(&akun, sizeof(struct Account), 1, file) == 1) {
        if (strcmp(akun.username, username) == 0) {
            usernameExists = true;
            printf("\nUsername sudah ada                    \n");
            fclose(file);  // Close the file on error
            return 1;
        }
    }

    if (!usernameExists) {
        strncpy(akun.nama, nama, sizeof(akun.nama) - 1);
        strncpy(akun.username, username, sizeof(akun.username) - 1);
        strncpy(akun.password, password, sizeof(akun.password) - 1);

        fseek(file, 0, SEEK_END);

        fwrite(&akun, sizeof(struct Account), 1, file);
        printf("\nBerhasil buat akun                          \n");
        fclose(file);

        buatDompetAwal(username);
        buatActivity(username);

        return 0;
    }

    fclose(file);
    return 1;
}

const char *getNamaUser(const char username[20]) {
    FILE *file = fopen("data\\akun.dat", "rb");

    if (file == NULL) {
        printf("Gagal membuka file akun\n");
        return NULL;  // Tidak dapat membuka file
    }

    static char nama[50];  // asumsikan panjang nama maksimum 49 karakter

    struct Account akun;

    while (fread(&akun, sizeof(struct Account), 1, file) == 1) {
        if (strcmp(akun.username, username) == 0) {
            fclose(file);
            strncpy(nama, akun.nama, sizeof(nama) - 1);
            nama[sizeof(nama) - 1] = '\0';  // Pastikan null-terminated
            return nama;
        }
    }

    fclose(file);
    return NULL;  // Username tidak ditemukan
}
