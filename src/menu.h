#include <stdio.h>

void tampilMenuAwal();
void tampilMenuLogin();
void tampilMenuDaftar();
void tampilMenuUtama(char username[20]);
void tampilMenuCatat(char username[20]);
void tampilMenuCatatPengeluaran(char username[20]);
void tampilPilihKategori(char username[20], int jenis, int nominal);
void tampilBuatKategori(char username[20], int jenis, int nominal);
void tampilPilihDompet(char username[20], int jenis, char kategori[20], int nominal);
void tampilKonfirmasiCatatPengeluaran(char username[20], int jenis, char kategori[20], int iddompet, int nominal);
void tampilMenuRekap(char username[20]);
void tampilMenuDompet(char username[20]);
void tampilMenuTambahDompet(char username[20]);
void tampilMenuHapusDompet(char username[20]);
void tampilKonfirmasiHapusDompet(char username[20], char namadompet[20], int iddompet);
void tampilMenuUbahNamaDompet(char username[20]);
void tampilMenuInputNamaDompet(char username[20], int id_dompet);