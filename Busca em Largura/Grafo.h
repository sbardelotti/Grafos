#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
typedef struct grafo Grafo;
typedef struct no No;

Grafo* criaGrafo(int n_vertices);
int liberaGrafo(Grafo *g);
void insereAresta(Grafo *g, int inicio, int fim);
void insereArestaND(Grafo *g, int inicio, int fim);
void removeAresta(Grafo *g, int inicio, int fim);
void removeArestaND(Grafo *g, int inicio, int fim);

int *distancias(Grafo *g, int origem);
#endif // GRAFO_H_INCLUDED
