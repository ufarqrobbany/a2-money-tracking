#include "activity.h"

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
        printf("\nGagal membuka file aktivitas\n");
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
        printf("\nGagal membuka atau membuat file aktivitas\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    fwrite(&act, sizeof(struct Activity), 1, file);
    fclose(file);

    // Kurangi saldo
    kurangiSaldo(username, iddompet, nominal);

    printf("\nBerhasil mencatat pengeluaran\n");
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
        printf("\nGagal membuka atau membuat file aktivitas\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    fwrite(&act, sizeof(struct Activity), 1, file);
    fclose(file);

    // Tambah saldo
    tambahSaldo(username, iddompet, nominal);

    printf("\nBerhasil mencatat pemasukan\n");
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
        printf("\nGagal membuka atau membuat file aktivitas\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    fwrite(&act, sizeof(struct Activity), 1, file);
    fclose(file);

    // Transfer
    kurangiSaldo(username, id_dompet_asal, nominal);
    tambahSaldo(username, id_dompet_tujuan, nominal);

    printf("\nBerhasil mencatat transer saldo\n");
    return 0;
}