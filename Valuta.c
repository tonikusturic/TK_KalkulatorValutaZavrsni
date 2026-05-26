#define _CRT_SECURE_NO_WARNINGS
#include "valuta.h"
#include "util.h"
#include <string.h>
#include <errno.h>


static const char* PUTANJA_DATOTEKE = "valute.txt";
static const int MAX_VALUTA = 100;

int brojacDodavanja = 0;

/* ------------------ CREATE ------------------ */
void dodajValutu() {
    FILE* dat = fopen(PUTANJA_DATOTEKE, "a");
    if (!dat) {
        perror("Greska otvaranja datoteke");
        return;
    }

    Valuta nova;
    printf("Unesi kod valute: ");
    
    if (scanf("%3s", nova.kod) != 1)
    {
        printf("Greska, unesena kriva vrijednost.\n");
    }

    printf("Unesi tecaj prema EUR: ");
  
    printf("Unesi tecaj prema EUR: ");

    if (scanf("%lf", &nova.tecaj) != 1)
    {
        printf("Greska, unesena kriva vrijednost.\n");
    }
    

    fprintf(dat, "%s %.2lf\n", nova.kod, nova.tecaj);
    fclose(dat);

    brojacDodavanja++;
    printf("Valuta dodana! Ukupno dodano: %d\n", brojacDodavanja);
}

/* ------------------ READ ------------------ */
void prikaziValute() {
    FILE* dat = fopen(PUTANJA_DATOTEKE, "r");
    if (!dat) {
        perror("Greska otvaranja datoteke");
        return;
    }
    fseek(dat, 0, SEEK_END);
    long velicina = ftell(dat);
    rewind(dat);

    printf("Velicina datoteke: %ld bajtova\n", velicina);

    Valuta temp;
    Valuta* lista = sigurnoAlociraj(sizeof(Valuta) * MAX_VALUTA);

    int broj = 0;

    printf("\n--- POPIS VALUTA ---\n");
    while (fscanf(dat, "%3s %lf", temp.kod, &temp.tecaj) == 2) {
        printf("%s %.2lf\n", temp.kod, temp.tecaj);
        lista[broj++] = temp;
    }

    printf("Prosjecni tecaj: %.3lf\n", prosjecniTecaj(lista, broj));

    free(lista);
    fclose(dat);
}

/* ------------------ UPDATE ------------------ */
void azurirajValutu() {
    Valuta* lista = NULL;
    int broj = ucitajSveValute(&lista);
    if (broj == 0) {
        printf("Nema valuta.\n");
        return;
    }

    char kodValute[4];
    printf("Unesi kod za azuriranje: ");

    if (scanf("%3s", kodValute) != 1)
    {
        printf("Greska, unesena kriva vrijednost.\n");
    }


    for (int i = 0; i < broj; i++) {
        if (strcmp(lista[i].kod, kodValute) == 0) {
            printf("Unesi novi tecaj: ");

            if (scanf("%lf", &lista[i].tecaj))
            {
                printf("Greska, unesena kriva vrijednost.\n");
            }

            spremiSveValute(lista, broj);
            free(lista);
            printf("Azurirano.\n");
            return;
        }
    }

    printf("Valuta nije pronadena.\n");
    free(lista);
}

/* ------------------ DELETE ------------------ */
void obrisiValutu() {
    Valuta* lista = NULL;
    int broj = ucitajSveValute(&lista);
    if (broj == 0) return;

    char kodValute[4];
    printf("Unesi kod za brisanje: ");

    if (scanf("%3s", kodValute) != 1)
    {
        printf("Greska, unesena kriva vrijednost.\n");
    }
    

    int noviBroj = 0;
    for (int i = 0; i < broj; i++) {
        if (strcmp(lista[i].kod, kodValute) != 0)
            lista[noviBroj++] = lista[i];
    }

    spremiSveValute(lista, noviBroj);
    free(lista);
    printf("Valuta obrisana.\n");
}

/* ------------------ SORT ------------------ */
void sortirajValute() {
    Valuta* lista = NULL;
    int broj = ucitajSveValute(&lista);

    qsort(lista, broj, sizeof(Valuta), usporedbaTecajeva);

    spremiSveValute(lista, broj);
    free(lista);

    printf("Sortirano po tecaju.\n");
}

int usporedbaTecajeva(const void* a, const void* b) {
    const Valuta* v1 = (const Valuta*)a;
    const Valuta* v2 = (const Valuta*)b;
    return (v1->tecaj > v2->tecaj) - (v1->tecaj < v2->tecaj);
}

/* ------------------ SEARCH (rekurzija) ------------------ */
int rekurzivnoTrazi(Valuta* lista, int broj, const char* kodValute) {
    if (broj == 0) return -1;
    if (strcmp(lista[broj - 1].kod, kodValute) == 0)
        return broj - 1;

    return rekurzivnoTrazi(lista, broj - 1, kodValute);
}

void traziValutu() {
    Valuta* lista = NULL;
    int broj = ucitajSveValute(&lista);

    static char zadnjiKod[4]; 

    char trazeniKod[4];
    printf("Unesi kod za trazenje: ");

    if (scanf("%3s", trazeniKod) != 1)
    {
        printf("Greska, unesena kriva vrijednost.\n");
    }
    

    int indeks = rekurzivnoTrazi(lista, broj, trazeniKod);

    if (indeks >= 0)
        printf("Pronadena %s (tecaj %.3lf)\n", lista[indeks].kod, lista[indeks].tecaj);
    else
        printf("Valuta nije pronadena.\n");

    strcpy(zadnjiKod, trazeniKod);
    printf("Zadnji trazeni kod: %s\n", zadnjiKod);

    free(lista);
}

/* ------------------ CONVERSION ------------------ */
void konvertirajValutu() {
    Valuta* lista = NULL;
    int broj = ucitajSveValute(&lista);

    char kodIz[4], kodU[4];
    double iznos;


    printf("Unesi kod FROM: ");
    if (scanf("%3s", kodIz) != 1)
    {
        printf("Greska, unesena kriva vrijednost.\n");
    }
    printf("Unesi kod TO: ");
    if (scanf("%3s", kodU) != 1)
    {
        printf("Greska, unesena kriva vrijednost.\n");
    }
    printf("Unesi iznos: ");
    if (scanf("%lf", &iznos) != 1)
    {
        printf("Greska, unesena kriva vrijednost.\n");
    }
   

    double tecajIz = -1, tecajU = -1;

    for (int i = 0; i < broj; i++) {
        if (strcmp(lista[i].kod, kodIz) == 0) tecajIz = lista[i].tecaj;
        if (strcmp(lista[i].kod, kodU) == 0) tecajU = lista[i].tecaj;
    }

    if (tecajIz == -1 || tecajU == -1) {
        printf("Valuta ne postoji.\n");
        free(lista);
        return;
    }

    double rezultat = iznos * (tecajU / tecajIz);
    printf("%.2lf %s = %.2lf %s\n", iznos, kodIz, rezultat, kodU);

    free(lista);
}

/* ------------------ REMOVE() funkcija ------------------ */
void resetirajDatoteku() {
    if (remove(PUTANJA_DATOTEKE) == 0)
        printf("Datoteka obrisana.\n");
    else
        perror("Brisanje nije uspjelo");
}

/* ------------------ LOADING AND SAVING ------------------ */
int ucitajSveValute(Valuta** lista) {
    FILE* dat = fopen(PUTANJA_DATOTEKE, "r");
    if (!dat) {
        perror("Greska pri otvaranju");
        return 0;
    }

    *lista = sigurnoAlociraj(sizeof(Valuta) * MAX_VALUTA);

    int broj = 0;
    while (fscanf(dat, "%3s %lf", (*lista)[broj].kod, &(*lista)[broj].tecaj) == 2)
        broj++;

    fclose(dat);
    return broj;
}

void spremiSveValute(Valuta* lista, int broj) {
    FILE* dat = fopen(PUTANJA_DATOTEKE, "w");
    if (!dat) {
        perror("Greska upisa");
        return;
    }

    for (int i = 0; i < broj; i++)
        fprintf(dat, "%s %.2lf\n", lista[i].kod, lista[i].tecaj);

    fclose(dat);
}

/* ------------------ AVERAGE ------------------ */
double prosjecniTecaj(Valuta* lista, int broj) {
    if (broj == 0) return 0;

    double suma = 0;
    for (int i = 0; i < broj; i++)
        suma += lista[i].tecaj;

    return suma / broj;
}

