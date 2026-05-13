
#define _CRT_SECURE_NO_WARNINGS
#include "Valute.h"
#include <stdbool.h>

int main() {

	int izbor;
	bool radi = true;

	while (radi)
	{
		printf("\n=== KALKULATOR VALUTA ===\n");
		printf("\nSvi tecajevi su prikazani u odnosu na EUR (1 EUR = X VALUTA)\n");
		printf("\n");
		printf("1. Dodaj novu valutu (CREATE):\n");
		printf("2. Prikazi sve valute (READ):\n");
		printf("3. Azuriraj tecaj valute (UPDATE):\n");
		printf("4. Izlaz\n");
		scanf("%d", &izbor);


		switch ((IzbornikOpcije)izbor)
		{
		case DODAJ:
			dodajValutu(); break;
		case PRIKAZI:
			prikaziValute(); break;
		case AZURIRAJ:
			azurirajValutu(); break;
		case IZLAZ:
			radi = false; break;
		default:
			printf("Neispravan odabir.\n");

		}
	}

	return 0;
}
