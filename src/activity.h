#include <stdio.h>
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