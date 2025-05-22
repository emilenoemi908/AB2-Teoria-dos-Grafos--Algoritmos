#ifndef KRUSKAL_H
#define KRUSKAL_H

#define MAX 1000

extern int pai[MAX];
extern int rank[MAX];

typedef struct {
    int verticeOrigem;
    int verticeDestino;
    int peso;
} aresta;

extern aresta arestas[];
extern int totalArestas;

void addAresta(int s, int d, int peso);
int compararArestas(const void* a, const void* b);
void makeSet(int nVertices);
int find(int u);
void unionSet(int u, int v);
aresta* kruskal(int nVertices, int* nArestasAgm);
int somarAgm(aresta* arestas, int nArestas);
int getTotalArestas(void);

#endif
