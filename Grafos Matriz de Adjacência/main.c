#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

void imprimir(int *A, int tam)
{
    for(int i = 0; i < tam; i++)
        printf("%i ", A[i]);
    printf("\n");
}

void imprimirEntradaSaida(int *e, int *s, int tam)
{
    for(int i = 0; i < tam; i++)
        printf("%i(%i, %i) ", i, e[i], s[i]);
    printf("\n");
}

int main()
{
    int tam = 6;
    Grafo *gr;

    gr = criaGrafo(tam);

    insereAresta(gr, 0, 1);
    insereAresta(gr, 1, 2);
    insereAresta(gr, 1, 3);
    insereAresta(gr, 2, 3);
    insereAresta(gr, 2, 4);
    insereAresta(gr, 2, 0);
    insereAresta(gr, 3, 5);
    insereAresta(gr, 4, 5);
    insereAresta(gr, 5, 0);

    mostraGrafo(gr);
    printf("\n\n\n");
    imprimiGrafo(gr);
    printf("\n\n\n");

    int *vizinhos = noVizinho(gr, 2);
    imprimir(vizinhos, tam);

    int *oc, *os;
    oc = (int*) malloc(tam * sizeof(int));
    os = (int*) malloc(tam * sizeof(int));
    if(oc == NULL || os == NULL)
        return 1;

    buscProf(gr, 0, oc, os);
    imprimirEntradaSaida(oc, os, tam);

    free(oc);
    free(os);
    free(vizinhos);
    liberaGrafo(gr);
    return 0;
}

