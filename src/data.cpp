#include "data.h"

#include <stdio.h>

#define MAX_DATA 100

void catatData(struct Data data) {
    FILE *file = fopen("data.dat", "wb");

    if (file != NULL) {
        fwrite(&data, sizeof(struct Data), 1, file);
        fclose(file);
    } else {
        printf("Gagal membuka file untuk penyimpanan data.\n");
    }
}

// Fungsi untuk menghitung sisa saldo
int HitungSisaSaldo(struct Data data[], int n) {
    int saldo = 0;
    for (int i = 0; i < n; i++) {
        saldo += data[i].harga;
    }
    return saldo;
}

// Fungsi untuk menghitung rekap mingguan
void HitungRekapMingguan(struct Data data[], int n, int target_week, int target_month) {
    for (int i = 0; i < n; i++) {
        struct tm *date_info;
        date_info = localtime(&data[i].tanggal);
        
        // Mengecek apakah data transaksi berada di minggu dan bulan yang diinginkan
        int transaction_week = (date_info->tm_mday + 6 - date_info->tm_wday) / 7;
        int transaction_month = date_info->tm_mon + 1;
        
        if (transaction_week == target_week && transaction_month == target_month) {
            printf("Tanggal: %d/%d/%d\n", date_info->tm_mday, transaction_month, date_info->tm_year + 1900);
            printf("Jenis: %s\n", data[i].jenis);
            printf("Harga: Rp %d\n", data[i].harga);
            printf("\n");
        }
    }
}

// Fungsi untuk memuat data dari file .dat
int LoadData(struct Data data[], const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return 0;
    }

    int n = 0;
    while (fread(&data[n], sizeof(struct Data), 1, file) == 1) {
        n++;
    }

    fclose(file);
    return n;
}