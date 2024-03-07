#include "menu.h"

#include "account.h"
#include "common.h"

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
    printf("Saldo: \n");
    printf("Pengeluaran Bulan Ini: \n");

    // isi
    do {
        gotoxy(1, 6);
        printf("%c Catat\n", (current_selection == 1) ? 254 : ' ');
        printf("%c Rekap\n", (current_selection == 2) ? 254 : ' ');
        printf("%c dompet\n", (current_selection == 3) ? 254 : ' ');
        printf("%c keluar\n", (current_selection == 4) ? 254 : ' ');

        // navigasi menu
        key = getch();

        if ((key == 72) && (current_selection > 1)) {
            current_selection -= 1;
        } else if ((key == 80) && (current_selection < 3)) {
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
    } while (key != 14);
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
<<<<<<< Updated upstream
void tampilMenuDompet(char username[20]){
	int current_selection = 1;
=======

void tampilMenuDompet(char username[20]) {
    int current_selection = 1;
>>>>>>> Stashed changes
    char key;

    clearScreen();
    // print header
    printf("MONEY TRACKING APP\n");
    printf("User: %s\n", username);
    printf("====================\n");
    
    //tampil dompet

    // isi
    do {
<<<<<<< Updated upstream
        
=======
        gotoxy(1, 4);
>>>>>>> Stashed changes
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
                    // panggil prosedur tambah dompet
                    break;
                case 2:
                    // panggil prosedur hapus dompet
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
