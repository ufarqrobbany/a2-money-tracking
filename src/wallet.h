#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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
int getLastIDDompet(char username[20]);
int getFirstNonEmptyID(int idKosong[], int kosong, int lastID);
int getDompet(char username[20], bool display);
int tambahDompet(char username[20], char nama_dompet[20], int saldo_awal);
int hapusDompet(char username[20], int id_dompet);
char *getNamaDompet(char username[20], int id_dompet);
int isIdInKosong(int id, int idKosong[], int kosong);
int ubahNamaDompet(char username[20], int id_dompet, char namabaru[20]);