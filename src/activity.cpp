#include "activity.h"

// buat file activity
void buatActivity(char username[20]) {
    FILE *file;
    char file_name[50];

    sprintf(file_name, "data\\activities\\activity_%s.dat", username);
    file = fopen(file_name, "wb");

    fclose(file);
}

// catat pemasukan
// catat pengeluaran
// rekap bulanan
// rekap mingguan
// rekap harian