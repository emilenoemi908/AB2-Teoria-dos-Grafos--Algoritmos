#include <stdio.h>
#include <stdlib.h>
#include "../headers/kruskal.h"


int pai[MAX];
int rank[MAX];

aresta arestas[MAX * MAX];
int totalArestas = 0;

void addAresta(int s, int d, int peso){
  
    arestas[totalArestas].verticeOrigem = s;
    arestas[totalArestas].verticeDestino = d;
    arestas[totalArestas].peso = peso;
    totalArestas++;
    
}

int compararArestas(const void* a, const void* b) {
    aresta* ar1 = (aresta*)a;
    aresta* ar2 = (aresta*)b;
    return ar1->peso - ar2->peso;
}

void makeSet(int nVertices){
    for(int i=0; i<nVertices; i++){
        pai[i]=i;
        rank[i]=0;
    }
}

int find(int u) {
    if (pai[u] != u)
        pai[u] = find(pai[u]);
    return pai[u];
}

void unionSet(int u, int v) {
    int raizU = find(u);
    int raizV = find(v);
    if (raizU != raizV) {
        if (rank[raizU] < rank[raizV]) {
            pai[raizU] = raizV;
        } else if (rank[raizU] > rank[raizV]) {
            pai[raizV] = raizU;
        } else {
            pai[raizV] = raizU;
            rank[raizU]++;
        }
    }
}

aresta* kruskal(int nVertices, int* nArestasAgm){

    
    qsort(arestas, totalArestas, sizeof(aresta), compararArestas);
    
    makeSet(nVertices);

    aresta* agm= malloc((nVertices - 1) * sizeof(aresta)); 
    int c = 0;

    for(int i=0; i<totalArestas && c< (nVertices-1); i++){

        if(find(arestas[i].verticeOrigem) != find(arestas[i].verticeDestino)){
            agm[c++]=arestas[i];
            unionSet(arestas[i].verticeOrigem, arestas[i].verticeDestino);
        }
    }
    
    *nArestasAgm = c;

    return agm;

}

int somarAgm(aresta* arestas, int nArestas){
   
    int peso=0;
    for(int i=0; i< nArestas; i++){
        peso+= arestas[i].peso;
    }

    return peso;

}

int getTotalArestas() {
    return totalArestas;
}