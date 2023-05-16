#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"
#include <string.h>
#include <math.h>
typedef struct no No;
struct no{
    int rotulo;
    No *prox;
    int custo;
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
    fprintf(saida, "N�mero de Vertices: %d\nGrau do Grafo: %d\n", g->n_vertices, g->grau);
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
            pilha[topo++] = vertice_origem;    // empilhar corretamente a sa�da
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

// grafos espar�os
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

A primeira otimiza��o � evitar a repeti��o de checagens desnecess�rias no segundo loop. Isso � poss�vel porque a matriz de adjac�ncia de um DAG � triangular superior (ou seja, n�o possui ciclos), portanto s� precisamos percorrer as posi��es acima da diagonal principal. Para isso, modificamos o segundo loop para iniciar a vari�vel "destino" em "origem+1", em vez de 0. Essa mudan�a reduz pela metade o n�mero de checagens de "perm[origem] < perm[destino]".

A segunda otimiza��o � utilizar uma representa��o impl�cita do DAG, baseada em uma permuta��o aleat�ria dos v�rtices. Em vez de gerar o DAG com arestas aleat�rias e em seguida permutar os v�rtices, geramos a permuta��o aleat�ria primeiro e depois utilizamos essa permuta��o para criar o DAG aleat�rio de forma eficiente. Para isso, utilizamos duas vari�veis auxiliares: "sucessor" e "posicao".

A vari�vel "sucessor[i]" armazena o n�mero de sucessores do v�rtice i (ou seja, o n�mero de arestas que saem de i). Inicialmente, ela � inicializada com zeros para todos os v�rtices. Em seguida, percorremos os �ndices (origem, destino) acima da diagonal principal da matriz de adjac�ncia e geramos uma aresta com probabilidade "prob" para cada par de v�rtices. Se uma aresta � gerada da origem ao destino, incrementamos o valor de "sucessor[origem]".

A vari�vel "posicao[v]" armazena a posi��o do v�rtice v na permuta��o aleat�ria. Inicialmente, ela � inicializada com zeros para todos os v�rtices. Em seguida, percorremos a permuta��o aleat�ria "perm" e atualizamos a posi��o de cada v�rtice na vari�vel "posicao".

Por fim, percorremos os v�rtices na ordem da permuta��o aleat�ria e criamos as arestas para os sucessores de cada v�rtice, utilizando a lista de sucessores impl�cita na ordem dos v�rtices. Para isso, percorremos a lista de sucessores do v�rtice i (ou seja, os v�rtices com posi��o maior do que i e menor do que a pr�xima posi��o de i na permuta��o) e criamos uma aresta para cada sucessor. Como as posi��es dos v�rtices na permuta��o foram pr�-calculadas na vari�vel "posicao", podemos acessar a posi��o do sucessor na permuta��o atrav�s de "posicao[sucessor]".

*/

// Veja que o algortimo otimizado tem complexidade O(arestas + vertices) enquanto o normal � O(vertices^2)

Grafo* lerGrafoImpresso(FILE *entrada)
{
    int n_vertices, n_arestas, vertice, vizinho;
    Grafo *g;
    fscanf(entrada, "%d %d\n", &n_vertices, &n_arestas);
    g = criaGrafo(n_vertices);
    for(vertice = 0; vertice < g->n_vertices; vertice++)
    {
        fscanf(entrada, "%d", &vizinho);
        while(vizinho != -1)
        {
            insereArestaNaoSegura(g, vertice, vizinho);
            fscanf(entrada, "%d", &vizinho);
        }
    }
    return g;
}

/*
5 5    (5 vertices e 5 arestas)
1 2 -1 (vertice 0)
3 -1   (vertice 1)
3 -1   (vertice 2)
4 -1   (vertice 3)
        o -1 se refere a sentinela
*/

Grafo* lerGrafoImpressoSemSentinela(FILE *entrada)
{
    int n_vertices, n_arestas, vertice, vizinho, tam;
    Grafo *g;
    char *str, *aux;
    fscanf(entrada, "%d %d\n", &n_vertices, &n_arestas);
    g = criaGrafo(n_vertices);
    tam = ((g->n_vertices * ((int)log10((double)g->n_vertices) + 1)) + 3) * sizeof(char);
    str = malloc(tam);
    for(vertice = 0; vertice < g->n_vertices; vertice++)
    {
        fgets(str, tam, entrada); //le a entrada at� encontrar \n, fim de arquivo ou ler at� tam-1
        aux = strtok(str, ":"); //pega o token delimitado por :
        aux = strtok(NULL, " \n"); //pega o token delimitado por espa�o OU \n
        while(aux != NULL)
        {
            vizinho = atoi(aux);
            insereArestaNaoSegura(g, vertice, vizinho);
            aux = strtok(NULL, " \n");
        }
    }
    free(str);
    return g;
}

/*
n_vertices n_arestas (ter� n_vertices linhas para ler)
vertice1: vizinho11 vizinho12 vizinho13
vertice2: vizinho21 vizinho22
vertice3: vizinho31 vizinho32 vizinho33 vizinho34 vizinho35
...
verticen: vizinho11 ... vizinhon
*/

/*
A fun��o fgets() � uma fun��o em C que � usada para ler uma linha de um arquivo de entrada, incluindo o caractere de nova linha '\n' e armazenar em uma string.

A fun��o fgets() recebe tr�s argumentos:

char *str: � o ponteiro para uma string que armazenar� a linha lida do arquivo.
int n: � o n�mero m�ximo de caracteres que ser�o lidos da linha, incluindo o caractere '\n' final. Esse valor deve ser menor ou igual ao tamanho do array que cont�m a string str.
FILE *stream: � o ponteiro para o arquivo de entrada a partir do qual a fun��o deve ler.
*/

/*
tam � o tamanho (em bytes) da string que vamos usar para ler as linhas do arquivo de entrada.
Uma linha que apresenta os vizinhos do v�rtice 3, por exemplo, pode ter o formato "3: 1 5 4", indicando que existem os arcos (3, 1), (3, 5) e (3, 4), e lembrando que existe um '\n' invis�vel marcando o final da linha.
Como num grafo simples o m�ximo de vizinhos que um v�rtice pode ter � n - 1 (quando ele tem arcos para todos os outros v�rtices), essa linha pode ter at� n r�tulos de v�rtices (n - 1 dos vizinhos + 1 r�tulo do v�rtice origem antes do ':'), o que justifica o G->n multiplicado na express�o.
Al�m disso, cada r�tulo ocupa no m�ximo log10 (n + 1) d�gitos (para perceber isso, note que se n for 9, precisamos de apenas um d�gito, se n for 99 precisamos de dois d�gitos, e assim por diante).
Al�m dos d�gitos de cada r�tulo, precisamos de um espa�o separando os mesmos, o que justifica o +1 da express�o (log10 (n + 1) +1) que depois � multiplicada por G->n. Por fim, o +3 est� l� para deixar o espa�o do ':', do '\n' que est� no final da linha da entrada, e do '\0' que � necess�rio para marcarmos o final da string
*/

void buscaProfOrdTopoRDist(Grafo *g, int vertice, int *visitado, int *ordTopo, int *P_rotAtual)
{
    int vizinho;
    No *no;
    visitado[vertice] = 1;
    no = g->arestas[vertice];
    while(no != NULL)
    {
        vizinho = no->rotulo;
        if(visitado[vizinho] == 0)
            buscaProfOrdTopoRDist(g, vizinho, visitado, ordTopo, P_rotAtual);
        no = no->prox;
    }
    // Abaixo est� as altera��es
    ordTopo[*P_rotAtual] = vertice;
    (*P_rotAtual)--;
    // Agora o vetor est� indexado por posi��es com seu conte�do sendo o rotulo dos vertices
}

void ordenacaoTopoDist(Grafo *g, int *ordTopo)
{
    int vertice, rot_atual, *visitado;
    visitado = malloc(g->n_vertices * sizeof(int));
    for(vertice = 0; vertice < g->n_vertices; vertice++)
        visitado[vertice] = 0;
    rot_atual = g->n_vertices;
    for(vertice = 0; vertice < g->n_vertices; vertice++)
        if(visitado[vertice] == 0)
            buscaProfOrdTopoRDist(g, vertice, visitado, ordTopo, &rot_atual);
    free(visitado);
}

void distanciasDAG(Grafo *g, int origem, int *dist, int *pred)
{
    int i, *ordTopo;
    int vertice, vizinho, custo;
    No *no;
    for(i = 0; i < g->n_vertices; i++)
    {
        dist[i] = __INT_MAX__;
        pred[i] = -1;
    }
    dist[origem] = 0;
    ordTopo = malloc((g->n_vertices + 1) * sizeof(int));  //  Est� alocando com +1 para manter a conven��o de ir de 1 at� N, ou seja, a posi��o 0 n�o � utilizada
    ordenacaoTopoDist(g, ordTopo);
    for(i = 1; i <= g->n_vertices; i++)
    {
        vertice = ordTopo[i];
        no = g->arestas[vertice];
        while(no != NULL)
        {
            vizinho = no->rotulo;
            custo = no->custo;
            if(dist[vizinho] > dist[vertice] + custo)
            {
                dist[vizinho] = dist[vertice] + custo;
                pred[vizinho] = vertice;
            }
            no = no->prox;
        }
    }
    free(ordTopo);
}

// Tem que adaptar a inser��o e cria��o de novos vertices para dar suporte ao CUSTO

void Dijkstra(Grafo *g, int origem, int *dist, int *pred)
{
    int i, *R;
    int vertice, vizinho, custo, tam_R, min_dist;
    No *no;

    for(i = 0; i < g->n_vertices; i++)
    {
        dist[i] = __INT_MAX__;
        pred[i] = -1;
    }
    dist[origem] = 0;
    R = malloc(g->n_vertices * sizeof(int));  //  conjunto resolvidos
    for(i = 0; i < g->n_vertices; i++)
        R[i] = 0;
    tam_R = 0;

    while(tam_R < g->n_vertices)
    {
        min_dist = __INT_MAX__;
        vertice = -1;
        for(i = 0; i <= g->n_vertices; i++) // esse for em especifico torna o algorimo muito ineficiente
            if(R[i] == 0 && dist[i] < min_dist)
            {
                vertice = i;
                min_dist = dist[i];
            }

        R[vertice] = 1;
        tam_R++;

        for(no = g->arestas[vertice]; no != NULL; no = no->prox)
        {
            vizinho = no->rotulo;
            custo = no->custo;
            if(R[vizinho] == 0 && dist[vizinho] > dist[vertice] + custo)
            {
                dist[vizinho] = dist[vizinho] + custo;
                pred[vizinho] = vertice;
            }
        }
    }
    free(R);
}


