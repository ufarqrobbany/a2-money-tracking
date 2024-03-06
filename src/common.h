// File header umum yang mungkin berisi definisi konstanta, dan fungsi utilitas yang digunakan secara global di proyek.
#include <conio.h>
#include <stdio.h>
#include <windows.h>


#ifndef COMMON_H
#define COMMON_H

void gotoxy(int x, int y);
void clearScreen();

// Function declarations
void reverse(char str[], int length);
char* formatRupiah(int value);

#endif  // COMMON_H);
