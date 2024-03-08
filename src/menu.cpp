#include "menu.h"

#include "account.h"
#include "activity.h"
#include "common.h"
#include "wallet.h"

void tampilMenuAwal() {
    int current_selection = 1;
    char key;

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Selamat Datang di Aplikasi Money Tracking App\n");
    printf("Catat dan kelola keuanganmu dengan mudah\n");
    printf("===================================================\n");

    // isi
    do {
        gotoxy(1, 6);
        printf("[%c] Masuk\n", (current_selection == 1) ? 254 : ' ');
        printf("[%c] Daftar\n", (current_selection == 2) ? 254 : ' ');
        printf("[\033[1;31m%c\033[0m] Keluar\n", (current_selection == 3) ? 254 : ' ');
        printf("===================================================\n");
        printf("Gunakan tombol panah untuk navigasi dan tekan Enter\n");
        gotoxy(1, 20);

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
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Masuk ke akunmu\n");
        printf("===================================================\n");
        printf("Username : \n");
        printf("Password : \n");
        printf("===================================================\n");
        printf("Tekan ESC untuk kembali");

        gotoxy(12, 5);

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
                gotoxy(12 + n, 4 + p);
            } else if (key == 13) {  // Enter key
                if (n > 0) {
                    if (p == 1) {
                        username[n] = '\0';
                        p = 2;
                        n = 0;
                        gotoxy(12 + n, 4 + p);
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
            gotoxy(1, 7);
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
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Buat akun baru\n");
        printf("===================================================\n");
        printf("Nama\t\t: \n");
        printf("Username\t: \n");
        printf("Password\t: \n");
        printf("Ulangi Password\t: \n");
        printf("===================================================\n");
        printf("Tekan ESC untuk kembali");

        gotoxy(19, 5);

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
                gotoxy(19 + n, 4 + p);
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
                    gotoxy(19 + n, 4 + p);
                }
            } else if (key == 8) {  // Backspace key
                if (n > 0) {
                    printf("\b \b");
                    n--;
                }
            }
        } while (key != 27);  // ESC key

        if (key == 13) {
            gotoxy(1, 9);
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

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");
    printf("Total Saldo\t\t: ");
    formatRupiah(getTotalSaldo(username));
    printf("\nPemasukan Bulan Ini\t: ");
    formatRupiah(getPemasukanBulanan(username));
    printf("\nPengeluaran Bulan Ini\t: ");
    formatRupiah(getPengeluaranBulanan(username));
    printf("\n===================================================\n");

    // isi
    do {
        gotoxy(1, 9);
        printf("[%c] Catat\n", (current_selection == 1) ? 254 : ' ');
        printf("[%c] Rekap\n", (current_selection == 2) ? 254 : ' ');
        printf("[%c] Dompet\n", (current_selection == 3) ? 254 : ' ');
        printf("[\033[1;31m%c\033[0m] Keluar\n", (current_selection == 4) ? 254 : ' ');
        printf("===================================================\n");
        printf("Gunakan tombol panah untuk navigasi dan tekan Enter\n");

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
    int current_selection = 1, status = 1;
    char key;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");

        // isi
        do {
            gotoxy(1, 5);
            printf("[%c] Catat Pengeluaran\n", (current_selection == 1) ? 254 : ' ');
            printf("[%c] Catat Pemasukan\n", (current_selection == 2) ? 254 : ' ');
            printf("[%c] Catat Transfer\n", (current_selection == 3) ? 254 : ' ');
            printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == 4) ? 254 : ' ');
            printf("===================================================\n");
            printf("Gunakan tombol panah untuk navigasi dan tekan Enter\n");

            // navigasi menu
            key = getch();

            if ((key == 72) && (current_selection > 1)) {
                current_selection -= 1;
            } else if ((key == 80) && (current_selection < 4)) {
                current_selection += 1;
            } else if (key == 13) {
                switch (current_selection) {
                    case 1:
                        // panggil prosedur catat pengeluaran
                        tampilMenuCatatPengeluaran(username);
                        status = 0;
                        break;
                    case 2:
                        // panggil prosedur catat pemasukan
                        tampilMenuCatatPemasukan(username);
                        status = 0;
                        break;
                    case 3:
                        // jika dompet lebih dari 1
                        if (getDompet(username, false) > 1) {
                            tampilMenuCatatTransfer(username, 1, -1, "Catat Transfer Saldo antar Dompet");
                            status = 0;
                        } else {
                            printf("\nDompet kamu hanya ada 1, tambahkan dompet baru untuk transfer ke dompet tujuan\n");
                            getch();
                            status = 1;
                        }
                        break;
                    case 4:
                        tampilMenuUtama(username);
                        status = 0;
                        break;
                    default:
                        break;
                }
            }
        } while (key != 13);
    } while (status == 1);
}

void tampilMenuCatatPengeluaran(char username[20]) {
    char key, nominalstr[20];
    int n = 0, status = 1, nominal = 0;

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");
    printf("Catat pengeluaran\n");
    printf("===================================================\n");
    printf("Nominal : ");
    formatRupiah(nominal);
    printf("\n");
    printf("===================================================\n");
    printf("Tekan ESC untuk kembali\n");
    gotoxy(13, 7);

    do {
        key = getch();

        if (((key >= '0' && key <= '9')) && (n < 9)) {
            if (!(n == 0 && key == '0')) {
                nominalstr[n] = key;
                n++;
                sscanf(nominalstr, "%d", &nominal);

                gotoxy(11, 7);
                printf("                  ");
                gotoxy(11, 7);
                formatRupiah(nominal);
                gotoxy(11 + getLengthFormatRupiah(nominal) + 2, 7);
            }
        } else if (key == 13) {  // Enter key
            if (n > 0) {
                nominalstr[n] = '\0';
                sscanf(nominalstr, "%d", &nominal);
                n = 0;
                break;
            }
        } else if (key == 8) {  // Backspace key
            if (n > 0) {
                n--;

                nominalstr[n] = '\0';
                if (nominalstr[0] == '\0') {
                    nominal = 0;
                } else {
                    sscanf(nominalstr, "%d", &nominal);
                }

                gotoxy(11, 7);
                printf("                  ");
                gotoxy(11, 7);
                formatRupiah(nominal);
                gotoxy(11 + getLengthFormatRupiah(nominal) + 2, 7);
            }
        }
    } while (key != 27);  // ESC key

    if (key == 13) {
        tampilPilihKategori(username, 1, nominal);
    }

    if (key == 27) {
        tampilMenuCatat(username);
    }
}

void tampilMenuCatatPemasukan(char username[20]) {
    char key, nominalstr[20];
    int n = 0, status = 1, nominal = 0;

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");
    printf("Catat pemasukan\n");
    printf("===================================================\n");
    printf("Nominal : ");
    formatRupiah(nominal);
    printf("\n");
    printf("===================================================\n");
    printf("Tekan ESC untuk kembali\n");
    gotoxy(13, 7);

    do {
        key = getch();

        if (((key >= '0' && key <= '9')) && (n < 9)) {
            if (!(n == 0 && key == '0')) {
                nominalstr[n] = key;
                n++;
                sscanf(nominalstr, "%d", &nominal);

                gotoxy(11, 7);
                printf("                  ");
                gotoxy(11, 7);
                formatRupiah(nominal);
                gotoxy(11 + getLengthFormatRupiah(nominal) + 2, 7);
            }
        } else if (key == 13) {  // Enter key
            if (n > 0) {
                nominalstr[n] = '\0';
                sscanf(nominalstr, "%d", &nominal);
                n = 0;
                // gotoxy(19 + n, 3);
                break;
            }
        } else if (key == 8) {  // Backspace key
            if (n > 0) {
                n--;

                nominalstr[n] = '\0';
                if (nominalstr[0] == '\0') {
                    nominal = 0;
                } else {
                    sscanf(nominalstr, "%d", &nominal);
                }

                gotoxy(11, 7);
                printf("                  ");
                gotoxy(11, 7);
                formatRupiah(nominal);
                gotoxy(11 + getLengthFormatRupiah(nominal) + 2, 7);
            }
        }
    } while (key != 27);  // ESC key

    if (key == 13) {
        tampilPilihKategori(username, 2, nominal);
    }

    if (key == 27) {
        tampilMenuCatat(username);
    }
}

void tampilMenuCatatTransfer(char username[20], int jenis, int exid_dompet, const char *judul) {
    int current_selection = 1, jmlDompet = 0;
    char key, initiate = 1, j, status = 1;

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");
    printf("%s\n", judul);
    printf("===================================================\n");
    if (jenis == 1) {
        printf("Pilih dompet asal\n");
    } else {
        printf("Pilih dompet tujuan\n");
    }
    printf("===================================================\n");

    // hitung dompet
    jmlDompet = getDompet(username, false);

    Wallet dom;
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");

    // isi
    do {
        int idKosong[100] = {}, kosong = 0;
        gotoxy(1, 9);
        j = 0;
        if (initiate == 1) {
            printf("[%c] ", 254);
        } else {
            printf("[ ]");
        }

        while (fread(&dom, sizeof(struct Wallet), 1, file) == 1) {
            if ((strcmp(dom.nama_dompet, "") != 0) && (dom.id != exid_dompet)) {
                if (j == 0) {
                    gotoxy(1, 9);
                }

                if (j == 0 && initiate == 1) {
                    printf("[%c] %s, ", 254, dom.nama_dompet);
                } else {
                    printf("[%c] %s, ", (current_selection == dom.id || initiate == 1) ? 254 : ' ', dom.nama_dompet);
                }

                formatRupiah(dom.saldo);
                printf("\n");
                j++;

                if (current_selection == dom.id && isIdInKosong(current_selection, idKosong, kosong)) {
                    current_selection = dom.id;
                }
                initiate++;
            } else {
                idKosong[kosong] = dom.id;
                kosong++;
            }
        }

        if (current_selection <= 0 || isIdInKosong(current_selection, idKosong, kosong)) {
            for (int i = 1; i <= getLastIDDompet(username) + 1; ++i) {
                if (!isIdInKosong(i, idKosong, kosong)) {
                    current_selection = i;
                    break;
                }
            }
        }
        printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == getLastIDDompet(username) + 1) ? 254 : ' ');
        printf("===================================================\n");
        printf("Gunakan tombol panah untuk navigasi dan tekan Enter\n");

        // navigasi menu
        key = getch();

        initiate = 2;

        // Pindahkan posisi ke awal file
        fseek(file, 0, SEEK_SET);

        if ((key == 72) && (current_selection > 1)) {
            do {
                current_selection -= 1;
            } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection > 1));

            if (isIdInKosong(current_selection, idKosong, kosong)) {
                int firstNonEmptyID = getFirstNonEmptyID(idKosong, kosong, getLastIDDompet(username));
                if (firstNonEmptyID > 0) {
                    current_selection = firstNonEmptyID;
                }
            }

            current_selection = (current_selection < 1) ? 1 : current_selection;
        } else if ((key == 80) && (current_selection < getLastIDDompet(username) + 1)) {
            do {
                current_selection += 1;
            } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection < getLastIDDompet(username) + 1));

            if (isIdInKosong(current_selection, idKosong, kosong)) {
                int firstNonEmptyID = getFirstNonEmptyID(idKosong, kosong, getLastIDDompet(username));
                if (firstNonEmptyID > 0) {
                    current_selection = firstNonEmptyID;
                }
            }

            current_selection = (current_selection > getLastIDDompet(username) + 1) ? getLastIDDompet(username) + 1 : current_selection;
        } else if (key == 13) {
            fclose(file);
            if (current_selection == getLastIDDompet(username) + 1) {
                if (jenis == 1) {
                    tampilMenuCatat(username);
                } else {
                    tampilMenuCatatTransfer(username, 1, -1, "Catat Transfer Saldo antar Dompet");
                }
            } else {
                if (jenis == 1) {
                    tampilMenuCatatTransfer(username, 2, current_selection, "Catat Transfer Saldo antar Dompet");
                } else {
                    // catat
                    tampilMenuNominalTransfer(username, exid_dompet, current_selection);
                }
            }
        }
    } while (key != 13);
    fclose(file);
}

void tampilMenuNominalTransfer(char username[20], int id_dompet_asal, int id_dompet_tujuan) {
    char key, nominalstr[20];
    int n = 0, status = 1, nominal = 0;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");
        printf("Catat Transfer Saldo antar Dompet\n");
        printf("===================================================\n");
        printf("Dompet Asal \t: %s, ", getNamaDompet(username, id_dompet_asal));
        formatRupiah(getSaldoDompet(username, id_dompet_asal));
        printf("\n");
        printf("Dompet Tujuan \t: %s, ", getNamaDompet(username, id_dompet_tujuan));
        formatRupiah(getSaldoDompet(username, id_dompet_tujuan));
        printf("\n");
        printf("Nominal \t: ");
        formatRupiah(nominal);
        printf("\n");
        printf("===================================================\n");
        printf("Tekan ESC untuk kembali");
        gotoxy(21, 9);

        do {
            key = getch();

            if (((key >= '0' && key <= '9')) && (n < 9)) {
                if (!(n == 0 && key == '0')) {
                    nominalstr[n] = key;
                    n++;
                    sscanf(nominalstr, "%d", &nominal);

                    gotoxy(19, 9);
                    printf("                  ");
                    gotoxy(19, 9);
                    formatRupiah(nominal);
                    gotoxy(19 + getLengthFormatRupiah(nominal) + 2, 9);
                }
            } else if (key == 13) {  // Enter key
                if (n > 0) {
                    nominalstr[n] = '\0';
                    sscanf(nominalstr, "%d", &nominal);
                    n = 0;
                    break;
                }
            } else if (key == 8) {  // Backspace key
                if (n > 0) {
                    n--;

                    nominalstr[n] = '\0';
                    if (nominalstr[0] == '\0') {
                        nominal = 0;
                    } else {
                        sscanf(nominalstr, "%d", &nominal);
                    }

                    gotoxy(19, 9);
                    printf("                  ");
                    gotoxy(19, 9);
                    formatRupiah(nominal);
                    gotoxy(19 + getLengthFormatRupiah(nominal) + 2, 9);
                }
            }
        } while (key != 27);  // ESC key

        if (key == 13) {
            if ((getSaldoDompet(username, id_dompet_asal) - nominal) < 0) {
                gotoxy(1, 11);
                printf("Saldo dompet asal tidak mencukupi                        \n");
                status = 1;
                getch();

                strcpy(nominalstr, "         ");
                nominal = 0;
                sscanf(nominalstr, "%d", &nominal);

                gotoxy(19, 9);
                printf("                  ");
                gotoxy(19, 9);
                formatRupiah(nominal);
                gotoxy(19 + getLengthFormatRupiah(nominal) + 2, 9);
            } else if (getSaldoDompet(username, id_dompet_tujuan) + nominal > 999999999) {
                gotoxy(1, 11);
                printf("Nominal transfer melebihi batas                      \n");
                status = 1;
                getch();

                strcpy(nominalstr, "0");
                nominal = 0;
                sscanf(nominalstr, "%d", &nominal);

                gotoxy(19, 9);
                printf("                  ");
                gotoxy(19, 9);
                formatRupiah(nominal);
                gotoxy(19 + getLengthFormatRupiah(nominal) + 2, 9);
            } else {
                tampilKonfirmasiCatatTransfer(username, id_dompet_asal, id_dompet_tujuan, nominal);
                status = 0;
            }
        }

        if (key == 27) {
            tampilMenuCatatTransfer(username, 2, id_dompet_asal, "Catat Transfer Saldo antar Dompet");
            status = 0;
        }
    } while (status == 1);
}

void tampilPilihKategori(char username[20], int jenis, int nominal) {
    int current_selection = 1;
    char key, j;
    // char *kategori[100];
    char kategori[100][20];

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");
    printf("Pilih kategori %s\n", (jenis == 1) ? "pengeluaran" : "pemasukan");
    printf("===================================================\n");

    Activity act;
    char file_name[50];
    sprintf(file_name, "data\\activities\\activity_%s.dat", username);

    FILE *file = fopen(file_name, "rb");

    // isi
    do {
        gotoxy(1, 7);
        j = 2;

        printf("[%c] Buat Kategori Baru\n", (current_selection == 1) ? 254 : ' ');
        printf("------------------------------------\n");

        while (fread(&act, sizeof(struct Activity), 1, file) == 1) {
            if (strcmp(act.jenis, (jenis == 1) ? "Pengeluaran" : "Pemasukan") == 0) {
                int found = 0;
                for (int i = 2; i < j; i++) {
                    if (strcmp(kategori[i - 2], act.kategori) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    strncpy(kategori[j - 2], act.kategori, sizeof(kategori[j - 2]) - 1);
                    kategori[j - 2][sizeof(kategori[j - 2]) - 1] = '\0';  // Ensure null-terminated
                    printf("[%c] %s\n", (current_selection == j) ? 254 : ' ', kategori[j - 2]);
                    j++;

                    if (j >= 20) {
                        break;
                    }
                }
            }
        }

        printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == j) ? 254 : ' ');
        printf("===================================================\n");
        printf("Gunakan tombol panah untuk navigasi dan tekan Enter");

        // navigasi menu
        key = getch();

        // Pindahkan posisi ke awal file
        fseek(file, 0, SEEK_SET);

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < j)) {
            current_selection += 1;
        } else if (key == 13) {
            fclose(file);
            if (current_selection != j && current_selection != 1) {
                tampilPilihDompet(username, jenis, kategori[current_selection - 2], nominal);
            } else if (current_selection == j) {
                if (jenis == 1) {
                    tampilMenuCatatPengeluaran(username);
                } else {
                    tampilMenuCatatPemasukan(username);
                }
            } else {
                tampilBuatKategori(username, jenis, nominal);
            }
        }
    } while (key != 13);
    fclose(file);
}

void tampilBuatKategori(char username[20], int jenis, int nominal) {
    char kategoribaru[21], key;
    int n = 0, status = 1;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");
        printf("Buat kategori baru untuk %s\n", (jenis == 1) ? "pengeluaran" : "pemasukan");
        printf("===================================================\n");
        printf("Kategori : \n");
        printf("===================================================\n");
        printf("Tekan ESC untuk kembali");

        gotoxy(12, 7);

        do {
            key = getch();

            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 20)) {
                kategoribaru[n] = key;
                n++;
                printf("%c", key);
                gotoxy(12 + n, 7);
            } else if (key == 13) {  // Enter key
                if (n > 0) {
                    kategoribaru[n] = '\0';
                    n = 0;
                    break;
                }
            } else if (key == 8) {  // Backspace key
                if (n > 0) {
                    printf("\b \b");
                    n--;
                }
            }
        } while (key != 27);  // ESC key

        if (key == 13) {
            // pilihDompet
            tampilPilihDompet(username, jenis, kategoribaru, nominal);
        }
    } while (status == 1 && key != 27);

    if (status == 0) {
        tampilPilihKategori(username, jenis, nominal);
    }

    if (key == 27) {
        tampilPilihKategori(username, jenis, nominal);
    }
}

void tampilPilihDompet(char username[20], int jenis, char kategori[20], int nominal) {
    int current_selection = 1, jmlDompet = 0;
    char key, initiate = 1, j, status = 1;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");
        if (jenis == 1) {
            printf("Pilih dompet yang akan digunakan\n");
        } else {
            printf("Pilih dompet tujuan\n");
        }
        printf("===================================================\n");

        // hitung dompet
        jmlDompet = getDompet(username, false);

        Wallet dom;
        char file_name[50];
        sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

        FILE *file = fopen(file_name, "rb");

        // isi
        do {
            int idKosong[100] = {}, kosong = 0;
            gotoxy(1, 7);
            j = 0;

            // Display ASCII 254 in the first row
            if (initiate == 1) {
                printf("[%c] ", 254);
            } else {
                printf("[ ]");  // Spaces to maintain alignment for other rows
            }

            // Membaca file untuk mencari ID yang kosong
            while (fread(&dom, sizeof(struct Wallet), 1, file) == 1) {
                if (strcmp(dom.nama_dompet, "") != 0) {
                    if (j == 0) {
                        gotoxy(1, 7);
                    }

                    // Check if in the first row to keep ASCII 254
                    if (j == 0 && initiate == 1) {
                        printf("[%c] %s, ", 254, dom.nama_dompet);
                    } else {
                        printf("[%c] %s, ", (current_selection == dom.id || initiate == 1) ? 254 : ' ', dom.nama_dompet);
                    }

                    formatRupiah(dom.saldo);
                    printf("\n");
                    j++;

                    // Update current_selection if it's initially pointing to an ID in idKosong
                    if (current_selection == dom.id && isIdInKosong(current_selection, idKosong, kosong)) {
                        current_selection = dom.id;
                    }
                    initiate++;
                } else {
                    idKosong[kosong] = dom.id;
                    kosong++;
                }
            }

            // Menentukan nilai awal current_selection yang valid jika ID paling awal termasuk dalam idKosong
            if (current_selection <= 0 || isIdInKosong(current_selection, idKosong, kosong)) {
                for (int i = 1; i <= getLastIDDompet(username) + 1; ++i) {
                    if (!isIdInKosong(i, idKosong, kosong)) {
                        current_selection = i;
                        break;
                    }
                }
            }
            printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == getLastIDDompet(username) + 1) ? 254 : ' ');
            printf("===================================================\n");
            printf("Gunakan tombol panah untuk navigasi dan tekan Enter");

            // navigasi menu
            key = getch();

            initiate = 2;

            // Pindahkan posisi ke awal file
            fseek(file, 0, SEEK_SET);

            if ((key == 72) && (current_selection > 1)) {
                do {
                    current_selection -= 1;
                } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection > 1));

                // Adjust current_selection to the first non-empty ID if necessary
                if (isIdInKosong(current_selection, idKosong, kosong)) {
                    int firstNonEmptyID = getFirstNonEmptyID(idKosong, kosong, getLastIDDompet(username));
                    if (firstNonEmptyID > 0) {
                        current_selection = firstNonEmptyID;
                    }
                }

                current_selection = (current_selection < 1) ? 1 : current_selection;
            } else if ((key == 80) && (current_selection < getLastIDDompet(username) + 1)) {
                do {
                    current_selection += 1;
                } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection < getLastIDDompet(username) + 1));

                // Adjust current_selection to the first non-empty ID if necessary
                if (isIdInKosong(current_selection, idKosong, kosong)) {
                    int firstNonEmptyID = getFirstNonEmptyID(idKosong, kosong, getLastIDDompet(username));
                    if (firstNonEmptyID > 0) {
                        current_selection = firstNonEmptyID;
                    }
                }

                current_selection = (current_selection > getLastIDDompet(username) + 1) ? getLastIDDompet(username) + 1 : current_selection;
            } else if (key == 13) {
                fclose(file);
                if (current_selection == getLastIDDompet(username) + 1) {
                    tampilPilihKategori(username, jenis, nominal);
                } else {
                    if (jenis == 1) {
                        if ((getSaldoDompet(username, current_selection) - nominal) < 0) {
                            gotoxy(1, 9 + jmlDompet);
                            printf("Saldo pada dompet tersebut kurang                        ");
                            status = 1;
                            getch();
                        } else {
                            // tampilKonfirmasiCatatPengeluaran(username, jenis, kategori, current_selection, nominal);
                            tampilPilihTanggal(username, jenis, kategori, current_selection, nominal);
                            status = 0;
                        }
                    } else {
                        if ((getSaldoDompet(username, current_selection) + nominal) > 999999999) {
                            gotoxy(1, 9 + jmlDompet);
                            printf("Saldo melebihi batas                                      ");
                            status = 1;
                            getch();
                        } else {
                            // atur tanggal
                            tampilPilihTanggal(username, jenis, kategori, current_selection, nominal);
                            status = 0;
                        }
                    }
                }
            }
        } while (key != 13);
        fclose(file);
    } while (status == 1);
}

void tampilPilihTanggal(char username[20], int jenis, char kategori[20], int iddompet, int nominal) {
    int current_selection = 1, status = 1;
    char key;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");
        printf("Pilih tanggal\n");

        // isi
        do {
            gotoxy(1, 6);
            printf("===================================================\n");
            printf("[%c] Saat Ini\n", (current_selection == 1) ? 254 : ' ');
            printf("[%c] Atur Tanggal\n", (current_selection == 2) ? 254 : ' ');
            printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == 3) ? 254 : ' ');
            printf("===================================================\n");
            printf("Gunakan tombol panah untuk navigasi dan tekan Enter");

            // navigasi menu
            key = getch();

            if ((key == 72) && (current_selection > 1)) {
                current_selection -= 1;
            } else if ((key == 80) && (current_selection < 2)) {
                current_selection += 1;
            } else if (key == 13) {
                switch (current_selection) {
                    case 1:
                        // status = catatPengeluaran(username, kategori, iddompet, nominal);
                        // getch();
                        if (jenis == 1) {
                            tampilKonfirmasiCatatPengeluaran(username, jenis, kategori, current_selection, nominal, 0);
                        } else {
                            tampilKonfirmasiCatatPemasukan(username, jenis, kategori, current_selection, nominal, 0);
                        }
                        break;
                    case 2:
                        tampilAturTanggal(username, jenis, kategori, current_selection, nominal);
                        break;
                    default:
                        tampilPilihDompet(username, jenis, kategori, nominal);
                        break;
                }
            }
        } while (key != 13);
    } while (status == 1);

    if (status == 0) {
        tampilMenuUtama(username);
    }
}

// int tanggal, bulan, tahun;

//     // Input tanggal
//     printf("Masukkan tanggal: ");
//     scanf("%d", &tanggal);

//     // Input bulan
//     printf("Masukkan bulan: ");
//     scanf("%d", &bulan);

//     // Input tahun
//     printf("Masukkan tahun: ");
//     scanf("%d", &tahun);

//     struct tm waktu = {0};
//     waktu.tm_mday = tanggal;
//     waktu.tm_mon = bulan - 1; // Bulan dimulai dari 0
//     waktu.tm_year = tahun - 1900; // Tahun dimulai dari 1900

//     return mktime(&waktu);

void tampilKonfirmasiCatatPengeluaran(char username[20], int jenis, char kategori[20], int iddompet, int nominal, time_t waktu) {
    int current_selection = 1, status = 1;
    char key;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");
        printf("Konfirmasi Catat Pengeluaran\n");
        printf("===================================================\n");
        printf("Jumlah Pengeluaran\t: ");
        formatRupiah(nominal);
        printf("\nDari Dompet\t\t: %s\n", getNamaDompet(username, iddompet));
        printf("Kategori\t\t: %s\n", kategori);

        int temp;
        temp = getSaldoDompet(username, iddompet);

        printf("===================================================\n");
        printf("Saldo Dompet \"%s\" : ", getNamaDompet(username, iddompet));
        formatRupiah(temp);
        printf("\nDompet \"%s\" akan berkurang menjadi ", getNamaDompet(username, iddompet));
        formatRupiah(temp - nominal);

        // isi
        do {
            gotoxy(1, 13);
            printf("===================================================\n");
            printf("[%c] Konfirmasi\n", (current_selection == 1) ? 254 : ' ');
            printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == 2) ? 254 : ' ');
            printf("===================================================\n");
            printf("Gunakan tombol panah untuk navigasi dan tekan Enter");

            // navigasi menu
            key = getch();

            if ((key == 72) && (current_selection > 1)) {
                current_selection -= 1;
            } else if ((key == 80) && (current_selection < 2)) {
                current_selection += 1;
            } else if (key == 13) {
                switch (current_selection) {
                    case 1:
                        gotoxy(1, 16);
                        status = catatPengeluaran(username, kategori, iddompet, nominal, waktu);
                        getch();
                        break;
                    default:
                        tampilPilihDompet(username, jenis, kategori, nominal);
                        break;
                }
            }
        } while (key != 13);
    } while (status == 1);

    if (status == 0) {
        tampilMenuUtama(username);
    }
}

void tampilKonfirmasiCatatPemasukan(char username[20], int jenis, char kategori[20], int iddompet, int nominal, time_t waktu) {
    int current_selection = 1, status = 1;
    char key;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");
        printf("Konfirmasi Catat Pemasukan\n");
        printf("===================================================\n");
        printf("Jumlah Pemasukan\t: ");
        formatRupiah(nominal);
        printf("\nDompet Tujuan\t\t: %s\n", getNamaDompet(username, iddompet));
        printf("Kategori\t\t: %s\n", kategori);

        int temp;
        temp = getSaldoDompet(username, iddompet);

        printf("===================================================\n");
        printf("Saldo Dompet \"%s\" : ", getNamaDompet(username, iddompet));
        formatRupiah(temp);
        printf("\nDompet \"%s\" akan bertambah menjadi ", getNamaDompet(username, iddompet));
        formatRupiah(temp + nominal);

        // isi
        do {
            gotoxy(1, 13);
            printf("===================================================\n");
            printf("[%c] Konfirmasi\n", (current_selection == 1) ? 254 : ' ');
            printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == 2) ? 254 : ' ');
            printf("===================================================\n");
            printf("Gunakan tombol panah untuk navigasi dan tekan Enter");

            // navigasi menu
            key = getch();

            if ((key == 72) && (current_selection > 1)) {
                current_selection -= 1;
            } else if ((key == 80) && (current_selection < 2)) {
                current_selection += 1;
            } else if (key == 13) {
                switch (current_selection) {
                    case 1:
                        gotoxy(1, 16);
                        status = catatPemasukan(username, kategori, iddompet, nominal, waktu);
                        getch();
                        break;
                    default:
                        tampilPilihDompet(username, jenis, kategori, nominal);
                        break;
                }
            }
        } while (key != 13);
    } while (status == 1);

    if (status == 0) {
        tampilMenuUtama(username);
    }
}

void tampilKonfirmasiCatatTransfer(char username[20], int id_dompet_asal, int id_dompet_tujuan, int nominal) {
    int current_selection = 1, status = 1;
    char key;

    do {
        clearScreen();

        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");
        printf("Catat Transfer Saldo antar Dompet\n");
        printf("===================================================\n");
        printf("Dompet Asal \t: %s, ", getNamaDompet(username, id_dompet_asal));
        formatRupiah(getSaldoDompet(username, id_dompet_asal));
        printf("\n");
        printf("Dompet Tujuan \t: %s, ", getNamaDompet(username, id_dompet_tujuan));
        formatRupiah(getSaldoDompet(username, id_dompet_tujuan));
        printf("\n");
        printf("Nominal \t: ");
        formatRupiah(nominal);
        printf("\n");
        printf("===================================================\n");

        printf("Saldo Dompet \"%s\" \t: ", getNamaDompet(username, id_dompet_asal));
        formatRupiah(getSaldoDompet(username, id_dompet_asal));
        printf(" -> ");
        formatRupiah(getSaldoDompet(username, id_dompet_asal) - nominal);
        printf("\nSaldo Dompet \"%s\" \t: ", getNamaDompet(username, id_dompet_tujuan));
        formatRupiah(getSaldoDompet(username, id_dompet_tujuan));
        printf(" -> ");
        formatRupiah(getSaldoDompet(username, id_dompet_tujuan) + nominal);
        printf("\n===================================================\n");

        // isi
        do {
            gotoxy(1, 14);
            printf("[%c] Konfirmasi\n", (current_selection == 1) ? 254 : ' ');
            printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == 2) ? 254 : ' ');
            printf("===================================================\n");
            printf("Gunakan tombol panah untuk navigasi dan tekan Enter");

            // navigasi menu
            key = getch();

            if ((key == 72) && (current_selection > 1)) {
                current_selection -= 1;
            } else if ((key == 80) && (current_selection < 2)) {
                current_selection += 1;
            } else if (key == 13) {
                switch (current_selection) {
                    case 1:
                        gotoxy(1, 16);
                        status = catatTransfer(username, id_dompet_asal, id_dompet_tujuan, nominal);
                        getch();
                        break;
                    default:
                        tampilMenuNominalTransfer(username, id_dompet_asal, id_dompet_tujuan);
                        break;
                }
            }
        } while (key != 13);
    } while (status == 1);

    if (status == 0) {
        tampilMenuUtama(username);
    }
}

void tampilMenuRekap(char username[20]) {
    int current_selection = 1;
    char key;

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");

    // isi
    do {
        gotoxy(1, 5);
        printf("[%c] Tampil Rekap Harian\n", (current_selection == 1) ? 254 : ' ');
        printf("[%c] Tampil Rekap Mingguan\n", (current_selection == 2) ? 254 : ' ');
        printf("[%c] Tampil Rekap Bulanan\n", (current_selection == 3) ? 254 : ' ');
        printf("[%c] Tampil Semua Pemasukan\n", (current_selection == 4) ? 254 : ' ');
        printf("[%c] Tampil Semua Pengeluaran\n", (current_selection == 5) ? 254 : ' ');
        printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == 6) ? 254 : ' ');
        printf("===================================================\n");
        printf("Gunakan tombol panah untuk navigasi dan tekan Enter");

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
                    getHarian(username);
                    break;
                case 2:
                    getMingguan(username);
                    // panggil prosedur tampil rekap mingguan
                    break;
                case 3:
                    getBulanan(username);
                    // panggil prosedur tampil rekap bulanan
                    break;
                case 4:
                    getSemuaPemasukan(username);
                    // panggil prosedur tampil rekap pemasukkan
                    break;
                case 5:
                    getSemuaPengeluaran(username);
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
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");

    // tampil dompet
    jmlDompet = getDompet(username, true);
    printf("===================================================\n");

    // isi
    do {
        gotoxy(1, 4 + jmlDompet + 3);
        printf("[%c] Tambah Dompet\n", (current_selection == 1) ? 254 : ' ');
        printf("[%c] Ubah Nama Dompet\n", (current_selection == 2) ? 254 : ' ');
        printf("[%c] Hapus Dompet\n", (current_selection == 3) ? 254 : ' ');
        printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == 4) ? 254 : ' ');
        printf("===================================================\n");
        printf("Gunakan tombol panah untuk navigasi dan tekan Enter\n");

        // navigasi menu
        key = getch();

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 4)) {
            current_selection += 1;
        } else if (key == 13) {
            switch (current_selection) {
                case 1:
                    // panggil prosedur tambah dompet
                    if (jmlDompet < 10) {
                        tampilMenuTambahDompet(username);
                    } else {
                        gotoxy(1, 12 + jmlDompet);
                        printf("Tidak bisa menambah dompet, maksimal 10 dompet dalam 1 akun");
                        getch();
                        key = 0;
                    }
                    break;
                case 2:
                    // panggil prosedur ubah dompet
                    tampilMenuUbahNamaDompet(username);
                    break;
                case 3:
                    // panggil prosedur hapus dompet
                    if (jmlDompet > 1) {
                        tampilMenuHapusDompet(username);
                    } else {
                        gotoxy(1, 12 + jmlDompet);
                        printf("Tidak bisa menghapus dompet lagi, sisakan 1 dompet di akunmu");
                        getch();
                        key = 0;
                    }
                    break;
                case 4:
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
    int n = 0, p = 1, status = 1, saldo = 0;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");
        printf("Tambah dompet baru\n");
        printf("===================================================\n");

        // tampil dompet
        jmlDompet = getDompet(username, true);
        printf("===================================================\n");

        printf("Nama Dompet\t: \n");
        printf("Saldo Awal\t: ");
        formatRupiah(saldo);
        printf("\n");
        printf("===================================================\n");
        printf("Tekan ESC untuk kembali");
        gotoxy(19, 4 + jmlDompet + 5);

        do {
            key = getch();

            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 20)) {
                if (p == 1) {
                    namadompet[n] = key;
                    n++;
                    printf("%c", key);
                    gotoxy(19 + n, 8 + p + jmlDompet);
                } else if ((p == 2) && (key >= '0' && key <= '9') && (n < 8)) {
                    if (!(n == 0 && key == '0')) {
                        saldoawal[n] = key;
                        n++;
                        sscanf(saldoawal, "%d", &saldo);
                        gotoxy(19, 8 + p + jmlDompet);
                        printf("                  ");
                        gotoxy(19, 8 + p + jmlDompet);
                        formatRupiah(saldo);
                        gotoxy(19 + getLengthFormatRupiah(saldo) + 2, 8 + p + jmlDompet);
                    }
                }
            } else if (key == 13) {  // Enter key
                if (n == 0 && p == 2) {
                    saldo = 0;
                    p = 1;
                    n = 0;
                    break;
                }

                if (n > 0) {
                    if (p == 1) {
                        namadompet[n] = '\0';
                        p = 2;
                        n = 0;
                        gotoxy(19 + n + 2, 8 + p + jmlDompet);
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
                    if (p == 1) {
                        printf("\b \b");
                    }
                    n--;

                    if (p == 2) {
                        saldoawal[n] = '\0';
                        if (saldoawal[0] == '\0') {
                            saldo = 0;
                        } else {
                            sscanf(saldoawal, "%d", &saldo);
                        }

                        gotoxy(19, 5 + p + jmlDompet);
                        printf("                  ");
                        gotoxy(19, 5 + p + jmlDompet);
                        formatRupiah(saldo);
                        gotoxy(19 + getLengthFormatRupiah(saldo) + 2, 5 + p + jmlDompet);
                    }
                }
            }
        } while (key != 27);  // ESC key

        if (key == 13) {
            gotoxy(1, 9 + 2 + jmlDompet);
            status = tambahDompet(username, namadompet, saldo);
            getch();

            if (status == 1) {
                strcpy(saldoawal, "         ");
                saldo = 0;
                sscanf(saldoawal, "%d", &saldo);

                gotoxy(19, 5 + p + jmlDompet);
                printf("                  ");
                gotoxy(19, 5 + p + jmlDompet);
                formatRupiah(saldo);
                gotoxy(19 + getLengthFormatRupiah(saldo) + 2, 5 + p + jmlDompet);
            }
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
    char key, initiate = 1, j;

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");
    printf("Pilih dompet yang akan dihapus\n");
    printf("===================================================\n");

    // hitung dompet
    jmlDompet = getDompet(username, false);

    Wallet dom;
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");

    // isi
    do {
        int idKosong[100] = {}, kosong = 0;
        gotoxy(1, 7);
        j = 0;

        // Display ASCII 254 in the first row
        if (initiate == 1) {
            printf("[%c] ", 254);
        } else {
            printf("[ ] ");  // Spaces to maintain alignment for other rows
        }

        // Membaca file untuk mencari ID yang kosong
        while (fread(&dom, sizeof(struct Wallet), 1, file) == 1) {
            if (strcmp(dom.nama_dompet, "") != 0) {
                if (j == 0) {
                    gotoxy(1, 7);
                }

                // Check if in the first row to keep ASCII 254
                if (j == 0 && initiate == 1) {
                    printf("[%c] %s, ", 254, dom.nama_dompet);
                } else {
                    printf("[%c] %s, ", (current_selection == dom.id || initiate == 1) ? 254 : ' ', dom.nama_dompet);
                }

                formatRupiah(dom.saldo);
                printf("\n");
                j++;

                // Update current_selection if it's initially pointing to an ID in idKosong
                if (current_selection == dom.id && isIdInKosong(current_selection, idKosong, kosong)) {
                    current_selection = dom.id;
                }
                initiate++;
            } else {
                idKosong[kosong] = dom.id;
                kosong++;
            }
        }

        // Menentukan nilai awal current_selection yang valid jika ID paling awal termasuk dalam idKosong
        if (current_selection <= 0 || isIdInKosong(current_selection, idKosong, kosong)) {
            for (int i = 1; i <= getLastIDDompet(username) + 1; ++i) {
                if (!isIdInKosong(i, idKosong, kosong)) {
                    current_selection = i;
                    break;
                }
            }
        }
        printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == getLastIDDompet(username) + 1) ? 254 : ' ');
        printf("===================================================\n");
        printf("Gunakan tombol panah untuk navigasi dan tekan Enter\n");

        // navigasi menu
        key = getch();

        initiate = 2;

        // Pindahkan posisi ke awal file
        fseek(file, 0, SEEK_SET);

        if ((key == 72) && (current_selection > 1)) {
            do {
                current_selection -= 1;
            } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection > 1));

            // Adjust current_selection to the first non-empty ID if necessary
            if (isIdInKosong(current_selection, idKosong, kosong)) {
                int firstNonEmptyID = getFirstNonEmptyID(idKosong, kosong, getLastIDDompet(username));
                if (firstNonEmptyID > 0) {
                    current_selection = firstNonEmptyID;
                }
            }

            current_selection = (current_selection < 1) ? 1 : current_selection;
        } else if ((key == 80) && (current_selection < getLastIDDompet(username) + 1)) {
            do {
                current_selection += 1;
            } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection < getLastIDDompet(username) + 1));

            // Adjust current_selection to the first non-empty ID if necessary
            if (isIdInKosong(current_selection, idKosong, kosong)) {
                int firstNonEmptyID = getFirstNonEmptyID(idKosong, kosong, getLastIDDompet(username));
                if (firstNonEmptyID > 0) {
                    current_selection = firstNonEmptyID;
                }
            }

            current_selection = (current_selection > getLastIDDompet(username) + 1) ? getLastIDDompet(username) + 1 : current_selection;
        } else if (key == 13) {
            fclose(file);
            if (current_selection == getLastIDDompet(username) + 1) {
                tampilMenuDompet(username);
            } else {
                tampilKonfirmasiHapusDompet(username, getNamaDompet(username, current_selection), current_selection);
            }
        }
    } while (key != 13);
    fclose(file);
}

void tampilKonfirmasiHapusDompet(char username[20], char namadompet[20], int iddompet) {
    int current_selection = 1, status = 1;
    char key;

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");
    printf("Yakin ingin menghapus dompet \"%s\"?\nSemua riwayat aktivitas pada dompet ini akan terhapus\n", namadompet);
    printf("===================================================\n");

    // isi
    do {
        gotoxy(1, 8);
        printf("[%c] Tidak, kembali\n", (current_selection == 1) ? 254 : ' ');
        printf("[\033[1;31m%c\033[0m] Yakin\n", (current_selection == 2) ? 254 : ' ');
        printf("===================================================\n");
        printf("Gunakan tombol panah untuk navigasi dan tekan Enter");

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
                    gotoxy(1, 10);
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

void tampilMenuUbahNamaDompet(char username[20]) {
    int current_selection = 1, jmlDompet = 0;
    char key, initiate = 1, j;

    clearScreen();
    // print header
    printf("\033[1mMONEY TRACKING APP\033[0m\n");
    printf("===================================================\n");
    printf("Nama : %s\n", getNamaUser(username));
    printf("===================================================\n");
    printf("Pilih dompet yang akan diubah namanya\n");
    printf("===================================================\n");

    // hitung dompet
    jmlDompet = getDompet(username, false);

    Wallet dom;
    char file_name[50];
    sprintf(file_name, "data\\wallets\\wallet_%s.dat", username);

    FILE *file = fopen(file_name, "rb");

    // isi
    do {
        int idKosong[100] = {}, kosong = 0;
        gotoxy(1, 7);
        j = 0;

        // Display ASCII 254 in the first row
        if (initiate == 1) {
            printf("[%c] ", 254);
        } else {
            printf("[ ]");  // Spaces to maintain alignment for other rows
        }

        // Membaca file untuk mencari ID yang kosong
        while (fread(&dom, sizeof(struct Wallet), 1, file) == 1) {
            if (strcmp(dom.nama_dompet, "") != 0) {
                if (j == 0) {
                    gotoxy(1, 7);
                }

                // Check if in the first row to keep ASCII 254
                if (j == 0 && initiate == 1) {
                    printf("[%c] %s, ", 254, dom.nama_dompet);
                } else {
                    printf("[%c] %s, ", (current_selection == dom.id || initiate == 1) ? 254 : ' ', dom.nama_dompet);
                }

                formatRupiah(dom.saldo);
                printf("\n");
                j++;

                // Update current_selection if it's initially pointing to an ID in idKosong
                if (current_selection == dom.id && isIdInKosong(current_selection, idKosong, kosong)) {
                    current_selection = dom.id;
                }
                initiate++;
            } else {
                idKosong[kosong] = dom.id;
                kosong++;
            }
        }

        // Menentukan nilai awal current_selection yang valid jika ID paling awal termasuk dalam idKosong
        if (current_selection <= 0 || isIdInKosong(current_selection, idKosong, kosong)) {
            for (int i = 1; i <= getLastIDDompet(username) + 1; ++i) {
                if (!isIdInKosong(i, idKosong, kosong)) {
                    current_selection = i;
                    break;
                }
            }
        }

        printf("[\033[1;31m%c\033[0m] Kembali\n", (current_selection == getLastIDDompet(username) + 1) ? 254 : ' ');
        printf("===================================================\n");
        printf("Gunakan tombol panah untuk navigasi dan tekan Enter");

        // navigasi menu
        key = getch();

        initiate = 2;

        // Pindahkan posisi ke awal file
        fseek(file, 0, SEEK_SET);

        if ((key == 72) && (current_selection > 1)) {
            do {
                current_selection -= 1;
            } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection > 1));

            // Adjust current_selection to the first non-empty ID if necessary
            if (isIdInKosong(current_selection, idKosong, kosong)) {
                int firstNonEmptyID = getFirstNonEmptyID(idKosong, kosong, getLastIDDompet(username));
                if (firstNonEmptyID > 0) {
                    current_selection = firstNonEmptyID;
                }
            }

            current_selection = (current_selection < 1) ? 1 : current_selection;
        } else if ((key == 80) && (current_selection < getLastIDDompet(username) + 1)) {
            do {
                current_selection += 1;
            } while (isIdInKosong(current_selection, idKosong, kosong) && (current_selection < getLastIDDompet(username) + 1));

            // Adjust current_selection to the first non-empty ID if necessary
            if (isIdInKosong(current_selection, idKosong, kosong)) {
                int firstNonEmptyID = getFirstNonEmptyID(idKosong, kosong, getLastIDDompet(username));
                if (firstNonEmptyID > 0) {
                    current_selection = firstNonEmptyID;
                }
            }

            current_selection = (current_selection > getLastIDDompet(username) + 1) ? getLastIDDompet(username) + 1 : current_selection;
        } else if (key == 13) {
            fclose(file);
            if (current_selection == getLastIDDompet(username) + 1) {
                tampilMenuDompet(username);
            } else {
                tampilMenuInputNamaDompet(username, current_selection);
            }
        }
    } while (key != 13);
    fclose(file);
}

void tampilMenuInputNamaDompet(char username[20], int id_dompet) {
    char namabaru[21], key;
    int n = 0, status = 1;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Nama : %s\n", getNamaUser(username));
        printf("===================================================\n");
        printf("Ubah nama dompet \"%s\" \n", getNamaDompet(username, id_dompet));
        printf("===================================================\n");
        printf("Nama Baru : \n");
        printf("===================================================\n");
        printf("Tekan ESC untuk kembali");

        gotoxy(13, 7);

        do {
            key = getch();

            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 20)) {
                namabaru[n] = key;
                n++;
                printf("%c", key);
                gotoxy(13 + n, 7);
            } else if (key == 13) {  // Enter key
                if (n > 0) {
                    namabaru[n] = '\0';
                    n = 0;
                    break;
                }
            } else if (key == 8) {  // Backspace key
                if (n > 0) {
                    printf("\b \b");
                    n--;
                }
            }
        } while (key != 27);  // ESC key

        if (key == 13) {
            gotoxy(1, 8);
            status = ubahNamaDompet(username, id_dompet, namabaru);
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

int isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int cekTanggalValid(int tgl, int bln, int thn) {
    // Periksa validitas bulan
    if (bln < 1 || bln > 12) {
        return 1;  // Bulan tidak valid
    }

    // Array untuk menyimpan jumlah hari dalam setiap bulan
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Periksa apakah tahun kabisat
    if (isLeapYear(thn)) {
        daysInMonth[2] = 29;  // Tahun kabisat, bulan Februari memiliki 29 hari
    }

    // Periksa validitas tanggal
    if (tgl < 1 || tgl > daysInMonth[bln]) {
        return 2;  // Tanggal tidak valid
    }

    return 0;  // Tanggal valid
}

void tampilAturTanggal(char username[20], int jenis, char kategori[20], int iddompet, int nominal) {
    char tanggal[21], bulan[21], tahun[21], key;
    int tgl, bln, thn;
    int n = 0, p = 1, status = 1;

    do {
        clearScreen();
        // print header
        printf("\033[1mMONEY TRACKING APP\033[0m\n");
        printf("===================================================\n");
        printf("Masukkan tanggal\n");
        printf("===================================================\n");
        printf("Tanggal : \n");
        printf("Bulan   : \n");
        printf("Tahun   : \n");
        printf("===================================================\n");
        printf("Tekan ESC untuk kembali");

        gotoxy(12, 5);

        do {
            key = getch();

            if (((key >= '0' && key <= '9')) && (n < 4)) {
                if (p == 1) {
                    tanggal[n] = key;
                } else if (p == 2) {
                    bulan[n] = key;
                } else {
                    tahun[n] = key;
                }
                n++;
                printf("%c", key);
                gotoxy(12 + n, 4 + p);
            } else if (key == 13) {  // Enter key
                if (n > 0) {
                    if (p == 1) {
                        tanggal[n] = '\0';
                        sscanf(tanggal, "%d", &tgl);
                        p = 2;
                        n = 0;
                        gotoxy(12 + n, 4 + p);
                    } else if (p == 2) {
                        bulan[n] = '\0';
                        sscanf(bulan, "%d", &bln);
                        p = 3;
                        n = 0;
                        gotoxy(12 + n, 4 + p);
                    } else {
                        tahun[n] = '\0';
                        sscanf(tahun, "%d", &thn);
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
            gotoxy(1, 7);
            status = cekTanggalValid(tgl, bln, thn);
            getch();
        }
    } while (status == 1 && key != 27);

    if (status == 0) {
        time_t aturtgl;
        struct tm tanggalStruct = {0};
        tanggalStruct.tm_mday = tgl;
        tanggalStruct.tm_mon = bln - 1;
        tanggalStruct.tm_year = thn - 1900;

        aturtgl = mktime(&tanggalStruct);
        if (jenis == 1) {
            tampilKonfirmasiCatatPengeluaran(username, jenis, kategori, iddompet, nominal, aturtgl);
        } else {
            tampilKonfirmasiCatatPemasukan(username, jenis, kategori, iddompet, nominal, aturtgl);
        }
    }

    if (key == 27) {
        tampilPilihTanggal(username, jenis, kategori, iddompet, nominal);
    }
}