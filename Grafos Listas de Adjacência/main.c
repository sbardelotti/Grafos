#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

void imprimir(int *A, int tam)
{
    for(int i = 0; i < tam; i++)
        printf("%i", A[i]);

}

void imprimirEntradaSaida(int *e, int *s, int tam)
{
    for(int i = 0; i < tam; i++)
        printf("%i(%i, %i) ", i, e[i], s[i]);
    printf("\n");
}

int arestasAleatorio(int vertices)
{
    return (rand() % (vertices*(vertices-1))) + 1;
}

void troca(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main()
{
    Grafo *gr;
    FILE *saida;

    int tam = 7;
    saida = fopen("grafo.txt", "w");
    gr = criaGrafo(tam);

    insereAresta(gr, 0, 1);
    //insereArestaND(gr, 0, 1);
    insereAresta(gr, 1, 2);
    insereAresta(gr, 1, 3);
    insereAresta(gr, 2, 3);
    insereAresta(gr, 2, 4);
    insereAresta(gr, 2, 0);
    insereAresta(gr, 3, 5);
    insereAresta(gr, 4, 5);
    insereAresta(gr, 5, 0);
    insereArestaND(gr, 5, 6);
    removeArestaND(gr, 5, 6);

    mostraGrafo(gr);
    printf("\n\n\n");
    imprimirGrafo(gr);

    imprimiArquivoGrafo(gr, saida);

    fclose(saida);

    printf("\n");
    int *vizinhos = noVizinho(gr, 2);
    imprimir(vizinhos, tam);
    printf("\n");

    int *oc, *os;
    oc = (int*) malloc(tam * sizeof(int));
    os = (int*) malloc(tam * sizeof(int));
    if(oc == NULL || os == NULL)
        return 1;

    buscProf(gr, 0, oc, os);
    imprimirEntradaSaida(oc, os, tam);

    int *componentes = (int *) malloc(tam * sizeof(int));
    identComponentes(gr, componentes);
    printf("\nComponentes: ");
    imprimir(componentes, tam);

    printf("\n\n\n");
    int *entrada_aleatorio, *saida_aleatorio, *comp_aleatorio;
    int tam_aleatorio = rand();
    comp_aleatorio = (int *) malloc(tam_aleatorio * sizeof(int));
    entrada_aleatorio = (int *) malloc(tam_aleatorio * sizeof(int));
    saida_aleatorio = (int *) malloc(tam_aleatorio * sizeof(int));
    Grafo *aleatorio = grafoAleatorioD(tam_aleatorio, arestasAleatorio(tam_aleatorio));
    buscProf(aleatorio, 0, entrada_aleatorio, saida_aleatorio);
    imprimirEntradaSaida(entrada_aleatorio, saida_aleatorio, tam_aleatorio);
    identComponentes(aleatorio, comp_aleatorio);
    printf("\nComponentes: ");
    imprimir(comp_aleatorio, tam_aleatorio);
    printf("\n\n");
    mostraGrafo(aleatorio);

    int dag_vertice = 10;
    int *perm = malloc(dag_vertice * sizeof(int));
    for(int i = 0; i < dag_vertice; i++)
        perm[i] = i + 1;

    //  Retorna um n�mero entre [0, n)
    int uniformeAleat(int n)
    {
        return (int)((double)rand() / (double)(RAND_MAX + 1) * n);
    }

    //  Knuth shuffle
    int *permAleat(int *perm, int n)
    {
        int i, j;
        for(i = 0; i < n - 1; i++)
        {
            j = i + uniformeAleat(n - i);
            troca(&perm[i], &perm[j]);
        }
        return perm;
    }
    //  o j guarda um indice que vai de 0 at� n - i + i - 1, ou seja n - 1
    /*  esse algoritmo cria um vetor de permuta��es de tamanho n - 1, existe um �ndice que percorre da esquerda para a direita
        considere que tudo aquilo antes do �ndice como prefixo e depois do �ndice como sufixo, ao andar um posi��o o �ndice
        sorteia alg�em do sufixo e ocorre uma troca entre o �ndice e o n�mero sorteado, logo o prefixo ser�o compostos de
        n�meros embaralhados enquanto o sufixo ser�o aqueles que ainda n�o est�o embaralhados. Veja que o n�mero sorteado pode ser
        o pr�prio �ndice
    */
    //  no in�cio de cada inter��o do for � feito uma permuta��o do vetor original 0...n - 1
    //  veja que o vetor n�o � poss�vel de ser corrompido pois � feito apenas trocas
    //  a escolha do n�mero sorterado possui chance uniforme dentre todas a possibilidade
    //  sendo o prefixo v[0...i - 1] a prob de escohler o n�mero � 1 / (n! / (n - i)!)
    //  ou seja se tiver apenas 4 n�meros no sufixo ent�o a chance � de 25% para cada, se tiver 2 ent�o tem chance igual de 50%
    //  veja que ao final da intera��o i ser� igual a n, portanto 1 / n! que � o n�mero total de possivel permuta��es
    //  isso signifiac que a aleatoriedade do algoritmo se prova uniforme entre todos os elementos
    //  tempo: O(n) espa�o: O(1)
    liberaGrafo(gr);
    return 0;
}
