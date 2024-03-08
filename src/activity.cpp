#include "activity.h"

#include "common.h"
#include "menu.h"
#include "wallet.h"

// Nama-nama bulan
const char *namaBulan[] = {
    "Januari", "Februari", "Maret", "April", "Mei", "Juni",
    "Juli", "Agustus", "September", "Oktober", "November", "Desember"};

// Nama-nama hari
const char *namaHari[] = {
    "Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu"};

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

int catatPengeluaran(char username[20], char kategori[20], int iddompet, int nominal, time_t waktu) {
    FILE *file;
    char file_name[50];
    struct Activity act;

    // Aktivitas
    act.id = getLastIDActivity(username) + 1;
    time_t rawtime;
    if (waktu == 0) {
        // saat ini
        act.waktu = time(&rawtime);
    } else {
        act.waktu = waktu;
    }
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

int catatPemasukan(char username[20], char kategori[20], int iddompet, int nominal, time_t waktu) {
    FILE *file;
    char file_name[50];
    struct Activity act;

    // Aktivitas
    act.id = getLastIDActivity(username) + 1;
    time_t rawtime;
    if (waktu == 0) {
        // saat ini
        act.waktu = time(&rawtime);
    } else {
        act.waktu = waktu;
    }
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
    char key;
    do {
        clearScreen();
        gotoxy(1, 1);
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

        printf("\033[1mRekap Hari Ini\033[0m (%s, %02d %s %04d)\n", namaHari[localTime->tm_wday], localTime->tm_mday, namaBulan[localTime->tm_mon], localTime->tm_year + 1900);
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
                    printf("Waktu\t: %02d:%02d:%02d %s, %02d %s %04d\n", localtime(&act.waktu)->tm_hour, localtime(&act.waktu)->tm_min, localtime(&act.waktu)->tm_sec, namaHari[localtime(&act.waktu)->tm_wday], localtime(&act.waktu)->tm_mday, namaBulan[localtime(&act.waktu)->tm_mon], localtime(&act.waktu)->tm_year + 1900);
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
        printf("Tekan ESC untuk kembali");
        key = getch();
    } while (key != 27);

    if (key == 27) {
        tampilMenuRekap(username);
    }
}

void getBulanan(char username[20]) {
    char key;
    do {
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
            if (localTime->tm_mon == localtime(&act.waktu)->tm_mon &&
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

        printf("\033[1mRekap Bulan Ini\033[0m (%s %04d)\n", namaBulan[localTime->tm_mon], localTime->tm_year + 1900);
        printf("Total Pemasukan Bulan Ini : \033[1;32m");
        formatRupiah(totalpemasukan);
        printf("\033[0m\n");
        printf("Total Pengeluaran Bulan Ini : \033[1;31m");
        formatRupiah(totalpengeluaran);
        printf("\033[0m\n");
        printf("----------------------------------------------\n");

        // FSEEK KEmbali ke 0
        fseek(file, 0, SEEK_SET);
        // tampil rekap
        while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
            if (localTime->tm_mon == localtime(&act.waktu)->tm_mon &&
                localTime->tm_year == localtime(&act.waktu)->tm_year) {
                if (strcmp(act.jenis, "Transfer") != 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0) {
                    printf("Waktu\t: %02d:%02d:%02d %s, %02d %s %04d\n", localtime(&act.waktu)->tm_hour, localtime(&act.waktu)->tm_min, localtime(&act.waktu)->tm_sec, namaHari[localtime(&act.waktu)->tm_wday], localtime(&act.waktu)->tm_mday, namaBulan[localtime(&act.waktu)->tm_mon], localtime(&act.waktu)->tm_year + 1900);
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
        printf("Tekan ESC untuk kembali");
        key = getch();
    } while (key != 27);

    if (key == 27) {
        tampilMenuRekap(username);
    }
}

void getMingguan(char username[20]) {
    char key;
    do {
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
            // Menghitung minggu aktivitas
            int activityWeek = localtime(&act.waktu)->tm_yday / 7;

            // Memeriksa jika aktivitas berada dalam minggu ini
            if (localTime->tm_year == localtime(&act.waktu)->tm_year && activityWeek == localtime(&act.waktu)->tm_yday / 7) {
                if (strcmp(act.jenis, "Transfer") != 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0) {
                    if (strcmp(act.jenis, "Pemasukan") == 0) {
                        totalpemasukan += act.nominal;
                    } else if (strcmp(act.jenis, "Pengeluaran") == 0) {
                        totalpengeluaran += act.nominal;
                    }
                }
            }
        }

        printf("\033[1mRekap Minggu Ini\033[0m (Minggu %d, %04d)\n", localTime->tm_yday / 7, localTime->tm_year + 1900);
        printf("Total Pemasukan Minggu Ini : \033[1;32m");
        formatRupiah(totalpemasukan);
        printf("\033[0m\n");
        printf("Total Pengeluaran Minggu Ini : \033[1;31m");
        formatRupiah(totalpengeluaran);
        printf("\033[0m\n");
        printf("----------------------------------------------\n");

        // FSEEK KEmbali ke 0
        fseek(file, 0, SEEK_SET);

        // tampil rekap
        while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
            // Menghitung minggu aktivitas
            int activityWeek = localtime(&act.waktu)->tm_yday / 7;

            // Memeriksa jika aktivitas berada dalam minggu ini
            if (localTime->tm_year == localtime(&act.waktu)->tm_year && activityWeek == localtime(&act.waktu)->tm_yday / 7) {
                if (strcmp(act.jenis, "Transfer") != 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0) {
                    printf("Waktu\t: %02d:%02d:%02d %s, %02d %s %04d\n", localtime(&act.waktu)->tm_hour, localtime(&act.waktu)->tm_min, localtime(&act.waktu)->tm_sec, namaHari[localtime(&act.waktu)->tm_wday], localtime(&act.waktu)->tm_mday, namaBulan[localtime(&act.waktu)->tm_mon], localtime(&act.waktu)->tm_year + 1900);
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
        printf("Tekan ESC untuk kembali");
        key = getch();
    } while (key != 27);

    if (key == 27) {
        tampilMenuRekap(username);
    }
}

void getSemuaPengeluaran(char username[20]) {
    char key;
    do {
        clearScreen();
        char file_name[50];
        sprintf(file_name, "data\\activities\\activity_%s.dat", username);

        int totalpengeluaran = 0;

        int n = 0;

        FILE *file = fopen(file_name, "rb");
        if (file == NULL) {
            printf("\nGagal membuka file                          \n");
            exit(1);
        }

        printf("\033[1mRekap Semua Pengeluaran\033[0m\n");

        // Tampil rekap semua pengeluaran
        struct Activity act;
        while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
            if (strcmp(act.jenis, "Transfer") != 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0 &&
                strcmp(act.jenis, "Pengeluaran") == 0) {
                totalpengeluaran += act.nominal;
            }
        }

        printf("Total Pengeluaran : \033[1;31m");
        formatRupiah(totalpengeluaran);
        printf("\033[0m\n");
        printf("----------------------------------------------\n");

        fseek(file, 0, SEEK_SET);
        while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
            if (strcmp(act.jenis, "Transfer") != 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0 &&
                strcmp(act.jenis, "Pengeluaran") == 0) {
                printf("Waktu\t: %02d:%02d:%02d %s, %02d %s %04d\n", localtime(&act.waktu)->tm_hour, localtime(&act.waktu)->tm_min, localtime(&act.waktu)->tm_sec, namaHari[localtime(&act.waktu)->tm_wday], localtime(&act.waktu)->tm_mday, namaBulan[localtime(&act.waktu)->tm_mon], localtime(&act.waktu)->tm_year + 1900);
                printf("Jenis\t: \033[1;31m%s\033[0m\n", act.jenis);
                printf("Kategori: %s\n", act.kategori);
                printf("Nominal\t: ");
                formatRupiah(act.nominal);
                printf("\nDompet\t: %s\n", getNamaDompet(username, act.id_dompet));
                printf("----------------------------------------------\n");
                n++;
            }
        }

        fclose(file);

        printf("Tekan ESC untuk kembali");
        key = getch();
    } while (key != 27);

    if (key == 27) {
        tampilMenuRekap(username);
    }
}

void getSemuaPemasukan(char username[20]) {
    char key;
    do {
        clearScreen();
        char file_name[50];
        sprintf(file_name, "data\\activities\\activity_%s.dat", username);

        int totalpemasukan = 0;

        int n = 0;

        FILE *file = fopen(file_name, "rb");
        if (file == NULL) {
            printf("\nGagal membuka file                          \n");
            exit(1);
        }

        printf("\033[1mRekap Semua Pemasukan\033[0m\n");

        // Tampil rekap semua pemasukan
        struct Activity act;
        while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
            if (strcmp(act.jenis, "Transfer") != 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0 &&
                strcmp(act.jenis, "Pemasukan") == 0) {
                totalpemasukan += act.nominal;
            }
        }

        printf("Total Pemasukan : \033[1;32m");
        formatRupiah(totalpemasukan);
        printf("\033[0m\n");
        printf("----------------------------------------------\n");

        fseek(file, 0, SEEK_SET);
        while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
            if (strcmp(act.jenis, "Transfer") != 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0 &&
                strcmp(act.jenis, "Pemasukan") == 0) {
                printf("Waktu\t: %02d:%02d:%02d %s, %02d %s %04d\n", localtime(&act.waktu)->tm_hour, localtime(&act.waktu)->tm_min, localtime(&act.waktu)->tm_sec, namaHari[localtime(&act.waktu)->tm_wday], localtime(&act.waktu)->tm_mday, namaBulan[localtime(&act.waktu)->tm_mon], localtime(&act.waktu)->tm_year + 1900);
                printf("Jenis\t: \033[1;32m%s\033[0m\n", act.jenis);
                printf("Kategori: %s\n", act.kategori);
                printf("Nominal\t: ");
                formatRupiah(act.nominal);
                printf("\nDompet\t: %s\n", getNamaDompet(username, act.id_dompet));
                printf("----------------------------------------------\n");
                n++;
            }
        }

        fclose(file);

        printf("Tekan ESC untuk kembali");
        key = getch();
    } while (key != 27);

    if (key == 27) {
        tampilMenuRekap(username);
    }
}

int getPemasukanBulanan(char username[20]) {
    char file_name[50];
    sprintf(file_name, "data\\activities\\activity_%s.dat", username);

    int totalpemasukan = 0;

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
        if (localTime->tm_mon == localtime(&act.waktu)->tm_mon &&
            localTime->tm_year == localtime(&act.waktu)->tm_year) {
            if (strcmp(act.jenis, "Pemasukan") == 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0) {
                totalpemasukan += act.nominal;
            }
        }
    }

    fclose(file);

    return totalpemasukan;
}

int getPengeluaranBulanan(char username[20]) {
    char file_name[50];
    sprintf(file_name, "data\\activities\\activity_%s.dat", username);

    int totalpengeluaran = 0;

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
        if (localTime->tm_mon == localtime(&act.waktu)->tm_mon &&
            localTime->tm_year == localtime(&act.waktu)->tm_year) {
            if (strcmp(act.jenis, "Pengeluaran") == 0 && strcmp(getNamaDompet(username, act.id_dompet), "") != 0) {
                totalpengeluaran += act.nominal;
            }
        }
    }

    fclose(file);

    return totalpengeluaran;
}