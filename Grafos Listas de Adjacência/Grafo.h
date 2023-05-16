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
void mostraGrafo(Grafo *g);
void imprimirGrafo(Grafo *g);
void imprimiArquivoGrafo(Grafo *g, FILE *saida);
void buscProf(Grafo *g, int vertice_inicial, int *ordem_chegada, int *ordem_saida);
void identComponentes(Grafo *g, int *componentes);
int *noVizinho(Grafo *g, int proc);
void ordenacaoTopologica(Grafo *g, int *ordTopo);
Grafo* grafoAleatorio(int vertices, int arestas);
Grafo* grafoAleatorioD(int vertices, int arestas);
Grafo* dagAleatorio(int vertices, int arestas, int *perm);
Grafo* dagAleatorioP(int vertices, int arestas, int *perm);
Grafo* dagAleatorioOtimizadaKnuthS(int vertices, int arestas, int *perm);

Grafo* lerGrafoImpresso(FILE *entrada);
Grafo* lerGrafoImpressoSemSentinela(FILE *entrada);

void distanciasDAG(Grafo *g, int origem, int *dist, int *pred);
void Dijkstra(Grafo *g, int origem, int *dist, int *pred);
#endif // GRAFO_H_INCLUDED
