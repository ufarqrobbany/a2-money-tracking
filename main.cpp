#include <stdio.h>
#include <stdlib.h>

#include "src/data.h"

int main() {
    int menu = 0;
    // buka data tersimpan di file
    system("cls");

    while (menu != 3) {
        printf("\nMONEY TRACKING APP\n");
        printf("Saldo: \n");
        printf("Pengeluaran Bulan Ini: \n");
        printf("========================== \n");
        printf("1. Catat\n");
        printf("2. Lihat Rekap\n");
        printf("3. Keluar\n");
        printf("ketikkan pilihan anda :");
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                int menucatat;
                system("cls");
                printf("1. catat pengeluaran\n");
                printf("2. catat pemasukkan\n");
                printf("3. kembali ke manu awal\n");
                printf("ketikkan pilihan anda:");
                scanf("%d", &menucatat);
                switch (menucatat) {
                    case 1:
                        // panggil prosedur catat pengeluaran
                        system("cls");
                        break;
                    case 2:
                        // panggil prosedur catat pemasukan
                        system("cls");
                        break;
                    case 3:
                        system("cls");
                        break;
                }
                break;
            case 2:
                int menurekap;
                system("cls");
                printf("1. Tampil rekap harian\n");
                printf("2. Tampil rekap mingguan\n");
                printf("3. Tampil rekap bulanan\n");
                printf("4. Tampil semua pemasukkan\n");
                printf("5. Tampil semua pengeluaran\n");
                printf("ketikkan pilihan anda :");
                scanf("%d", &menurekap);
                switch (menurekap) {
                    case 1:
                        // panggil prosedur tampil rekap harian
                        system("cls");
                        break;
                    case 2:
                        // panggil prosedur tampil rekap mingguan
                        system("cls");
                        break;
                    case 3:
                        // panggil prosedur tampil rekap bulanan
                        system("cls");
                        break;
                    case 4:
                        // panggil prosedur tampil rekap pemasukkan
                        system("cls");
                        break;
                    case 5:
                        // panggil prosedur tampil rekap pengeluaran
                        system("cls");
                        break;
                }
                break;
            case 3:
                // keluar
                exit(1);
        }
    }

    return 0;
}
