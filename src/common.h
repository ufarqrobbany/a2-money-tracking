// File header umum yang mungkin berisi definisi konstanta, dan fungsi utilitas yang digunakan secara global di proyek.
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void gotoxy(int x, int y);
void clearScreen();
void reverse(char str[], int length);
char* formatRupiah(int value);
char* formatUang(char *uang);
