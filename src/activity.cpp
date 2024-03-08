#include "activity.h"

#include "common.h"
#include "wallet.h"

// buat file activity
void buatActivity(char username[20]) {
    FILE *file;
    char file_name[50];

    sprintf(file_name, "data\\activities\\activity_%s.dat", username);
    file = fopen(file_name, "wb");

    fclose(file);
}

int getLastIDActivity(char username[20]) {
    char file_name[50];
    int id = -1;  // Initialize id to a default value
    sprintf(file_name, "data\\activities\\activity_%s.dat", username);

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("\nGagal membuka file aktivitas                                        \n");
        return -1;  // Return an error code or handle the error appropriately
    }

    struct Activity act;
    while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
        id = act.id;
    }

    fclose(file);
    return id;
}

int catatPengeluaran(char username[20], char kategori[20], int iddompet, int nominal) {
    FILE *file;
    char file_name[50];
    struct Activity act;

    // Aktivitas
    act.id = getLastIDActivity(username) + 1;
    time_t rawtime;
    act.waktu = time(&rawtime);
    strcpy(act.jenis, "Pengeluaran");
    strcpy(act.kategori, kategori);
    act.nominal = nominal;
    act.id_dompet = iddompet;

    sprintf(file_name, "data\\activities\\activity_%s.dat", username);

    file = fopen(file_name, "ab+");
    if (file == NULL) {
        printf("\nGagal membuka atau membuat file aktivitas                                    \n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    fwrite(&act, sizeof(struct Activity), 1, file);
    fclose(file);

    // Kurangi saldo
    kurangiSaldo(username, iddompet, nominal);

    printf("\nBerhasil mencatat pengeluaran                                    \n");
    return 0;
}

int catatPemasukan(char username[20], char kategori[20], int iddompet, int nominal) {
    FILE *file;
    char file_name[50];
    struct Activity act;

    // Aktivitas
    act.id = getLastIDActivity(username) + 1;
    time_t rawtime;
    act.waktu = time(&rawtime);
    strcpy(act.jenis, "Pemasukan");
    strcpy(act.kategori, kategori);
    act.nominal = nominal;
    act.id_dompet = iddompet;

    sprintf(file_name, "data\\activities\\activity_%s.dat", username);

    file = fopen(file_name, "ab+");
    if (file == NULL) {
        printf("\nGagal membuka atau membuat file aktivitas                                       \n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    fwrite(&act, sizeof(struct Activity), 1, file);
    fclose(file);

    // Tambah saldo
    tambahSaldo(username, iddompet, nominal);

    printf("\nBerhasil mencatat pemasukan                                       \n");
    return 0;
}

int catatTransfer(char username[20], int id_dompet_asal, int id_dompet_tujuan, int nominal) {
    FILE *file;
    char file_name[50];
    struct Activity act;

    // Aktivitas
    act.id = getLastIDActivity(username) + 1;
    time_t rawtime;
    act.waktu = time(&rawtime);
    strcpy(act.jenis, "Transfer");
    sprintf(act.kategori, "%d", id_dompet_tujuan);
    act.nominal = nominal;
    act.id_dompet = id_dompet_asal;

    sprintf(file_name, "data\\activities\\activity_%s.dat", username);

    file = fopen(file_name, "ab+");
    if (file == NULL) {
        printf("\nGagal membuka atau membuat file aktivitas                                          \n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    fwrite(&act, sizeof(struct Activity), 1, file);
    fclose(file);

    // Transfer
    kurangiSaldo(username, id_dompet_asal, nominal);
    tambahSaldo(username, id_dompet_tujuan, nominal);

    printf("\nBerhasil mencatat transer saldo                                           \n");
    return 0;
}

void getHarian(char username[20]) {
    clearScreen();
    char file_name[50];
    sprintf(file_name, "data\\activities\\activity_%s.dat", username);

    int totalpemasukan = 0, totalpengeluaran = 0;

    int n = 0;

    FILE *file = fopen(file_name, "rb");
    if (file == NULL) {
        printf("\nGagal membuka file                          \n");
        exit(1);
    }

    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);

    // hitung total
    struct Activity act;
    while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
        if (localTime->tm_mday == localtime(&act.waktu)->tm_mday &&
            localTime->tm_mon == localtime(&act.waktu)->tm_mon &&
            localTime->tm_year == localtime(&act.waktu)->tm_year) {
            if (strcmp(act.jenis, "Transfer") != 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0) {
                if (strcmp(act.jenis, "Pemasukan") == 0) {
                    totalpemasukan += act.nominal;
                } else if (strcmp(act.jenis, "Pengeluaran") == 0) {
                    totalpengeluaran += act.nominal;
                }
            }
        }
    }

    printf("\033[1mRekap Hari Ini\033[0m (%02d-%02d-%04d)\n", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
    printf("Total Pemasukan Hari Ini : \033[1;32m");
    formatRupiah(totalpemasukan);
    printf("\033[0m\n");
    printf("Total Pengeluaran Hari Ini : \033[1;31m");
    formatRupiah(totalpengeluaran);
    printf("\033[0m\n");
    printf("----------------------------------------------\n");

    // FSEEK KEmbali ke 0
    fseek(file, 0, SEEK_SET);
    // tampil rekap
    while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
        if (localTime->tm_mday == localtime(&act.waktu)->tm_mday &&
            localTime->tm_mon == localtime(&act.waktu)->tm_mon &&
            localTime->tm_year == localtime(&act.waktu)->tm_year) {
            if (strcmp(act.jenis, "Transfer") != 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0) {
                printf("Waktu\t: %s", asctime(localtime(&act.waktu)));
                if (strcmp(act.jenis, "Pemasukan") == 0) {
                    printf("Jenis\t: \033[1;32m%s\033[0m\n", act.jenis);
                } else if (strcmp(act.jenis, "Pengeluaran") == 0) {
                    printf("Jenis\t: \033[1;31m%s\033[0m\n", act.jenis);
                }
                printf("Kategori: %s\n", act.kategori);
                printf("Nominal\t: ");
                formatRupiah(act.nominal);
                printf("\nDompet\t: %s\n", getNamaDompet(username, act.id_dompet));
                printf("----------------------------------------------\n");
            }
        }
    }

    fclose(file);
}