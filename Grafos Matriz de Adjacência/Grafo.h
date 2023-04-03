#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
typedef struct grafo Grafo;

Grafo *criaGrafo(int n_vertices);
int liberaGrafo(Grafo *g);
void insereAresta(Grafo *g, int inicio, int fim);
void insereArestaND(Grafo *g, int inicio, int fim);
void removeAresta(Grafo *g, int inicio, int fim);
void removeArestaND(Grafo *g, int inicio, int fim);
void mostraGrafo(Grafo *g);
void imprimiGrafo(Grafo *g);
void buscProf(Grafo *g, int vertice_inicial, int *ordem_chegada, int *ordem_saida);

int *noVizinho(Grafo *g, int no);

#endif // GRAFO_H_INCLUDED
