#include <time.h>

struct Data {
    time_t tanggal;
    char jenis[20];
    int harga;
    int sisa_saldo;
};

void catatData(struct Data data);