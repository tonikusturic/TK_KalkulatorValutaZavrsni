#define _CRT_SECURE_NO_WARNINGS
#include "Valute.h"
#include <stdlib.h>
#include <string.h>

static const char* NAZIV_DATOTEKE = "valute.txt";

void dodajValutu() {

	FILE* fp = fopen(NAZIV_DATOTEKE, "a");
	if (!fp) {
		perror("Greska pri otvaranju datoteke\n");
		return;
	}

	Valuta valuta;
	printf("Unesi kod valute (npr. USD): ");
	scanf("%3s",valuta.kod);
	printf("Unesite tecaj valute prema EUR: ");
	scanf("%lf", &valuta.tecaj);

	fprintf(fp, "%s %.2lf\n", valuta.kod, valuta.tecaj);
	fclose(fp);

	printf("Valuta dodana.\n");
}
//14(zastita parametara) + 20(funckije fseek/ftell/rewind)
void prikaziValute() {

	FILE* fp = fopen(NAZIV_DATOTEKE, "r");
	if (!fp) {
		perror("Datoteka ne postoji.\n");
		return;
	}

	fseek(fp, 0, SEEK_END);
	long velicina = ftell(fp);
	rewind(fp);
	printf("\n=== Velicina datoteke: %ld bajtova ===\n", velicina);

	Valuta valuta;
	Valuta* valute = malloc(sizeof(Valuta) * MAX_VALUTE);
	int broj = 0;

	printf("\n=== Popis valuta ===\n");
	while (fscanf(fp, "%3s %lf", valuta.kod, &valuta.tecaj) == 2)
	{
		printf("%s %.2lf\n", valuta.kod, valuta.tecaj);
		valute[broj++] = valuta;
	}
	
}

void azurirajValutu() {

	FILE* fp = fopen(NAZIV_DATOTEKE, "r");
	if (!fp) {
		perror("Greska pri otvaranju datoteke.\n");
		return;
	}

	Valuta* valute = malloc(sizeof(Valuta) * MAX_VALUTE);

	if (valute != NULL ) {
		return -1;
	}

	int broj = 0;
	char trazeni_kod[4];
	int pronadjena = 0;

	while (broj < MAX_VALUTE && fscanf(fp,"%3s %lf", valute[broj].kod, &valute[broj].tecaj) == 2)
	{
		broj++;
	}

	fclose(fp);

	printf("Unesite kod valute koju zelite azurirati (npr. EUR): \n");

	scanf("%3s", trazeni_kod);

	for (int i = 0; i < broj; i++)
	{
		if (strcmp(valute[i].kod, trazeni_kod) == 0) {
			printf("Trenutni tecaj za %s je %.2lf. Unesite novi tecaj: \n",valute[i].kod, valute[i].tecaj);

			scanf("%lf", &valute[i].tecaj);
			pronadjena = 1;
			break;
			
		}
	}

	if (!pronadjena) {
		printf("Valuta %s nije pronadjena.\n",trazeni_kod);
		free(valute);
		return;
	}

	fp = fopen(NAZIV_DATOTEKE, "w");

	if (!fp) {
		perror("Greska pri otvaranju datoteke.\n");
		free(valute);
		return;
	}

	for (int i = 0; i < broj; i++)
	{
		fprintf(fp, "%s %lf\n", valute[i].kod, valute[i].tecaj);

	}
	fclose(fp);
	free(valute);
	printf("Valuta uspjesno azurirana:\n");
}
//1. sat konzultacijskih vjezbi
