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

void mostraGrafo(Grafo *g) {
    int i;
    No *no;
    for (i = 0; i < g->n_vertices; i++) {
        printf("%d: ", i);
        for (no = g->arestas[i]; no != NULL; no = no->prox) {
            printf("%d ", no->rotulo);
        }
        printf("\n");
    }
}

int temAresta(Grafo *g, int inicio, int fim)
{
    if(g == NULL)
        return 0;
    No *no;
    for(no = g->arestas[inicio]; no != NULL; no = no->prox)
        if(no->rotulo == fim)
            return 1;
    return 0;
}

void imprimirGrafo(Grafo *g)
{
    int i, j;
    printf("__|");
    for (i = 0; i < g->n_vertices; i++)
        printf("%d ", i);
    printf("\n");
    for (i = 0; i < g->n_vertices; i++)
    {
        printf("%d: ", i);
        for (j = 0; j < g->n_vertices; j++)
            temAresta(g, i, j) ? printf("1 ") : printf("0 ");

        printf("\n");
    }
}

void imprimiArquivoGrafo(Grafo *g, FILE *saida)
{
    int i;
    No *no;
    fprintf(saida, "Número de Vertices: %d\nGrau do Grafo: %d\n", g->n_vertices, g->grau);
    for(i = 0; i < g->n_vertices; i++)
    {
        for(no = g->arestas[i]; no != NULL; no = no->prox)
            fprintf(saida, "%2d ", no->rotulo);
        fprintf(saida, "-1");
        fprintf(saida, "\n");
    }
}

int *noVizinho(Grafo *g, int proc)
{
    if (g == NULL || proc < 0 || proc >= g->n_vertices)
        return NULL;
    No *no;
    int aux = 0;
    int *vizinhos = (int *) malloc(g->grau * sizeof(int));
    memset(vizinhos, 0, g->grau * sizeof(int));
    for(no = g->arestas[proc]; no != NULL; no = no->prox)
    {
        vizinhos[aux++] = no->rotulo;
    }

    int *resultado = (int *) realloc(vizinhos, aux * sizeof(int));
    if (resultado == NULL) {
        free(vizinhos);
        return NULL;
    } else {
        return resultado;
    }

    //return vizinhos;
}

void buscProfR(Grafo *g, int vertice_origem, int *ordem_chegada, int *ordem_saida, int *ptempo)
{
    int vertice_adjacente;
    No *no;
    ordem_chegada[vertice_origem] = (*ptempo)++;
    no = g->arestas[vertice_origem];
    while(no != NULL)
    {
        vertice_adjacente = no->rotulo;
        if(ordem_chegada[vertice_adjacente] == -1)
            buscProfR(g, vertice_adjacente, ordem_chegada, ordem_saida, ptempo);
        no = no->prox;
    }
    ordem_saida[vertice_origem] = (*ptempo)++;
}

void buscProfI(Grafo *g, int vertice_inicial, int *ordem_chegada, int *ordem_saida, int tempo)
{
    int vertice_origem, vertice_adjacente;
    int *pilha;
    No *no;
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
            no = g->arestas[vertice_origem];
            while(no != NULL)
            {
                vertice_adjacente = no->rotulo;
                if(ordem_chegada[vertice_adjacente] == -1)
                    pilha[topo++] = vertice_adjacente;
                no = no->prox;
            }
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
    buscProfR(g, vertice_inicial, ordem_chegada, ordem_saida, &tempo);
    //buscProfI(g, vertice_inicial, ordem_chegada, ordem_saida, tempo);
}

void buscaCompR(Grafo *g, int v, int *componentes, int id_comp)
{
    int w;
    No *no;
    componentes[v] = id_comp;
    no = g->arestas[v];
    while(no != NULL)
    {
        w = no->rotulo;
        if(componentes[w] == -1)
            buscaCompR(g, w, componentes, id_comp);
        no = no->prox;
    }
}

void identComponentes(Grafo *g, int *componentes)
{
    int v, id_componente;
    memset(componentes, -1, g->n_vertices * sizeof(int));
    id_componente = 0;
    for(v = 0; v < g->n_vertices; v++)
        if(componentes[v] == -1)
        {
            id_componente++;
            buscaCompR(g, v, componentes, id_componente);
        }
}

void buscaProfOrdTopoR(Grafo *g, int vertice_atual, int *visitado, int *ordTopo, int *prot_atual)
{
    int vertice_adjacente;
    No *no;
    visitado[vertice_atual] = 1;
    for(no = g->arestas[vertice_atual]; no != NULL; no = no->prox)
    {
        vertice_adjacente = no->rotulo;
        if(visitado[vertice_adjacente] == 0)
            buscaProfOrdTopoR(g, vertice_adjacente, visitado, ordTopo, prot_atual);
    }
    ordTopo[vertice_atual] = (*prot_atual)--;
}

void buscaProfOrdTopoI(Grafo *g, int origem, int *visitado, int *ordTopo, int *prot_atual)
{
    int vertice_atual, vertice_adjacente;
    No *no;
    int topo = 0;
    int *pilha = malloc(g->grau * sizeof(int));
    pilha[topo++] = origem;

    while(topo > 0)
    {
        vertice_atual = pilha[--topo];
        if(visitado[vertice_atual] == 0)
        {
            visitado[vertice_atual] = 1;
            pilha[topo++] = vertice_atual;
            for(no = g->arestas[vertice_atual]; no != NULL; no = no->prox)
            {
                vertice_adjacente = no->rotulo;
                if(visitado[vertice_adjacente] == 0)
                    pilha[topo++] = vertice_adjacente;
            }
        }
        else if(ordTopo[vertice_atual] == -1)
            ordTopo[vertice_atual] = (*prot_atual)--;
    }
}

void ordenacaoTopologica(Grafo *g, int *ordTopo)
{
    int vertice_atual, rot_atual, *visitado;
    visitado = malloc(g->n_vertices * sizeof(int));
    memset(visitado, 0, g->n_vertices * sizeof(int));
    memset(ordTopo, -1, g->n_vertices * sizeof(int));
    rot_atual = g->n_vertices;
    for(vertice_atual = 0; vertice_atual < g->n_vertices; vertice_atual++)
        if(visitado[vertice_atual] == 0)
            buscaProfOrdTopoR(g, vertice_atual, visitado, ordTopo, &rot_atual);
    free(visitado);
}

int verticeAleatorio(Grafo *g)
{
    if(g == NULL)
        return -1;
    double r;
    r = (double) rand() / ((double) RAND_MAX + 1.0);
    return (int)(r * g->n_vertices);
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

// grafos esparços
Grafo* grafoAleatorio(int vertices, int arestas)
{
    Grafo* g = criaGrafo(vertices);
    while(g->grau < arestas)
    {
        int origem = verticeAleatorio(g);
        int destino = verticeAleatorio(g);
        if(origem != destino)
            insereAresta(g, origem, destino);
    }

    return g;
}

Grafo* grafoAleatorioD(int vertices, int arestas)
{
    int origem, destino;
    double prob = (double) arestas / vertices / (vertices - 1);
    Grafo* g = criaGrafo(vertices);
    for(origem = 0; origem < vertices; origem++)
        for(destino = 0; destino < vertices; destino++)
            if(origem != destino)
                if(rand() < prob * (RAND_MAX + 1.0))
                    insereArestaNaoSegura(g, origem, destino);

    return g;
}

Grafo* dagAleatorio(int vertices, int arestas, int *perm)
{
    Grafo *g = criaGrafo(vertices);
    while(g->grau < arestas)
    {
        int origem = verticeAleatorio(g);
        int destino = verticeAleatorio(g);
        if(perm[origem] < perm[destino])
            insereAresta(g, origem, destino);
    }
    return g;
}

Grafo* dagAleatorioP(int vertices, int arestas, int *perm)
{
    double prob = (double) arestas / vertices / (vertices - 1) * 2;
    Grafo *g = criaGrafo(vertices);
    for(int origem = 0; origem < vertices; origem++)
        for(int destino = 0; destino < vertices; destino++)
            if(perm[origem] < perm[destino])
                if(rand() < prob * (RAND_MAX + 1.0))
                    insereArestaNaoSegura(g, origem, destino);
    return g;
}

Grafo* dagAleatorioOtimizadaKnuthS(int vertices, int arestas, int *perm)
{
    double prob = (double) arestas / vertices / (vertices - 1) * 2;
    Grafo *g = criaGrafo(vertices);
    int *sucessor = calloc(vertices, sizeof(int));
    for(int origem = 0; origem < vertices; origem++)
        for(int destino = origem+1; destino < vertices; destino++)
            if(rand() < prob * (RAND_MAX + 1.0))
                sucessor[destino]++;
    int *posicao = calloc(vertices+1, sizeof(int));
    for(int i = 0; i < vertices; i++)
        posicao[perm[i]] = i;
    for(int i = 0; i < vertices; i++)
        for(int j = 0; j < sucessor[i]; j++)
            insereArestaNaoSegura(g, perm[i], perm[posicao[i+1]+j]);
    free(sucessor);
    free(posicao);
    return g;
}

/*

A primeira otimização é evitar a repetição de checagens desnecessárias no segundo loop. Isso é possível porque a matriz de adjacência de um DAG é triangular superior (ou seja, não possui ciclos), portanto só precisamos percorrer as posições acima da diagonal principal. Para isso, modificamos o segundo loop para iniciar a variável "destino" em "origem+1", em vez de 0. Essa mudança reduz pela metade o número de checagens de "perm[origem] < perm[destino]".

A segunda otimização é utilizar uma representação implícita do DAG, baseada em uma permutação aleatória dos vértices. Em vez de gerar o DAG com arestas aleatórias e em seguida permutar os vértices, geramos a permutação aleatória primeiro e depois utilizamos essa permutação para criar o DAG aleatório de forma eficiente. Para isso, utilizamos duas variáveis auxiliares: "sucessor" e "posicao".

A variável "sucessor[i]" armazena o número de sucessores do vértice i (ou seja, o número de arestas que saem de i). Inicialmente, ela é inicializada com zeros para todos os vértices. Em seguida, percorremos os índices (origem, destino) acima da diagonal principal da matriz de adjacência e geramos uma aresta com probabilidade "prob" para cada par de vértices. Se uma aresta é gerada da origem ao destino, incrementamos o valor de "sucessor[origem]".

A variável "posicao[v]" armazena a posição do vértice v na permutação aleatória. Inicialmente, ela é inicializada com zeros para todos os vértices. Em seguida, percorremos a permutação aleatória "perm" e atualizamos a posição de cada vértice na variável "posicao".

Por fim, percorremos os vértices na ordem da permutação aleatória e criamos as arestas para os sucessores de cada vértice, utilizando a lista de sucessores implícita na ordem dos vértices. Para isso, percorremos a lista de sucessores do vértice i (ou seja, os vértices com posição maior do que i e menor do que a próxima posição de i na permutação) e criamos uma aresta para cada sucessor. Como as posições dos vértices na permutação foram pré-calculadas na variável "posicao", podemos acessar a posição do sucessor na permutação através de "posicao[sucessor]".

*/

// Veja que o algortimo otimizado tem complexidade O(arestas + vertices) enquanto o normal é O(vertices^2)

