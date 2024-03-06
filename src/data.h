#include <time.h>

struct Data {
    time_t tanggal;
    char jenis[20];
    int harga;
    int sisa_saldo;
};

void catatData(struct Data data);
void HitungRekapMingguan(struct Data data[], int n, int target_week, int target_month);
int HitungSisaSaldo(struct Data data[], int n);
int LoadData(struct Data data[], const char *filename);