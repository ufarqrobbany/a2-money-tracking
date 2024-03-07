#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Wallet {
    int id;
    char nama_dompet[20];
    int saldo;
};

void buatDompetAwal(char username[20]);

// getSaldo
int getSaldoDompet(char username[20], int id_dompet);
// getTotalSaldo
int getTotalSaldo(char username[20]);
// kurangiSaldo
// tambahSaldo
int getDompet(char username[20], bool display);
int tambahDompet(char username[20], char nama_dompet[20], int saldo_awal);
