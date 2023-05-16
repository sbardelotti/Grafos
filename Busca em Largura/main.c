#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#define TAM 5
int main()
{
    Grafo *gr = criaGrafo(TAM);
    insereAresta(gr, 0, 1);
    insereAresta(gr, 0, 2);
    insereAresta(gr, 1, 3);
    insereAresta(gr, 2, 3);
    insereAresta(gr, 3, 4);
    int *d = distancias(gr, 0);
    for(int i = 0; i < TAM; i++)
        printf("Vert: %i Dist: %i \n", i, d[i]);

    return 0;
}
