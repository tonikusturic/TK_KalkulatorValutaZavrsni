#define _CRT_SECURE_NO_WARNINGS
#include "valuta.h"
#include <stdbool.h>

int main() {
    int izbor;
    bool radi = true;

    while (radi) {
        printf("\n === KALKULATOR VALUTA ===\n");
        printf(" Svi tecajevi su u odnosu na EUR \n");

        printf(" 1. Dodaj valutu \n");
        printf(" 2. Prikazi valute \n");
        printf(" 3. Azuriraj valutu \n");
        printf(" 4. Obrisi valutu \n");
        printf(" 5. Sortiraj valute \n");
        printf(" 6. Trazi valutu \n");
        printf(" 7. Konvertiraj iznos \n");
        printf(" 8. Resetiraj datoteku \n");
        printf(" 9. Izlaz \n");

        printf(" Odabir: ");
        if (scanf("%d", &izbor)!= 1)
        {
            printf("Greska, unesena kriva vrijednost.\n");
                return 1;
        }

        switch ((IzbornikOpcija)izbor) {
        case IZBORNIK_DODAJ: dodajValutu(); break;
        case IZBORNIK_PRIKAZI: prikaziValute(); break;
        case IZBORNIK_AZURIRAJ: azurirajValutu(); break;
        case IZBORNIK_OBRISI: obrisiValutu(); break;
        case IZBORNIK_SORTIRAJ: sortirajValute(); break;
        case IZBORNIK_TRAZI: traziValutu(); break;
        case IZBORNIK_KONVERTIRAJ: konvertirajValutu(); break;
        case IZBORNIK_RESET: resetirajDatoteku(); break;
        case IZBORNIK_IZLAZ: radi = false; break;
        default: printf("Neispravan unos!\n");
        }
    }

    return 0;
}
