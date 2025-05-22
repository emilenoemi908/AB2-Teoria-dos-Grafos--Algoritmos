#ifndef PRIM_H
#define PRIM_H

typedef struct no {
    int vertice;
    int peso;
    struct no* prox;
} no;

typedef struct grafo {
    int nVertices;
    int nArestas;
    no** adLists;
    int* visitas;
    int custoTotal;
} grafo;

typedef struct minHeap {
    int capacidade;
    int tamanho;
    int* pos;
    int* vertices;
} minHeap;

// Protótipos
no* criarNo(int vertice, int peso);
grafo* criarGrafo(int nVertices);
void addAresta(grafo* gr, int origem, int destino, int peso);
minHeap* criarMinHeap(int capacidade);
void inserirHeap(minHeap* heap, int vertice, int* chave);
void decreaseKey(minHeap* heap, int vertice, int* chave);
void heapify(minHeap* heap, int i, int* chave);
int removerMinimo(minHeap* min, int* chave);
void trocar(minHeap* min, int a, int b);
grafo* prim(grafo* gr, int s);
int custo(grafo* gr);
void liberarGrafo(grafo* g);

#endif
