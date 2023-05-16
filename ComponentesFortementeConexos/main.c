#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main()
{
    /*
        O maior tempo de término represeta um vértice componente fonte
        Precisamos encontrar o vértice componente sorvedouro
        Para isso vamos inverter o grafo, assim a fonte do grafo invertido será o sorvedoro do grafo original
    */
    /*
        1 - Computa G reverso
        2 - Computa o tempo de termino no grafo reverso
        3 - Executar Busca em profundidade em G só que começando pelos vértices com maior tempo de término que não foram visitados
        e então eu marco os vértices visitados com um rótulo distinto
    */
    return 0;
}
