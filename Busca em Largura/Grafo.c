#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include "Fila.h"
#include <string.h>
typedef struct no No;
struct no{
    int rotulo;
    No *prox;
};

struct grafo{
    No **arestas;
    int n_vertices;
    int grau;
};

Grafo* criaGrafo(int n_vertices)
{
    Grafo *g = (Grafo *) malloc(sizeof(Grafo));
    if(g != NULL)
    {
        int i;
        g->n_vertices = n_vertices;
        g->grau = 0;
        g->arestas = (No **) malloc(n_vertices * sizeof(No*));
        for(i = 0; i < n_vertices; i++)
            g->arestas[i] = NULL;
        //memset(g->A, 0, n_vertices * sizeof(struct No*));
    }
    return g;
}

int liberaGrafo(Grafo *g)
{
    if(g == NULL)
        return 0;
    int i;
    No *no;
    for(i = 0; i < g->n_vertices; i++)
    {
        no = g->arestas[i];
        while(no != NULL)
        {
            g->arestas[i] = no;
            no = no->prox;
            free(g->arestas[i]);
        }
        g->arestas[i] = NULL;
    }
    free(g->arestas);
    g->arestas = NULL;
    free(g);
    g = NULL;
    return 1;
}

void insereAresta(Grafo *g, int inicio, int fim)
{
    if(g == NULL)
        return;
    No *no;
    for(no = g->arestas[inicio]; no != NULL; no = no->prox)
        if(no->rotulo == fim)
            return;
    no = malloc(sizeof(struct no));
    no->rotulo = fim;
    no->prox = g->arestas[inicio];
    g->arestas[inicio] = no;
    g->grau++;
}

void insereArestaND(Grafo *g, int inicio, int fim)
{
    insereAresta(g, inicio, fim);
    insereAresta(g, fim, inicio);
}

void removeAresta(Grafo *g, int inicio, int fim)
{
    if (g == NULL)
        return;
    No *no, *ant;
    for (no = g->arestas[inicio], ant = NULL; no != NULL; ant = no, no = no->prox)
    {
        if (no->rotulo == fim)
        {
            if (ant == NULL)
                g->arestas[inicio] = no->prox;
            else
                ant->prox = no->prox;
            //(ant == NULL) ? (g->arestas[inicio] = no->prox) : (ant->prox = no->prox);
        free(no);
        g->grau--;
        break;
        }
    }
}

void removeArestaND(Grafo *g, int inicio, int fim)
{
    removeAresta(g, inicio, fim);
    removeAresta(g, fim, inicio);
}

void insereArestaNaoSegura(Grafo *g, int inicio, int fim)
{
    No *no;
    no = malloc(sizeof(No));
    no->rotulo = fim;
    no->prox = g->arestas[inicio];
    g->arestas[inicio] = no;
    g->grau++;
}

int *distancias(Grafo *g, int origem)
{
    int vertice, vizinho, *dist;
    Fila* fila;
    No *no;
    dist = malloc(g->n_vertices * sizeof(int));
    fila = CriaFila();
    for(int i = 0; i < g->n_vertices; i++)
        dist[i] = -1;
    dist[origem] = 0;
    InsereFila(fila, origem);
    while(!FilaVazia(fila))
    {
        vertice = desenfileirar(fila);
        no = g->arestas[vertice];
        while(no != NULL)
        {
            vizinho = no->rotulo;
            if(dist[vizinho] == -1)
            {
                dist[vizinho] = dist[vertice] + 1;
                InsereFila(fila, vizinho);
            }
            no = no->prox;
        }
    }

    LiberaFila(fila);
    return dist;
}












