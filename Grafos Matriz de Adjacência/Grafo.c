#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Grafo.h"


struct grafo
{
    int **arestas;
    int n_vertices;
    int grau;
};

Grafo* criaGrafo(int n_vertices)
{
    int i;
    //int j;
    Grafo *g = (Grafo *) malloc(sizeof(Grafo));
    if(g != NULL)
    {
        g->n_vertices = n_vertices;
        g->grau = 0;
        g->arestas = (int **) malloc(n_vertices * sizeof(int *));
        for(i = 0; i < n_vertices; i++)
        {
            g->arestas[i] = (int *) malloc(n_vertices * sizeof(int));
            memset(g->arestas[i], 0, n_vertices * sizeof(int));
            //for(j = 0; j < n_vertices; j++)
            //    g->A[i][j] = 0;
        }
    }
    return g;
}

void insereAresta(Grafo *g, int inicio, int fim)
{
    if(g != NULL && g->arestas[inicio][fim] == 0)
    {
        g->arestas[inicio][fim] = 1;
        g->grau++;
    }
}

void insereArestaND(Grafo *g, int inicio, int fim)
{
    if(g != NULL && g->arestas[inicio][fim] == 0)
    {
        g->arestas[inicio][fim] = g->arestas[fim][inicio] = 1;
        g->grau += 2;
    }
}

void removeAresta(Grafo *g, int inicio, int fim)
{
    if(g != NULL && g->arestas[inicio][fim] == 1)
    {
        g->arestas[inicio][fim] = 0;
        g->grau--;
    }
}

void removeArestaND(Grafo *g, int inicio, int fim)
{
    if(g != NULL && g->arestas[inicio][fim] == 1)
    {
        g->arestas[inicio][fim] = g->arestas[fim][inicio] = 0;
        g->grau -= 2;
    }
}


void mostraGrafo(Grafo *g)
{
    int i, j;
    for(i = 0; i < g->n_vertices; i++)
    {
        printf("%2d:", i);
        for(j = 0; j < g->n_vertices; j++)
            if(g->arestas[i][j] == 1)
                printf(" %2d", j);
        printf("\n");
    }
}

void imprimiGrafo(Grafo *g)
{
    int i, j;
    for(i = 0; i < g->n_vertices; i++)
    {
        for(j = 0; j < g->n_vertices; j++)
            if(g->arestas[i][j] == 1)
                printf("%2d", j);
        printf("\n");
    }
}

int liberaGrafo(Grafo *g)
{
    if(g != NULL)
    {
        int i;
        for(i = 0; i < g->n_vertices; i++)
        {
            free(g->arestas[i]);
            g->arestas[i] = NULL;
        }
        free(g->arestas);
        g->arestas = NULL;
        free(g);
        return 1;
    }
    return 0;
}

int *noVizinho(Grafo *g, int no)
{
    if (g == NULL || no < 0 || no >= g->n_vertices)
        return NULL;
    int aux = 0;
    int *vizinhos = (int *) malloc(g->grau * sizeof(int));
    memset(vizinhos, 0, g->grau * sizeof(int));
    for(int i = 0; i < g->grau; i++)
    {
        if (i != no && g->arestas[no][i] == 1)
            vizinhos[aux++] = i;
    }

    return vizinhos;
}

void buscProfR(Grafo *g, int vertice_origem, int *ordem_chegada, int *ordem_saida, int *ptempo)
{
    int vertice_adjacente;
    ordem_chegada[vertice_origem] = (*ptempo)++;
    for(vertice_adjacente = 0; vertice_adjacente < g->n_vertices; vertice_adjacente++)
        if(g->arestas[vertice_origem][vertice_adjacente] == 1 && ordem_chegada[vertice_adjacente] == -1)
            buscProfR(g, vertice_adjacente, ordem_chegada, ordem_saida, ptempo);
    ordem_saida[vertice_origem] = (*ptempo)++;
}

void buscProfI(Grafo *g, int vertice_inicial, int *ordem_chegada, int *ordem_saida, int tempo)
{
    int vertice_origem, vertice_adjacente;
    int *pilha;
    int topo = 0;
    pilha = malloc(g->grau * sizeof(int));
    pilha[topo++] = vertice_inicial;
    while(topo > 0)
    {
        vertice_origem = pilha[--topo];
        if(ordem_chegada[vertice_origem] == -1)
        {
            ordem_chegada[vertice_origem] = tempo++;
            pilha[topo++] = vertice_origem;    // empilhar corretamente a saída
            for(vertice_adjacente = 0; vertice_adjacente < g->n_vertices; vertice_adjacente++)
                if(g->arestas[vertice_origem][vertice_adjacente] == 1 && ordem_chegada[vertice_adjacente] == -1)
                    pilha[topo++] = vertice_adjacente;
        }
        else if(ordem_saida[vertice_origem] == -1)
            ordem_saida[vertice_origem] = tempo++;
    }
    free(pilha);
}

void buscProf(Grafo *g, int vertice_inicial, int *ordem_chegada, int *ordem_saida)
{
    if (vertice_inicial >= g->n_vertices || vertice_inicial < 0)
        return;

    int tempo;
    memset(ordem_chegada, -1, g->n_vertices * sizeof(int));
    memset(ordem_saida, -1, g->n_vertices * sizeof(int));
    tempo = 1;
    //buscProfR(g, vertice_inicial, ordem_chegada, ordem_saida, &tempo);
    buscProfI(g, vertice_inicial, ordem_chegada, ordem_saida, tempo);
}

Grafo* lerGrafoMatriz(FILE *entrada)
{
    int n_vertices, vertice, vizinho, valor;
    Grafo *g;
    fscanf(entrada, "%d\n", &n_vertices);
    g = criaGrafo(n_vertices);
    for(vertice = 0; vertice < g->n_vertices; vertice++)
        for(vizinho = 0; vizinho < g->n_vertices; vizinho++)
        {
            fscanf(entrada, "%d", &valor);
            if(valor == 1)
                insereAresta(g, vertice, vizinho);
        }
    return g;
}










