#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

/* (9,16,17,18) Sigurno zauzimanje memorije */
static inline void* sigurnoAlociraj(size_t velicina) {
    void* p = malloc(velicina);
    if (!p) {
        perror("Greska: alokacija memorije");
        exit(EXIT_FAILURE);
    }
    return p;
}

#endif
