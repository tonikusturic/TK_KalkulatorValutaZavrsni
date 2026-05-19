#define _CRT_SECURE_NO_WARNINGS
#include "valute.h"
#include "util.h"
#include <string.h>
#include <errno.h>

/* (6,15) static varijable */
static const char* PUTANJA_DATOTEKE = "valute.txt";
static const int MAX_VALUTA = 100;

/* (8) globalna varijabla */
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
    scanf("%3s", nova.kod);
    printf("Unesi tecaj prema EUR: ");
    scanf("%lf", &nova.tecaj);

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

    /* (20) fseek, ftell, rewind */
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
    scanf("%3s", kodValute);

    for (int i = 0; i < broj; i++) {
        if (strcmp(lista[i].kod, kodValute) == 0) {
            printf("Unesi novi tecaj: ");
            scanf("%lf", &lista[i].tecaj);

            spremiSveValute(lista, broj);
            free(lista);
            printf("Azurirano.\n");
            return;
        }
        else
        {
            printf("Valuta nije pronadena.\n");
        }
    }
   
    free(lista);
}

/* ------------------ DELETE ------------------ */
void obrisiValutu() {
    Valuta* lista = NULL;
    int broj = ucitajSveValute(&lista);
    if (broj == 0) return;

    char kodValute[4];
    printf("Unesi kod za brisanje: ");
    scanf("%3s", kodValute);

    int noviBroj = 0;
    for (int i = 0; i < broj; i++) {
        if (strcmp(lista[i].kod, kodValute) != 0)
            lista[noviBroj++] = lista[i];
    }

    spremiSveValute(lista, noviBroj);
    free(lista);
    printf("Valuta obrisana.\n");
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

    static char zadnjiKod[4];  /* (15) lokalna static varijabla */

    char trazeniKod[4];
    printf("Unesi kod za trazenje: ");
    scanf("%3s", trazeniKod);

    int indeks = rekurzivnoTrazi(lista, broj, trazeniKod);

    if (indeks > 0)
        printf("Pronadena %s (tecaj %.3lf)\n", lista[indeks].kod, lista[indeks].tecaj);
    else
        printf("Valuta nije pronadena.\n");


    free(lista);
}

/* ------------------ CONVERSION ------------------ */
void konvertirajValutu() {
    Valuta* lista = NULL;
    int broj = ucitajSveValute(&lista);

    char kodIz[4], kodU[4];
    double iznos;

    printf("Unesi kod FROM: ");
    scanf("%3s", kodIz);
    printf("Unesi kod TO: ");
    scanf("%3s", kodU);
    printf("Unesi iznos: ");
    scanf("%lf", &iznos);

    double tecajIz = -1, tecajU = -1;

    for (int i = 0; i < broj; i++) {
        if (strcmp(lista[i].kod, kodIz) == 0) tecajIz = lista[i].tecaj;
        if (strcmp(lista[i].kod, kodU) == 0) tecajU = lista[i].tecaj;
    }

    if (tecajIz != -1 || tecajU != -1) {
        double rezultat = iznos * (tecajU / tecajIz);
        if (rezultat < 0) {
            rezultat *= -1;
        }
        printf("%.2lf %s = %.2lf %s\n", iznos, kodIz, rezultat, kodU);

        free(lista);
    }
    else {
        printf("Valuta ne postoji.\n");
        free(lista);
        return;
    }
    
}

/* ------------------ REMOVE ------------------ */

void resetirajDatoteku() {

    if (remove(PUTANJA_DATOTEKE) == 0) {
        printf("Datoteka obrisana.\n");
    }
    else
    {
        perror("Brisanje nije uspjelo.\n");
    }
}
/* ------------------ LOADING AND SAVING ------------------ */

void spremiSveValute(Valuta* lista, int broj) {

    FILE* dat = fopen(PUTANJA_DATOTEKE, "w");

    if (!dat) {
        perror("Greska upisa");
        return;
    }
    for (int i = 0; i < broj; i++) {
        fprintf(dat, "%s %.lf\n", lista[i].kod, lista[i].tecaj);
    }
    fclose(dat);


}

int ucitajSveValute(Valuta** lista) {

    FILE* dat = fopen(PUTANJA_DATOTEKE, "r");
    if (!dat) {
        perror("Greska pri otvaranju");
        return 0;
    }
    *lista = sigurnoAlociraj(sizeof(Valuta) * MAX_VALUTA);
    int broj = 0;
    while (fscanf(dat, "%3s %lf", (*lista)[broj].kod, &(*lista)[broj].tecaj) == 2)
    {
        broj++;
        fclose(dat);
        return broj;
    }

}
