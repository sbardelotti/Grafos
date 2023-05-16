#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED
typedef struct fila Fila;

Fila* CriaFila();
void LiberaFila(Fila* f);
int TamanhoFila(Fila* f);
int FilaVazia(Fila* f);
int InsereFila(Fila* f, int n);
int RemoveFila(Fila* f);
int ConsultaFila(Fila* f, int* n);
void ImprimirFila(Fila* f);
int InverterFila(Fila* f);

int desenfileirar(Fila* f);

#endif // FILA_H_INCLUDED
