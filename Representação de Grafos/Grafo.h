#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
typedef struct grafo Grafo;

Grafo *cria_Grafo(int n_vertices, int grau_max, int ponderado);
void libera_Grafo(Grafo* gr);
int insereAresta(Grafo* gr, int orig, int dest, int digrafo, float peso);
int removeAresta(Grafo* gr, int orig, int dest, int digrafo);

void buscaProfundidade_Grafo(Grafo *gr, int ini, int *visitado);
void buscaLargura_Grafo(Grafo *gr, int ini, int *visitado);
void menorCaminho_Grafo(Grafo *gr, int ini, int *ant, float *dist);

#endif // GRAFO_H_INCLUDED
