#pragma once
#ifndef VALUTA_H
#define VALUTA_H
#define MAX_VALUTE 100
#define MAX_VALUTE 100

#include <stdio.h>

typedef struct {

	char kod[4];
	double tecaj;
} Valuta;

typedef enum {

	DODAJ = 1, PRIKAZI, AZURIRAJ, IZLAZ
}IzbornikOpcije;

void dodajValutu();
void prikaziValute();
void azurirajValutu();
#endif // !VALUTA_H
