#ifndef KOSARAJU_H
#define KOSARAJU_H

#define MAX 1000

typedef struct no {
    int vertice;
    struct no* prox;
} no;

typedef struct grafo {
    int nVertices;
    struct no** adLists;
    int* visitas;
} grafo;

typedef struct {
    int* vertices; 
    int tamanho;   
    int menor_vertice; 
} CFC;

extern int pilha[MAX];
extern int topo;

no* criarNo(int vertice);
grafo* criarGrafo(int nVertices);
void empilhar(int v);
int desempilhar();
void addAresta(struct grafo* gr, int s, int d);
int cmp(const void* a, const void* b);
grafo* grafoReverso(grafo* gr);
void DFS(grafo* gr, int s);
void DFSreverso(grafo* gr, int s, int* comp, int* tamanho);
int cmpC(const void* a, const void* b);
void kosaraju(grafo* gr,  FILE *saida);

#endif