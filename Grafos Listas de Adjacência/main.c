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

    //  Retorna um número entre [0, n)
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
    //  o j guarda um indice que vai de 0 até n - i + i - 1, ou seja n - 1
    /*  esse algoritmo cria um vetor de permutações de tamanho n - 1, existe um índice que percorre da esquerda para a direita
        considere que tudo aquilo antes do índice como prefixo e depois do índice como sufixo, ao andar um posição o índice
        sorteia algúem do sufixo e ocorre uma troca entre o índice e o número sorteado, logo o prefixo serão compostos de
        números embaralhados enquanto o sufixo serão aqueles que ainda não estão embaralhados. Veja que o número sorteado pode ser
        o próprio índice
    */
    //  no início de cada interção do for é feito uma permutação do vetor original 0...n - 1
    //  veja que o vetor não é possível de ser corrompido pois é feito apenas trocas
    //  a escolha do número sorterado possui chance uniforme dentre todas a possibilidade
    //  sendo o prefixo v[0...i - 1] a prob de escohler o número é 1 / (n! / (n - i)!)
    //  ou seja se tiver apenas 4 números no sufixo então a chance é de 25% para cada, se tiver 2 então tem chance igual de 50%
    //  veja que ao final da interação i será igual a n, portanto 1 / n! que é o número total de possivel permutações
    //  isso signifiac que a aleatoriedade do algoritmo se prova uniforme entre todos os elementos
    //  tempo: O(n) espaço: O(1)
    liberaGrafo(gr);
    return 0;
}
