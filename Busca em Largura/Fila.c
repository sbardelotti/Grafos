#include <stdio.h>
#include <stdlib.h>
#include "Fila.h"

struct fila{
    struct no *inicio;
    struct no *fim;
};

struct no{
    int n;
    struct no *prox;
};

typedef struct no No;

Fila* CriaFila(){
    Fila* f = (Fila *) malloc(sizeof(Fila));
    if(f != NULL){
        f->inicio = NULL;
        f->fim = NULL;
    }
    return f;
}

void LiberaFila(Fila* f){
    if(f != NULL){
        No* no;
        while(f->inicio != NULL){
            no = f->inicio;
            f->inicio = f->inicio->prox;
            free(no);
        }
        free(f);
    }
}

int TamanhoFila(Fila* f){
    if(f == NULL) return 0;
    int count = 0;
    No* no = f->inicio;
    while(no != NULL){
        count ++;
        no = no->prox;
    }
    return count;
}

int FilaVazia(Fila* f){
    if(f == NULL) return 1;
    if(f->inicio == NULL) return 1;
    return 0;
}

int InsereFila(Fila* f, int n){
    if(f == NULL) return 0;
    No *no = (No *) malloc(sizeof(No));
    if(no == NULL) return 0;
    no->n = n;
    no->prox = NULL;
    if(f->fim == NULL){
        f->inicio = no;
    }else{
        f->fim->prox = no;
    }
    f->fim = no;
    return 1;
}

int RemoveFila(Fila* f){
    if(f == NULL) return 0;
    if(f->inicio == NULL) return 0;
    No *no = f->inicio;
    f->inicio = f->inicio->prox;
    if(f->inicio == NULL) f->fim = NULL;
    free(no);
    return 1;
}

int ConsultaFila(Fila* f, int* n){
    if(f == NULL) return 0;
    if(f->inicio == NULL) return 0;
    *n = f->inicio->n;
    return 1;
}

void ImprimirFila(Fila* f){
    if(f == NULL) return;
    if(f->inicio == NULL) return;
    No* no = f->inicio;
    while(no->prox != NULL){
        printf("%d, ", no->n);
        no = no->prox;
    }
    printf("%d", no->n);
}

int InverterFila(Fila* f){
    if(f == NULL) return 0;
    if(f->inicio == NULL) return 0;
    No *ant = NULL, *atual = f->inicio, *proximo = NULL;
    while(atual != NULL){
        proximo = atual->prox;
        atual->prox = ant;
        if(ant == NULL){
            f->fim = atual;
        }
        ant = atual;
        atual = proximo;
    }
    f->inicio = ant;
    return 1;
}

int desenfileirar(Fila* f){
    if(f == NULL || f->inicio == NULL) {
        return -1;
    }
    No* no = f->inicio;
    int valor = no->n;
    f->inicio = no->prox;
    if(f->inicio == NULL) {
        f->fim = NULL;
    }
    free(no);
    return valor;
}
