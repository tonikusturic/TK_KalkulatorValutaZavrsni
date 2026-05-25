#ifndef VALUTA_H
#define VALUTA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* (3,4) Struktura s jasnim nazivima */
typedef struct {
    char kod[4];          // kod valute, npr. "USD"
    double tecaj;         // tečaj u odnosu na EUR
} Valuta;

/* (11) Enum izbornika */
typedef enum {
    IZBORNIK_DODAJ = 1,
    IZBORNIK_PRIKAZI,
    IZBORNIK_AZURIRAJ,
    IZBORNIK_OBRISI,
    IZBORNIK_SORTIRAJ,
    IZBORNIK_TRAZI,
    IZBORNIK_KONVERTIRAJ,
    IZBORNIK_RESET,
    IZBORNIK_IZLAZ
} IzbornikOpcija;

/* (8) extern globalna varijabla */
extern int brojacDodavanja;

/* Funkcije (10,13) */
void dodajValutu();
void prikaziValute();
void azurirajValutu();
void obrisiValutu();
void sortirajValute();
void traziValutu();
void konvertirajValutu();
void resetirajDatoteku();

int ucitajSveValute(Valuta** lista);
void spremiSveValute(Valuta* lista, int broj);
int usporedbaTecajeva(const void* a, const void* b);
int rekurzivnoTrazi(Valuta* lista, int broj, const char* kodValute);
double prosjecniTecaj(Valuta* lista, int broj);

#endif
