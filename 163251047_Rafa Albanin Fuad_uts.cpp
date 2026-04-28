#include <stdio.h>

int main() {
    char tipe_user[20];
    int lantai_awal, lantai_tujuan;
    int lift1 = 2, lift2 = 7, lift3 = 5, lift4 = 7, lift5 = 10; 
    int jarak1, jarak2, jarak3, jarak4, jarak5;
    int lift_terdekat, jarak_minimal;

   
    printf("Masukkan tipe user: ");
    scanf("%s", tipe_user);
    
    printf("Masukkan lantai saat ini: ");
    scanf("%d", &lantai_awal);

    printf("Masukkan lantai tujuan: ");
    scanf("%d", &lantai_tujuan);

    
    if (lantai_awal < 1 || lantai_awal > 10 || lantai_tujuan < 1 || lantai_tujuan > 10) {
        printf("Input lantai salah!.\n");
        return 0; 
    }


    printf("\nPosisi Lift 1: %d", lift1);
    printf("\nPosisi Lift 2: %d", lift2);
    printf("\nPosisi Lift 3: %d", lift3);
    printf("\nPosisi Lift 4: %d", lift4);
    printf("\nPosisi Lift 5: %d\n", lift5);


    jarak1 = lantai_awal - lift1; if(jarak1 < 0) jarak1 = -jarak1;
    jarak2 = lantai_awal - lift2; if(jarak2 < 0) jarak2 = -jarak2;
    jarak3 = lantai_awal - lift3; if(jarak3 < 0) jarak3 = -jarak3;
    jarak4 = lantai_awal - lift4; if(jarak4 < 0) jarak4 = -jarak4;
    jarak5 = lantai_awal - lift5; if(jarak5 < 0) jarak5 = -jarak5;

   
    jarak_minimal = jarak1;
    lift_terdekat = 1;

    if (jarak2 < jarak_minimal) { jarak_minimal = jarak2; lift_terdekat = 2; }
    if (jarak3 < jarak_minimal) { jarak_minimal = jarak3; lift_terdekat = 3; }
    if (jarak4 < jarak_minimal) { jarak_minimal = jarak4; lift_terdekat = 4; }
    if (jarak5 < jarak_minimal) { jarak_minimal = jarak5; lift_terdekat = 5; }


    printf("\nLift %d lebih dekat ke posisi Anda.", lift_terdekat);
    printf("\nRekomendasi: Gunakan Lift %d.\n", lift_terdekat);
    
    printf("\nUser tipe %s akan menggunakan Lift %d dari lantai %d ke lantai %d.\n", 
           tipe_user, lift_terdekat, lantai_awal, lantai_tujuan);

    return 0;
}
