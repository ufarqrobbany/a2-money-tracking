#include "menu.h"

#include "account.h"
#include "common.h"
#include "wallet.h"

void tampilMenuAwal() {
    int current_selection = 1;
    char key;

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("====================\n");

    // isi
    do {
        gotoxy(1, 3);
        printf("%c Masuk\n", (current_selection == 1) ? 254 : ' ');
        printf("%c Daftar\n", (current_selection == 2) ? 254 : ' ');
        printf("%c Keluar\n", (current_selection == 3) ? 254 : ' ');

        // navigasi menu
        key = getch();

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 3)) {
            current_selection += 1;
        } else if (key == 13) {
            switch (current_selection) {
                case 1:
                    tampilMenuLogin();
                    break;
                case 2:
                    tampilMenuDaftar();
                    break;
                default:
                    break;
            }
        }
    } while (key != 13);
}

void tampilMenuLogin() {
    char username[21], password[21], key;
    int n = 0, p = 1, status = 1;

    do {
        clearScreen();
        // print header
        printf("MONEY TRACKING APP\n");
        printf("Login\n");
        printf("====================\n");
        printf("Username: \n");
        printf("Password: ");

        gotoxy(11, 4);

        do {
            key = getch();

            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 20)) {
                if (p == 1) {
                    username[n] = key;
                } else {
                    password[n] = key;
                }
                n++;
                printf("%c", key);
                gotoxy(11 + n, 3 + p);
            } else if (key == 13) {  // Enter key
                if (n > 0) {
                    if (p == 1) {
                        username[n] = '\0';
                        p = 2;
                        n = 0;
                        gotoxy(11 + n, 3 + p);
                    } else {
                        password[n] = '\0';
                        p = 1;
                        n = 0;
                        break;
                    }
                }
            } else if (key == 8) {  // Backspace key
                if (n > 0) {
                    printf("\b \b");
                    n--;
                }
            }
        } while (key != 27);  // ESC key

        if (key == 13) {
            status = login(username, password);
            getch();
        }
    } while (status == 1 && key != 27);

    if (status == 0) {
        tampilMenuUtama(username);
    }

    if (key == 27) {
        tampilMenuAwal();
    }
}

void tampilMenuDaftar() {
    char name[21], username[21], password[21], re_password[21], key;
    int n = 0, p = 1, status = 1;

    do {
        clearScreen();
        // print header
        printf("MONEY TRACKING APP\n");
        printf("Daftar Akun\n");
        printf("====================\n");
        printf("Nama\t\t: \n");
        printf("Username\t: \n");
        printf("Password\t: \n");
        printf("Ulangi Password\t: ");

        gotoxy(19, 4);

        do {
            key = getch();

            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 20)) {
                if (p == 1) {
                    name[n] = key;
                } else if (p == 2) {
                    username[n] = key;
                } else if (p == 3) {
                    password[n] = key;
                } else {
                    re_password[n] = key;
                }
                n++;
                printf("%c", key);
                gotoxy(19 + n, 3 + p);
            } else if (key == 13) {  // Enter key
                if (n > 0) {
                    if (p == 1) {
                        name[n] = '\0';
                        p = 2;
                    } else if (p == 2) {
                        username[n] = '\0';
                        p = 3;
                    } else if (p == 3) {
                        password[n] = '\0';
                        p = 4;
                    } else {
                        re_password[n] = '\0';
                        p = 1;
                        n = 0;
                        break;
                    }
                    n = 0;
                    gotoxy(19 + n, 3 + p);
                }
            } else if (key == 8) {  // Backspace key
                if (n > 0) {
                    printf("\b \b");
                    n--;
                }
            }
        } while (key != 27);  // ESC key

        if (key == 13) {
            status = daftar(name, username, password, re_password);
            getch();
        }

    } while (status == 1 && key != 27);

    if (status == 0) {
        tampilMenuUtama(username);
    }

    if (key == 27) {
        tampilMenuAwal();
    }
}

void tampilMenuUtama(char username[20]) {
    int current_selection = 1;
    char key;

    // buka data tersimpan di file

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("User: %s\n", username);
    printf("====================\n");
    printf("Total Saldo: ");
    formatRupiah(getTotalSaldo(username));
    printf("\nPengeluaran Bulan Ini: \n");

    // isi
    do {
        gotoxy(1, 6);
        printf("%c Catat\n", (current_selection == 1) ? 254 : ' ');
        printf("%c Rekap\n", (current_selection == 2) ? 254 : ' ');
        printf("%c Dompet\n", (current_selection == 3) ? 254 : ' ');
        printf("%c keluar\n", (current_selection == 4) ? 254 : ' ');

        // navigasi menu
        key = getch();

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 4)) {
            current_selection += 1;
        } else if (key == 13) {
            switch (current_selection) {
                case 1:
                    tampilMenuCatat(username);
                    break;
                case 2:
                    tampilMenuRekap(username);
                    break;
                case 3:
                    tampilMenuDompet(username);
                    break;
                case 4:
                    exit(1);
                    break;
                default:
                    break;
            }
        }
    } while (key != 13);
}

void tampilMenuCatat(char username[20]) {
    int current_selection = 1;
    char key;

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("User: %s\n", username);
    printf("====================\n");

    // isi
    do {
        gotoxy(1, 4);
        printf("%c Catat Pengeluaran\n", (current_selection == 1) ? 254 : ' ');
        printf("%c Catat Pemasukan\n", (current_selection == 2) ? 254 : ' ');
        printf("%c Kembali\n", (current_selection == 3) ? 254 : ' ');

        // navigasi menu
        key = getch();

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 3)) {
            current_selection += 1;
        } else if (key == 13) {
            switch (current_selection) {
                case 1:
                    // panggil prosedur catat pengeluaran
                    break;
                case 2:
                    // panggil prosedur catat pemasukan
                    break;
                case 3:
                    tampilMenuUtama(username);
                    break;
                default:
                    break;
            }
        }
    } while (key != 13);
}

void tampilMenuRekap(char username[20]) {
    int current_selection = 1;
    char key;

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("User: %s\n", username);
    printf("====================\n");

    // isi
    do {
        gotoxy(1, 4);
        printf("%c Tampil Rekap Harian\n", (current_selection == 1) ? 254 : ' ');
        printf("%c Tampil Rekap Mingguan\n", (current_selection == 2) ? 254 : ' ');
        printf("%c Tampil Rekap Bulanan\n", (current_selection == 3) ? 254 : ' ');
        printf("%c Tampil Semua Pemasukan\n", (current_selection == 4) ? 254 : ' ');
        printf("%c Tampil Semua Pengeluaran\n", (current_selection == 5) ? 254 : ' ');
        printf("%c Kembali\n", (current_selection == 6) ? 254 : ' ');

        // navigasi menu
        key = getch();

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 6)) {
            current_selection += 1;
        } else if (key == 13) {
            switch (current_selection) {
                case 1:
                    // panggil prosedur tampil rekap harian
                    break;
                case 2:
                    // panggil prosedur tampil rekap mingguan
                    break;
                case 3:
                    // panggil prosedur tampil rekap bulanan
                    break;
                case 4:
                    // panggil prosedur tampil rekap pemasukkan
                    break;
                case 5:
                    // panggil prosedur tampil rekap pengeluaran
                    break;
                case 6:
                    tampilMenuUtama(username);
                    break;
                default:
                    break;
            }
        }
    } while (key != 13);
}

void tampilMenuDompet(char username[20]) {
    int current_selection = 1, jmlDompet = 0;
    char key;

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("User: %s\n", username);
    printf("====================\n");

    // tampil dompet
    jmlDompet = getDompet(username, true);
    printf("====================\n");

    // isi
    do {
        gotoxy(1, 4 + jmlDompet + 2);
        printf("%c Tambah dompet\n", (current_selection == 1) ? 254 : ' ');
        printf("%c Hapus dompet\n", (current_selection == 2) ? 254 : ' ');
        printf("%c Kembali\n", (current_selection == 3) ? 254 : ' ');

        // navigasi menu
        key = getch();

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 3)) {
            current_selection += 1;
        } else if (key == 13) {
            switch (current_selection) {
                case 1:
                    if (jmlDompet < 10) {
                        tampilMenuTambahDompet(username);
                    } else {
                        gotoxy(1, 9 + jmlDompet);
                        printf("Tidak bisa menambah dompet, maksimal 10 dompet dalam 1 akun");
                        key = 0;
                    }
                    break;
                case 2:
                    // panggil prosedur hapus dompet
                    if (jmlDompet > 1) {
                        tampilMenuHapusDompet(username);
                    } else {
                        gotoxy(1, 9 + jmlDompet);
                        printf("Tidak bisa menghapus dompet lagi, sisakan 1 dompet di akunmu");
                        key = 0;
                    }
                    break;
                case 3:
                    tampilMenuUtama(username);
                    break;
                default:
                    break;
            }
        }
    } while (key != 13);
}

void tampilMenuTambahDompet(char username[20]) {
    char namadompet[21], key, jmlDompet, saldoawal[20];
    int n = 0, p = 1, status = 1, saldo;

    do {
        clearScreen();
        // print header
        printf("MONEY TRACKING APP\n");
        printf("Login\n");
        printf("====================\n");

        // tampil dompet
        jmlDompet = getDompet(username, true);
        printf("====================\n");

        printf("Nama Dompet\t: \n");
        printf("Saldo Awal\t: \n");
        gotoxy(19, 4 + jmlDompet + 2);

        do {
            key = getch();

            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 20)) {
                if (p == 1) {
                    namadompet[n] = key;
                    n++;
                    printf("%c", key);
                    gotoxy(19 + n, 5 + p + jmlDompet);
                } else if ((p == 2) && (key >= '0' && key <= '9')) {
                    saldoawal[n] = key;
                    n++;
                    printf("%c", key);
                    gotoxy(19 + n, 5 + p + jmlDompet);
                }
            } else if (key == 13) {  // Enter key
                if (n > 0) {
                    if (p == 1) {
                        namadompet[n] = '\0';
                        p = 2;
                        n = 0;
                        gotoxy(19 + n, 5 + p + jmlDompet);
                    } else {
                        saldoawal[n] = '\0';
                        sscanf(saldoawal, "%d", &saldo);
                        p = 1;
                        n = 0;
                        break;
                    }
                }
            } else if (key == 8) {  // Backspace key
                if (n > 0) {
                    printf("\b \b");
                    n--;
                }
            }
        } while (key != 27);  // ESC key

        if (key == 13) {
            status = tambahDompet(username, namadompet, saldo);
            getch();
        }
    } while (status == 1 && key != 27);

    if (status == 0) {
        tampilMenuDompet(username);
    }

    if (key == 27) {
        tampilMenuDompet(username);
    }
}

void tampilMenuHapusDompet(char username[20]) {
    int current_selection = 1, jmlDompet = 0;
    char key;

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("User: %s\n", username);
    printf("====================\n");
    printf("Pilih dompet yang akan dihapus\n");

    // hitung dompet
    jmlDompet = getDompet(username, false);

    Wallet dom;
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");

    // isi
    do {
        int idKosong[100] = {}, kosong = 0;
        gotoxy(1, 5);
        while (fread(&dom, sizeof(struct Wallet), 1, file) == 1) {
            if (strcmp(dom.nama_dompet, "") != 0) {
                printf("%c %s, ", (current_selection == dom.id) ? 254 : ' ', dom.nama_dompet);
                formatRupiah(dom.saldo);
                printf("\n");
            } else {
                idKosong[kosong] = dom.id;
                kosong++;
            }
        }

        // navigasi menu
        key = getch();

        // Pindahkan posisi ke awal file
        fseek(file, 0, SEEK_SET);

        if ((key == 72) && (current_selection > 1)) {
            do {
                current_selection -= 1;
            } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection > 1));
            current_selection = (current_selection < 1) ? 1 : current_selection;  // Ensure it doesn't go below 1
        } else if ((key == 80) && (current_selection < getLastIDDompet(username))) {
            do {
                current_selection += 1;
            } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection < getLastIDDompet(username)));

            current_selection = (current_selection > getLastIDDompet(username)) ? getLastIDDompet(username) : current_selection;  // Ensure it doesn't exceed last ID
        } else if (key == 13) {
            fclose(file);
            tampilKonfirmasiHapusDompet(username, getNamaDompet(username, current_selection), current_selection);
        }
    } while (key != 13);
    fclose(file);
}

void tampilKonfirmasiHapusDompet(char username[20], char namadompet[20], int iddompet) {
    int current_selection = 1, status = 1;
    char key;

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("User: %s\n", username);
    printf("====================\n");
    printf("Yakin ingin menghapus dompet \"%s\"? Semua riwayat aktivitas pada dompet ini akan terhapus", namadompet);

    // isi
    do {
        gotoxy(1, 5);
        printf("%c Tidak, kembali\n", (current_selection == 1) ? 254 : ' ');
        printf("%c Yakin, hapus\n", (current_selection == 2) ? 254 : ' ');

        // navigasi menu
        key = getch();

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 2)) {
            current_selection += 1;
        } else if (key == 13) {
            switch (current_selection) {
                case 1:
                    // hapus dompet
                    tampilMenuDompet(username);
                    break;
                default:
                    status = hapusDompet(username, iddompet);
                    getch();
                    break;
            }
        }
    } while (key != 13);

    if (status == 0) {
        tampilMenuDompet(username);
    }
}