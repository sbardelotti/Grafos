#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

void imprimir(int tam, int *imp)
{
    int i;
    for(i = 0; i < tam; i++)
        printf("%i ", imp[i]);
    printf("\n");
}

int main()
{

    int tam = 10;
    Grafo *gr;
    gr = cria_Grafo(tam, 7, 0);

    insereAresta(gr, 0, 1, 0, 0);
    insereAresta(gr, 1, 3, 0, 0);
    //removeAresta(gr, 0, 1, 0);
    insereAresta(gr, 1, 2, 0, 0);
    insereAresta(gr, 2, 3, 0, 0);
    insereAresta(gr, 3, 4, 0, 0);
    insereAresta(gr, 4, 5, 0, 0);
    insereAresta(gr, 4, 6, 0, 0);
    insereAresta(gr, 5, 6, 0, 0);

    int vis[tam];
    int ant[tam];
    float dist[tam];

    //buscaProfundidade_Grafo(gr, 0, vis);
    buscaLargura_Grafo(gr, 0, vis);
    menorCaminho_Grafo(gr, 0, ant, dist);

    //printf("Busca por Profundidade    ");
    printf("Busca por Largura:        ");
    imprimir(tam, vis);
    printf("Caminho menor distancia: ");
    imprimir(tam, ant);
    printf("Distancia:                ");
    for(int i = 0; i < tam; i++)
        printf("%.0f ", dist[i]);


    libera_Grafo(gr);
    return 0;
}
