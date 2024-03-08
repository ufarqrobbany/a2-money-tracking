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
int getLastIDActivity(char username[20]);
int catatPengeluaran(char username[20], char kategori[20], int iddompet, int nominal);
int catatPemasukan(char username[20], char kategori[20], int iddompet, int nominal);
int catatTransfer(char username[20], int id_dompet_asal, int id_dompet_tujuan, int nominal);
void getHarian(char username[20]);