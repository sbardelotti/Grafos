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
//  Retorna o tempo de termino sendo os indices o proprio tempo de termino
void loopBuscaProfTempoTerm(Grafo *g, int *tempoTerm);
void identCompFortConexo(Grafo *g, int *comp);
#endif // GRAFO_H_INCLUDED
