#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
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

void buscaProfTempoTermR(Grafo *g, int origem, int *visitado, int *tempoTerm, int *ptempo)
{
    int vertice_vizinho;
    No *no;
    visitado[origem] = 1;
    no = g->arestas[origem];
    while(no != NULL)
    {
        vertice_vizinho = no->rotulo;
        if(visitado[vertice_vizinho] == 0)
            buscaProfTempoTermR(g, vertice_vizinho, visitado, tempoTerm, ptempo);
        no = no->prox;
    }
    tempoTerm[*ptempo] = origem;
    (*ptempo)++;
}

void loopBuscaProfTempoTerm(Grafo *g, int *tempoTerm)
{
    int vertice, tempo, *visitado;
    visitado = malloc(g->n_vertices * sizeof(int));
    for(vertice = 0; vertice < g->n_vertices; vertice++)
    {
        visitado[vertice] = 0;
        tempoTerm[vertice] = -1;
    }
    tempo = 0;
    for(vertice = 0; vertice < g->n_vertices; vertice++)
        if(visitado[vertice] == 0)
            buscaProfTempoTermR(g, vertice, visitado, tempoTerm, &tempo);
    free(visitado);
}

void buscaProfIdentCompR(Grafo *g, int origem, int *componentes, int num_comp)
{
    int vizinho;
    No *no;
    componentes[origem] = num_comp;
    no = g->arestas[origem];
    while(no != NULL)
    {
        vizinho = no->rotulo;
        if(componentes[vizinho] == -1)
            buscaProfIdentCompR(g, vizinho, componentes, num_comp);
        no = no->prox;
    }
}

void loopBuscaProfIdentComp(Grafo *g, int *tempoTermino, int *componentes)
{
    int vertice, i, num_comp;
    for(vertice = 0; vertice < g->n_vertices; vertice++)
        componentes[vertice] = -1;
    num_comp = 0;
    for(i = g->n_vertices - 1; i >= 0; i--)
    {
        vertice = tempoTermino[i];
        if(componentes[vertice] == -1)
        {
            num_comp++;
            buscaProfIdentCompR(g, vertice, componentes, num_comp);
        }
    }
}

void identCompFortConexo(Grafo *g, int *comp)
{
    int vertice, vizinho, *tempoTermino;
    No *no;
    Grafo *gRev = criaGrafo(g->n_vertices);
    for(vertice = 0; vertice < g->n_vertices; vertice++)
    {
        no = g->arestas[vertice];
        while(no != NULL)
        {
            vizinho = no->rotulo;
            insereArestaNaoSegura(gRev, vizinho, vertice);
            no = no->prox;
        }
    }
    tempoTermino = malloc(g->n_vertices * sizeof(int));
    loopBuscaProfTempoTerm(gRev, tempoTermino);
    liberaGrafo(gRev);
    gRev = NULL;
    loopBuscaProfIdentComp(g, tempoTermino, comp);
    free(tempoTermino);
}









