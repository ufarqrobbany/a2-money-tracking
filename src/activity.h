#include <stdio.h>
#include <string.h>
#include <time.h>

struct Activity {
    int id;
    time_t waktu;
    char jenis[20];  // Pemasukan, Pengeluaran, Transfer
    char kategori[20];
    int nominal;
    int id_dompet;
};

void buatActivity(char username[20]);
int getKategori(char username[20], int jenis);
int catatPengeluaran(char username[20], char kategori[20], int iddompet, int nominal);