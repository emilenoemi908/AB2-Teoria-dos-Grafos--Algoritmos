#ifndef DJIKSTRA_H
#define DJIKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct no {
    int vertice;
    struct no* prox;
    int peso;
} no;

typedef struct grafo {
    int nVertices;
    int nArestas;
    struct no** adLists;
    int* visitas;
} grafo;

typedef struct elem {
    int chave;
    int conteudo;
} elem;

typedef struct minHeap {
    int tamanho;
    int capacidade;
    elem* heapArray;
    int* pos;
} minHeap;

grafo* criarGrafo(int nVertices);
void addAresta(grafo* gr, int s, int d, int peso);
no* criarNo(int vertice, int peso);

minHeap* criarHeap(int capacidade);
void trocar(minHeap* minH, int a, int b);
void heapifyD(minHeap* min, int i);
void heapifyU(minHeap* min, int i);
void inserirHeap(minHeap* min, int chave, int vertice);
void decreaseKey(minHeap* min, int vertice, int novaChave);
elem removeMin(minHeap* min);
void relaxar(minHeap* min, int* dist, int* pred, int u, int v, int peso);
void Dijkstra(grafo* gr, int s);

#endif