#include <iostream>
#include <graphics.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#define K 6

struct djikstra{
 char sehir1[50];
 char sehir2[50];
 int maliyet;
}dugum[K][K];

int sonsuz=9999;
void nedret(char bas_dugum[50],char hedef_dugum[50],int maliyet_matris[K][K]);
void ekran();
int satirno();
void konum(int no[],int matris[][2]);
void cizgi(int a[][2]);
void grafik_rota(int rota[][2]);

int main()
{
    FILE *dosya;
    dosya=fopen("Deneme2.txt","r");

    int maliyet_matris[K][K];
    char bas_dugum[50],hedef_dugum[50];
    int i,j;

    fseek(dosya, 0, SEEK_END);
    long int son=ftell(dosya); ///dosya sonuna gitti yeri söyledi
    fseek(dosya, 0, SEEK_SET);



    ///txt verisinden dugum bilgileri aktarildi
    for(i=0;i<K;i++)
    {
        for(j=0;j<K;j++)
        {
            fscanf(dosya,"%s %s %d\n",dugum[i][j].sehir1,dugum[i][j].sehir2,&dugum[i][j].maliyet);
            maliyet_matris[i][j]=dugum[i][j].maliyet;
        }
    }
    printf("A: Ankara\tB: Eskisehir\tC: Bolu\tD: Cankiri\tE: Kirsehir\tF: Kirikkale\t\n");
    printf("   A\tB\tC\tD\tE\tF\n");
    /// maliyet matrisini listeler
     for(i=0;i<K;i++)
    {
        printf("%s :",dugum[i][0].sehir1);
        for(j=0;j<K;j++)
        {
            printf("%d\t ",maliyet_matris[i][j]);
        }
        printf("\n");
    }

    printf("\nbaslangic dugumunu giriniz: ");
    scanf("%s",&bas_dugum);
    printf("hedef dugumu giriniz: ");
    scanf("%s",&hedef_dugum);

    ///enk_yol_djikstra(bas_dugum,hedef_dugum,maliyet_matris);
    nedret(bas_dugum,hedef_dugum,maliyet_matris);

    fclose(dosya);

    /// konumlari aktarir
    int satir=satirno();
    int konumxy[satir][2];
    int numara[satir];
    konum(numara,konumxy);


    /*int i;
    for(i=0;i<satir;i++)
    {
        printf("%d\tnumara: x: %d, y: %d\n",numara[i],konumxy[i][0],konumxy[i][1]);
    }*/

    ekran();
    while(1)
    {
        grafik_rota(konumxy);
    }
    getch();
    return 0;
}
int grafik_ciz[K];
int g_no=0;

void nedret(char bas_dugum[50],char hedef_dugum[50],int maliyet_matris[K][K])
{
    int guncel_dugum[K],baslangic_indisi;
    int secilen_dugum[K];
    int enkisa_dugum[K];
    int i,j,min1=10000;
    int gezilecek_dugum;
    int tekrar_kontrol[K];
    int sayac=0;
    char rota[K];
    int rota_sayac=0;
    int bitis_indisi;
    int cizim[K];
    int cizim_no=0;

        for(i=0;i<K;i++)
    {
        tekrar_kontrol[i]=0;
    }
printf("   \tA\tB\tC\tD\tE\tF\n");
    ///baslangic dugumunu guncel dizisine aktarir
    for(i=0;i<K;i++)
    {
        if(strcmp(bas_dugum,dugum[i][0].sehir1)==0)
        {
            baslangic_indisi=i;
             printf(" %s:\t",dugum[baslangic_indisi][0].sehir1);
             rota[rota_sayac]=baslangic_indisi;
             rota_sayac++;

            for(j=0;j<K;j++)
            {
                guncel_dugum[j]=maliyet_matris[i][j];
                printf("%d\t",guncel_dugum[j]);

                if(min1>guncel_dugum[j] && guncel_dugum[j]!=0)
                {
                    min1=guncel_dugum[j];
                    gezilecek_dugum=j;

                }
            }
            printf("\n");


           //  printf("min: %d",min);
        }
    }
    ///bitis dugumunu bulur
     for(i=0;i<K;i++)
    {
        if(strcmp(hedef_dugum,dugum[i][0].sehir1)==0)
        {
            bitis_indisi=i;

        }


        }

    /// secilen dugum dizisine aktarir
    tekrar_kontrol[baslangic_indisi]=1;

dugum:
    sayac=0;
    tekrar_kontrol[gezilecek_dugum]=1;

            for(j=0;j<K;j++)
            {
                secilen_dugum[j]=maliyet_matris[gezilecek_dugum][j]+min1;

            }

            for(i=0;i<K;i++)
            {
                if(secilen_dugum[i]<guncel_dugum[i])
                {
                enkisa_dugum[i]=secilen_dugum[i];
                }
                else
                {
                    enkisa_dugum[i]=guncel_dugum[i];
                }
            }
            printf(" %s:\t",dugum[gezilecek_dugum][0].sehir1);
            rota[rota_sayac]=gezilecek_dugum;
            rota_sayac++;
            for(i=0;i<K;i++)
            {
                printf("%d\t",enkisa_dugum[i]);
            }

min1=sonsuz;
           for(j=0;j<K;j++)
            {


                if(min1>enkisa_dugum[j] && enkisa_dugum[j]!=0)
                {
                    if(tekrar_kontrol[j]==0)
                    {
                        min1=enkisa_dugum[j];
                        gezilecek_dugum=j;
                    }


                }
            }


min1=maliyet_matris[baslangic_indisi][gezilecek_dugum];


            for(j=0;j<K;j++)
            {
                guncel_dugum[j]=enkisa_dugum[j];
            }
            //printf("\n tekrar kontrol\n");
        for(i=0;i<K;i++)
        {
            //printf("%d\t",tekrar_kontrol[i]);
            if(tekrar_kontrol[i]==1)
            {
                sayac++;
            }
        }



printf("\n");
               if(sayac<6)
                 {

                    goto dugum;
                 }

                    for(i=0;i<rota_sayac;i++)
                 {
                      printf(" %s:-->",dugum[rota[i]][0].sehir1);
                     if(rota[i]==bitis_indisi)
                     {
                        i=rota_sayac;

                     }
                 }

                        printf("ROTA\n\n");
                        for(i=0;i<rota_sayac;i++)
                        {
                            cizim[i]=rota[i];
                            if(rota[i]==bitis_indisi)
                            {
                                i=rota_sayac;
                            }
                        }
                            for(i=0;i<K;i++)
                            {
                                if(cizim[i]<K)
                                {
                                    grafik_ciz[g_no]=cizim[i];
                                    g_no++;
                                }
                            }

}

int satirno()
{
    FILE *dosya;
    dosya=fopen("sehir kod.txt","r");
    char sehir[50];
    int satirno=0;
    fseek(dosya, 0, SEEK_END);
    long int son=ftell(dosya); ///dosya sonuna gitti yeri söyledi
    fseek(dosya, 0, SEEK_SET);

    while(ftell(dosya)!=son){
    fscanf(dosya,"%s\n",sehir);
    satirno++;
    }
    fclose(dosya);
    return satirno;
}
void konum(int no[],int matris[][2])
{
    FILE *dosya;
    dosya=fopen("sehir konum.txt","r");

    int satir=satirno();
    int konum_xy[satir][2];
    int numara[satir];
    int i,j;
    //printf("satir no: %d\n",satir);

    for(i=0;i<satir;i++)
    {
            fscanf(dosya,"%d %d %d\n",&no[i],&matris[i][0],&matris[i][1]);
    }
   /* printf("\n");
    for(i=0;i<g_no;i++)
        printf("%d ",grafik_ciz[i]);*/
}
void ekran()
{

    initwindow(1000,514,"En Kisa Yol");
    setbkcolor(3);
    readimagefile("harita.jpg",0,0,1000,514);

    outtextxy(365,144,"A");
    outtextxy(250,150,"B");
    outtextxy(310,90,"C");
    outtextxy(400,100,"D");
    outtextxy(430,195,"E");
    outtextxy(400,150,"F");


}
void cizgi(int a[][2])
{
    setcolor(BLACK);
    setlinestyle(0,0,4);
    line(a[0][0],a[0][1],a[1][0],a[1][1]);
}
void grafik_rota(int rota[][2])
{
    int satir=satirno();
    int grafik_rota[satir];
    int grafik_rota_no=0;
    int i;
    int kontrol=0;

    int k_no=0;

  for(i=0;i<satir;i++)
    {
        grafik_rota[grafik_rota_no]=i;
        grafik_rota_no++;
    }
    while(kontrol!=(g_no-1))
    {
        setcolor(BLACK);
        setlinestyle(0,0,4);
        line(rota[grafik_ciz[kontrol]][0],rota[grafik_ciz[kontrol]][1],rota[grafik_ciz[kontrol+1]][0],rota[grafik_ciz[kontrol+1]][1]);
        kontrol++;
    }
}

