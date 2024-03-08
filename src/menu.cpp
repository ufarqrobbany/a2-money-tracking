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
    printf("MONEY TRACKING APP\n");
    printf("====================\n");

    // isi
    do {
        gotoxy(1, 3);
        printf("%c Masuk\n", (current_selection == 1) ? 254 : ' ');
        printf("%c Daftar\n", (current_selection == 2) ? 254 : ' ');
        printf("\n%c Keluar\n", (current_selection == 3) ? 254 : ' ');

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
        printf("\n%c Keluar\n", (current_selection == 4) ? 254 : ' ');

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
        printf("\n%c Kembali\n", (current_selection == 3) ? 254 : ' ');

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
                    tampilMenuCatatPengeluaran(username);
                    break;
                case 2:
                    // panggil prosedur catat pemasukan
                    tampilMenuCatatPemasukan(username);
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

void tampilMenuCatatPengeluaran(char username[20]) {
    char key, nominalstr[20];
    int n = 0, status = 1, nominal = 0;

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("Catat Pengeluaran\n");
    printf("====================\n");

    printf("Nominal \t: ");
    formatRupiah(nominal);
    printf("\n");
    gotoxy(21, 4);

    do {
        key = getch();

        if (((key >= '0' && key <= '9')) && (n < 9)) {
            if (!(n == 0 && key == '0')) {
                nominalstr[n] = key;
                n++;
                sscanf(nominalstr, "%d", &nominal);

                gotoxy(19, 4);
                printf("                  ");
                gotoxy(19, 4);
                formatRupiah(nominal);
                gotoxy(19 + getLengthFormatRupiah(nominal) + 2, 4);
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
                // if (p == 2) {
                //     printf("\b \b");
                // }
                n--;

                nominalstr[n] = '\0';
                if (nominalstr[0] == '\0') {
                    nominal = 0;
                } else {
                    sscanf(nominalstr, "%d", &nominal);
                }

                gotoxy(19, 4);
                printf("                  ");
                gotoxy(19, 4);
                formatRupiah(nominal);
                gotoxy(19 + getLengthFormatRupiah(nominal) + 2, 4);
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
    printf("MONEY TRACKING APP\n");
    printf("Catat Pemasukan\n");
    printf("====================\n");

    printf("Nominal \t: ");
    formatRupiah(nominal);
    printf("\n");
    gotoxy(21, 4);

    do {
        key = getch();

        if (((key >= '0' && key <= '9')) && (n < 9)) {
            if (!(n == 0 && key == '0')) {
                nominalstr[n] = key;
                n++;
                sscanf(nominalstr, "%d", &nominal);

                gotoxy(19, 4);
                printf("                  ");
                gotoxy(19, 4);
                formatRupiah(nominal);
                gotoxy(19 + getLengthFormatRupiah(nominal) + 2, 4);
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
                // if (p == 2) {
                //     printf("\b \b");
                // }
                n--;

                nominalstr[n] = '\0';
                if (nominalstr[0] == '\0') {
                    nominal = 0;
                } else {
                    sscanf(nominalstr, "%d", &nominal);
                }

                gotoxy(19, 4);
                printf("                  ");
                gotoxy(19, 4);
                formatRupiah(nominal);
                gotoxy(19 + getLengthFormatRupiah(nominal) + 2, 4);
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

void tampilPilihKategori(char username[20], int jenis, int nominal) {
    int current_selection = 1;
    char key, j;
    // char *kategori[100];
    char kategori[100][20];

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("User: %s\n", username);
    printf("====================\n");
    printf("Pilih kategori\n");

    Activity act;
    char file_name[50];
    sprintf(file_name, "data\\activities\\activity_%s.dat", username);

    FILE *file = fopen(file_name, "rb");

    // isi
    do {
        gotoxy(1, 5);
        j = 2;

        printf("%c Buat Kategori Baru\n\n", (current_selection == 1) ? 254 : ' ');

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
                    printf("%c %s\n", (current_selection == j) ? 254 : ' ', kategori[j - 2]);
                    j++;

                    if (j >= 20) {
                        break;
                    }
                }
            }
        }

        printf("\n%c Kembali", (current_selection == j) ? 254 : ' ');

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
        printf("MONEY TRACKING APP\n");
        printf("Buat Kategori Baru\n");
        printf("====================\n");
        printf("Kategori: ");

        gotoxy(11, 4);

        do {
            key = getch();

            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 20)) {
                kategoribaru[n] = key;
                n++;
                printf("%c", key);
                gotoxy(11 + n, 4);
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
        printf("MONEY TRACKING APP\n");
        printf("User: %s\n", username);
        printf("====================\n");
        if (jenis == 1) {
            printf("Pilih dompet yang akan digunakan\n");
        } else {
            printf("Pilih dompet tujuan\n");
        }

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
            j = 0;

            // Display ASCII 254 in the first row
            if (initiate == 1) {
                printf("%c ", 254);
            } else {
                printf("  ");  // Spaces to maintain alignment for other rows
            }

            // Membaca file untuk mencari ID yang kosong
            while (fread(&dom, sizeof(struct Wallet), 1, file) == 1) {
                if (strcmp(dom.nama_dompet, "") != 0) {
                    if (j == 0) {
                        gotoxy(1, 5);
                    }

                    // Check if in the first row to keep ASCII 254
                    if (j == 0 && initiate == 1) {
                        printf("%c %s, ", 254, dom.nama_dompet);
                    } else {
                        printf("%c %s, ", (current_selection == dom.id || initiate == 1) ? 254 : ' ', dom.nama_dompet);
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
            printf("\n%c Kembali", (current_selection == getLastIDDompet(username) + 1) ? 254 : ' ');

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
                            printf("\nSaldo pada dompet tersebut kurang");
                            status = 1;
                            getch();
                        } else {
                            tampilKonfirmasiCatatPengeluaran(username, jenis, kategori, current_selection, nominal);
                            status = 0;
                        }
                    } else {
                        if ((getSaldoDompet(username, current_selection) + nominal) > 999999999) {
                            printf("\nSaldo melebihi batas");
                            status = 1;
                            getch();
                        } else {
                            tampilKonfirmasiCatatPemasukan(username, jenis, kategori, current_selection, nominal);
                            status = 0;
                        }
                    }
                }
            }
        } while (key != 13);
        fclose(file);
    } while (status == 1);
}

void tampilKonfirmasiCatatPengeluaran(char username[20], int jenis, char kategori[20], int iddompet, int nominal) {
    int current_selection = 1, status = 1;
    char key;

    do {
        clearScreen();
        // print header
        printf("MONEY TRACKING APP\n");
        printf("User: %s\n", username);
        printf("====================\n");
        printf("Catat Pengeluaran\n");
        printf("====================\n");
        // formatRupiah(nominal);
        // printf(" akan dikurangi dari dompet %s\n", getNamaDompet(username, iddompet));
        printf("Jumlah Pengeluaran: ");
        formatRupiah(nominal);
        printf("\nDari Dompet: %s\n", getNamaDompet(username, iddompet));
        printf("Kategori: %s\n", kategori);

        int temp;
        temp = getSaldoDompet(username, iddompet);

        printf("\nSaldo Dompet \"%s\": ", getNamaDompet(username, iddompet));
        formatRupiah(temp);
        printf("\nDompet \"%s\" akan berkurang menjadi ", getNamaDompet(username, iddompet));
        formatRupiah(temp - nominal);

        // isi
        do {
            gotoxy(1, 12);
            printf("%c Konfirmasi\n", (current_selection == 1) ? 254 : ' ');
            printf("%c Kembali\n", (current_selection == 2) ? 254 : ' ');

            // navigasi menu
            key = getch();

            if ((key == 72) && (current_selection > 1)) {
                current_selection -= 1;
            } else if ((key == 80) && (current_selection < 2)) {
                current_selection += 1;
            } else if (key == 13) {
                switch (current_selection) {
                    case 1:
                        status = catatPengeluaran(username, kategori, iddompet, nominal);
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

void tampilKonfirmasiCatatPemasukan(char username[20], int jenis, char kategori[20], int iddompet, int nominal) {
    int current_selection = 1, status = 1;
    char key;

    do {
        clearScreen();
        // print header
        printf("MONEY TRACKING APP\n");
        printf("User: %s\n", username);
        printf("====================\n");
        printf("Catat Pemasukan\n");
        printf("====================\n");
        // formatRupiah(nominal);
        // printf(" akan dikurangi dari dompet %s\n", getNamaDompet(username, iddompet));
        printf("Jumlah Pemasukan: ");
        formatRupiah(nominal);
        printf("\nDompet Tujuan: %s\n", getNamaDompet(username, iddompet));
        printf("Kategori: %s\n", kategori);

        int temp;
        temp = getSaldoDompet(username, iddompet);

        printf("\nSaldo Dompet \"%s\": ", getNamaDompet(username, iddompet));
        formatRupiah(temp);
        printf("\nDompet \"%s\" akan bertambah menjadi ", getNamaDompet(username, iddompet));
        formatRupiah(temp + nominal);

        // isi
        do {
            gotoxy(1, 12);
            printf("%c Konfirmasi\n", (current_selection == 1) ? 254 : ' ');
            printf("%c Kembali\n", (current_selection == 2) ? 254 : ' ');

            // navigasi menu
            key = getch();

            if ((key == 72) && (current_selection > 1)) {
                current_selection -= 1;
            } else if ((key == 80) && (current_selection < 2)) {
                current_selection += 1;
            } else if (key == 13) {
                switch (current_selection) {
                    case 1:
                        status = catatPemasukan(username, kategori, iddompet, nominal);
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
        printf("\n%c Kembali\n", (current_selection == 6) ? 254 : ' ');

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
        printf("%c Tambah Dompet\n", (current_selection == 1) ? 254 : ' ');
        printf("%c Ubah Nama Dompet\n", (current_selection == 2) ? 254 : ' ');
        printf("%c Hapus Dompet\n", (current_selection == 3) ? 254 : ' ');
        printf("\n%c Kembali\n", (current_selection == 4) ? 254 : ' ');

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
        printf("MONEY TRACKING APP\n");
        printf("Tambah Dompet Baru\n");
        printf("====================\n");

        // tampil dompet
        jmlDompet = getDompet(username, true);
        printf("====================\n");

        printf("Nama Dompet\t: \n");
        printf("Saldo Awal\t: ");
        formatRupiah(saldo);
        printf("\n");
        gotoxy(19, 4 + jmlDompet + 2);

        do {
            key = getch();

            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 20)) {
                if (p == 1) {
                    namadompet[n] = key;
                    n++;
                    printf("%c", key);
                    gotoxy(19 + n, 5 + p + jmlDompet);
                } else if ((p == 2) && (key >= '0' && key <= '9') && (n < 9)) {
                    if (!(n == 0 && key == '0')) {
                        saldoawal[n] = key;
                        n++;
                        sscanf(saldoawal, "%d", &saldo);
                        // gotoxy(19, 5 + p + jmlDompet);
                        // formatRupiah(saldo);
                        // gotoxy(19 + getLengthFormatRupiah(saldo) + 2, 5 + p + jmlDompet);

                        gotoxy(19, 5 + p + jmlDompet);
                        printf("                  ");
                        gotoxy(19, 5 + p + jmlDompet);
                        formatRupiah(saldo);
                        gotoxy(19 + getLengthFormatRupiah(saldo) + 2, 5 + p + jmlDompet);
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
                        gotoxy(19 + n + 2, 5 + p + jmlDompet);
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
                        // // Remove the last character from saldoawal
                        // saldoawal[n] = '\0';

                        // // Move the cursor back, overwrite with a space, then move back again
                        // gotoxy(19 + n, 5 + p + jmlDompet);
                        // printf(" ");
                        // gotoxy(19 + n, 5 + p + jmlDompet);

                        saldoawal[n] = '\0';
                        if (saldoawal[0] == '\0') {
                            saldo = 0;
                        } else {
                            sscanf(saldoawal, "%d", &saldo);
                        }
                        // gotoxy(19, 5 + p + jmlDompet);
                        // formatRupiah(saldo);
                        // gotoxy(19 + getLengthFormatRupiah(saldo) + 2, 5 + p + jmlDompet);

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
    char key, initiate = 1, j;

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
        j = 0;

        // Display ASCII 254 in the first row
        if (initiate == 1) {
            printf("%c ", 254);
        } else {
            printf("  ");  // Spaces to maintain alignment for other rows
        }

        // Membaca file untuk mencari ID yang kosong
        while (fread(&dom, sizeof(struct Wallet), 1, file) == 1) {
            if (strcmp(dom.nama_dompet, "") != 0) {
                if (j == 0) {
                    gotoxy(1, 5);
                }

                // Check if in the first row to keep ASCII 254
                if (j == 0 && initiate == 1) {
                    printf("%c %s, ", 254, dom.nama_dompet);
                } else {
                    printf("%c %s, ", (current_selection == dom.id || initiate == 1) ? 254 : ' ', dom.nama_dompet);
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
        printf("\n%c Kembali", (current_selection == getLastIDDompet(username) + 1) ? 254 : ' ');

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

void tampilMenuUbahNamaDompet(char username[20]) {
    int current_selection = 1, jmlDompet = 0;
    char key, initiate = 1, j;

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("User: %s\n", username);
    printf("====================\n");
    printf("Pilih dompet yang akan diubah namanya\n");

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
        j = 0;

        // Display ASCII 254 in the first row
        if (initiate == 1) {
            printf("%c ", 254);
        } else {
            printf("  ");  // Spaces to maintain alignment for other rows
        }

        // Membaca file untuk mencari ID yang kosong
        while (fread(&dom, sizeof(struct Wallet), 1, file) == 1) {
            if (strcmp(dom.nama_dompet, "") != 0) {
                if (j == 0) {
                    gotoxy(1, 5);
                }

                // Check if in the first row to keep ASCII 254
                if (j == 0 && initiate == 1) {
                    printf("%c %s, ", 254, dom.nama_dompet);
                } else {
                    printf("%c %s, ", (current_selection == dom.id || initiate == 1) ? 254 : ' ', dom.nama_dompet);
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

        printf("\n%c Kembali", (current_selection == getLastIDDompet(username) + 1) ? 254 : ' ');

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
        printf("MONEY TRACKING APP\n");
        printf("Ubah Nama Dompet \"%s\"\n", getNamaDompet(username, id_dompet));
        printf("====================\n");
        printf("Nama Baru: \n");

        gotoxy(12, 4);

        do {
            key = getch();

            if (((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || (key == ' ')) && (n < 20)) {
                namabaru[n] = key;
                n++;
                printf("%c", key);
                gotoxy(12 + n, 4);
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
