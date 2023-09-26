#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct YeniOyun {
    char ad[100];
    float fiyat;
    float kullaniciDegerlendirmesi;
};

FILE *dosya;
FILE *gecici;

void oyunEkle() // Bu b�l�mde fopen i�ersinde varolan veya yeni a��lan kay�t dosyas�na yeni bilgiler eklemeyimizi sa�l�yor.
{
    system("cls");
    if ((dosya = fopen("oyunKutuphanesi.txt", "a")) != NULL)
    {
        struct YeniOyun oyun;
        
        // OYUN KAYDEDERKEN OYUN �SM� B�RKA� KEL�MEDEN OLU�UYORSA ARAYA BO�LUK YER�NE ALT T�RE (_) KOYULMALI. AKS� TAKT�RDE KOD HER B�R KEL�MEY� AYRI KAYDED�YOR.
        
        printf("Oyun Bilgilerini Giriniz:\n");
        printf("Oyun adi: "); 
        scanf("%s", oyun.ad);
        printf("Oyun fiyati: ");
        scanf("%f", &oyun.fiyat);
        printf("Oyunun kullanici degerlendirmesi: ");
        scanf("%f", &oyun.kullaniciDegerlendirmesi);

        fprintf(dosya, "%s\t%.2f\t%.2f\n", oyun.ad, oyun.fiyat, oyun.kullaniciDegerlendirmesi);
        fclose(dosya);
        printf("Kayit islemi tamamlandi.\n");
    }
    else
    {
        printf("Dosya acilamadi.\n");
    }
}

void oyunListele() // Dosyaya kaydedilen bilgileri �al��an komut sat�r�nda listeleyerek ekrana getirmeye yar�yor.
{
    rewind(dosya);
    system("cls");
    if ((dosya = fopen("oyunKutuphanesi.txt", "r")) != NULL)
    {
		printf("Eklenen Oyunlarin bilgileri\n");
		printf("Oyun isimleri\t");
        printf("Fiyatlari\t");
        printf("Kullanici Degerlendirmeleri\n");
        struct YeniOyun oyun;
        while (fscanf(dosya, "%s\t%f\t%f\n", oyun.ad, &oyun.fiyat, &oyun.kullaniciDegerlendirmesi) != EOF)
        {
            printf("%s\t%.2f\t%.2f\n", oyun.ad, oyun.fiyat, oyun.kullaniciDegerlendirmesi);
        }
        
        fclose(dosya);
    }
    else
    {
        printf("Dosya acilamadi.\n");
    }
}

void oyunAra() // Kay�tl� verilerden aras�ndan oyun ad� girerek aranan i�eri�i bulmam�z� sa�l�yor.
{
    system("cls");
    char isim[100];
    int sonuc = 0;
    
    if ((dosya = fopen("oyunKutuphanesi.txt", "r")) != NULL)
    {
        printf("Aramak istediginiz oyunun adi: ");
        scanf("%s", isim);
        
        printf("Aranan oyunun bilgileri:\n");
        printf("Oyun Adi\tFiyat\tDegerlendirme\n");
        
        struct YeniOyun oyun;
        while (fscanf(dosya, "%s\t%f\t%f\n", oyun.ad, &oyun.fiyat, &oyun.kullaniciDegerlendirmesi) != EOF)
        {
            if (strcmp(oyun.ad, isim) == 0)
            {
                printf("%s\t%.2f\t%.2f\n", oyun.ad, oyun.fiyat, oyun.kullaniciDegerlendirmesi);
                sonuc = 1;
            }
        }
        
        fclose(dosya);
    }
    
    if (sonuc == 0)
    {
        printf("%s isimli oyun listede bulunamadi.\n", isim);
    }
}

void yedekle()
{
    if ((gecici = fopen("yedek.txt", "w")) != NULL)
    {
        if ((dosya = fopen("oyunKutuphanesi.txt", "r")) != NULL)
        {
            struct YeniOyun oyun;
            while (fscanf(dosya, "%s\t%f\t%f\n", oyun.ad, &oyun.fiyat, &oyun.kullaniciDegerlendirmesi) != EOF)
            {
                fprintf(gecici, "%s\t%.2f\t%.2f\n", oyun.ad, oyun.fiyat, oyun.kullaniciDegerlendirmesi);
            }
        }
        
        remove("oyunKutuphanesi.txt");
        fclose(dosya);
        fclose(gecici);
    }
}

void guncelle(char *ptr) // strcmp stringi ile kar��la�t�rma yap�yor farkl�l�k tespit edilirse yeni veri g�ncelleniyor
{	 
    if ((dosya = fopen("oyunKutuphanesi.txt", "w")) != NULL)
    {
        if ((gecici = fopen("yedek.txt", "r")) != NULL)
        {
            struct YeniOyun oyun;
            while (fscanf(gecici, "%s\t%f\t%f\n", oyun.ad, &oyun.fiyat, &oyun.kullaniciDegerlendirmesi) != EOF)
            {
                if (strcmp(ptr, oyun.ad) == 0) 
                    continue;
                
                fprintf(dosya, "%s\t%.2f\t%.2f\n", oyun.ad, oyun.fiyat, oyun.kullaniciDegerlendirmesi);
            }
        }
        
        remove("yedek.txt");
        fclose(dosya);
        fclose(gecici);
        rewind(dosya);
    }
}

void oyunSil() // Kay�tl� verileri silmek i�in kullan�lan b�l�m.
{
    system("cls");
    char isim[100];
    int sonuc = 0;
    
    if ((dosya = fopen("oyunKutuphanesi.txt", "r")) != NULL)
    {
        printf("Silmek istediginiz oyunun adi: ");
        scanf("%s", isim);
        
        printf("Aranan Oyun Bilgileri\n");
        printf("Oyun Adi\tFiyat\tDegerlendirme\n");
        
        struct YeniOyun oyun;
        while (fscanf(dosya, "%s\t%f\t%f\n", oyun.ad, &oyun.fiyat, &oyun.kullaniciDegerlendirmesi) != EOF)
        {
            if (strcmp(oyun.ad, isim) == 0)
            {
                fclose(dosya);
                yedekle();
                guncelle(isim);
                sonuc = 1;
                break;
            }
        }
        
        fclose(dosya);
    }
    
    if (sonuc == 0)
    {
        printf("%s isimli oyun listede bulunamadi.\n", isim);
    }
    else
    {
        printf("Silme islemi basarili.\n");
    }
}

int main()
{
	struct YeniOyun oyun;
    int secim = -1;
    printf("Dikkat! Lutfen Oyun ismi girerken arada bosluk kullanmayiniz (ORNEK-) oyun adi= isim1_isim2 seklinde. )");
    while (secim != 0)
    {
        printf("\n1) Yeni kayit ekle\n");
        printf("2) Listele\n");
        printf("3) Arama\n");
        printf("4) Silme\n");
        printf("0) Cikis\n");
        printf("Seciminizi giriniz: ");
        scanf("%d", &secim);

        switch (secim)
        {
            case 1:
                oyunEkle();
                break;
            case 2:
                oyunListele();
                break;
            case 3:
                oyunAra();
                break;
            case 4:
                oyunSil();
                break;
            case 0:
                printf("Cikis yapildi.\n");
                break;
            default:
                printf("Hatali secim.\n");
                break;
        }
    }
    
    return 0;
}

