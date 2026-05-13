#include <stdio.h>

float tambah(float a, float b);
float kurang(float a, float b);
float kali(float a, float b);
float bagi(float a, float b);

int main() {
    int menu;
    float bil1, bil2;

    printf("Menu Kalkulator:\n1. Penjumlahan\n2. Pengurangan\n3. Perkalian\n4. Pembagian\nPilih menu: ");
    scanf("%d", &menu);

    printf("Masukkan bilangan pertama: ");
    scanf("%f", &bil1);
    printf("Masukkan bilangan kedua: ");
    scanf("%f", &bil2);

    printf("--------------------\n");
    switch(menu) {
        case 1: printf("Hasil Penjumlahan: %.2f\n", tambah(bil1, bil2)); break;
        case 2: printf("Hasil Pengurangan: %.2f\n", kurang(bil1, bil2)); break;
        case 3: printf("Hasil Perkalian: %.2f\n", kali(bil1, bil2)); break;
        case 4: 
            if(bil2 != 0) printf("Hasil Pembagian: %.2f\n", bagi(bil1, bil2));
            else printf("Error: Pembagi tidak boleh nol!\n");
            break;
        default: printf("Menu tidak tersedia.\n");
    }
    printf("--------------------\n");

    return 0;
}

float tambah(float a, float b) { return a + b; }
float kurang(float a, float b) { return a - b; }
float kali(float a, float b) { return a * b; }
float bagi(float a, float b) { return a / b; }

