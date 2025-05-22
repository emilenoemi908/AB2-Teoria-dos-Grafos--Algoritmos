#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "../headers/prim.h"

#define MAX 1000


no* criarNo(int vertice, int peso){
    no* novo= malloc(sizeof(no));
    novo->vertice=vertice;
    novo->peso=peso;
    novo->prox=NULL;
    return novo;
}

grafo* criarGrafo(int nVertices){

    grafo* gr= malloc(sizeof(grafo));
    gr->nVertices=nVertices;
    gr->nArestas=0;
    gr->adLists= malloc(nVertices* sizeof(no*));
    gr->visitas= malloc(nVertices * sizeof(int));
    gr->custoTotal=0;

    for(int i=0; i<nVertices; i++){
        gr->adLists[i]=NULL;
        gr->visitas[i]=0;
    }
    return gr;
}

minHeap* criarMinHeap(int capacidade){

    minHeap* minH= malloc(sizeof(minHeap));
    minH->capacidade= capacidade;
    minH->tamanho=0;
    minH->vertices= malloc(capacidade* sizeof(int));
    minH->pos= (int*) malloc(capacidade * sizeof(int));

    for (int i = 0; i < capacidade; i++) {
        minH->vertices[i] = -1;
        minH->pos[i] = -1;
    }


    return minH;
}

void addAresta(grafo* gr, int origem, int destino, int peso){

    no* noOrigem=criarNo(origem, peso);
    noOrigem->prox= gr->adLists[destino];
    gr->adLists[destino]=noOrigem;

    no* noDestino= criarNo(destino, peso);
    noDestino->prox=gr->adLists[origem];
    gr->adLists[origem]= noDestino;
}

void trocar(minHeap* heap, int a, int b){
    int aux= heap->vertices[a];
    heap->vertices[a] = heap->vertices[b];
    heap->vertices[b] = aux;
    

    heap->pos[heap->vertices[a]] = a;
    heap->pos[heap->vertices[b]] = b;
}

void inserirHeap(minHeap* heap, int vertice, int* chave){

    int i= heap->tamanho;
    heap->vertices[i] = vertice;
    heap->pos[vertice] = i;
    heap->tamanho++;

    while(i != 0 && chave[heap->vertices[(i-1)/2]] > chave[heap->vertices[i]]){
        trocar(heap, (i-1)/2, i);
        i=(i-1)/2;
    }


}

void decreaseKey(minHeap* heap, int vertice, int* chave){

    int i = heap->pos[vertice];
    
    while(i != 0 && chave[heap->vertices[(i-1)/2]] > chave[heap->vertices[i]]){
        trocar(heap, (i-1)/2, i);
        i = (i-1)/2;
    }
}


void heapify(minHeap* heap, int i, int* chave){
    
    int menor=i;
    int filhoE= 2* i + 1;
    int filhoD= 2* i + 2;


    if(filhoE < heap->tamanho && chave[heap->vertices[filhoE]] < chave[heap->vertices[menor]]) {
        menor=filhoE;
    }

    if (filhoD < heap->tamanho && chave[heap->vertices[filhoD]] < chave[heap->vertices[menor]]){
        menor=filhoD;
    }

    if(menor != i){
        trocar(heap, i, menor);
        heapify(heap, menor, chave);
    }
}

int removerMinimo(minHeap* heap, int* chave){

    if (heap->tamanho == 0) {
       exit(1);
    }

    int i= heap->vertices[0];
    int j= heap->vertices[heap->tamanho-1];

    heap->vertices[0] = j;
    heap->pos[j] = 0;
    heap->pos[i] = -1;

    heap->tamanho--;

    heapify(heap, 0, chave);

    return i;

}

grafo* prim(grafo* gr, int s){

    int* chave = malloc(gr->nVertices * sizeof(int));
    int* prev = (int*)malloc(gr->nVertices * sizeof(int)); 
    
    minHeap* heap= criarMinHeap(gr->nVertices);

    for(int i=0; i<gr->nVertices; i++){

        chave[i]=INT_MAX;
        prev[i]=-1;
        heap->pos[i]=-1;
    }

    chave[s] = 0;
    inserirHeap(heap, s, chave);

    grafo* agm= criarGrafo(gr->nVertices);

    while(heap->tamanho != 0){
       int v = removerMinimo(heap, chave);

        if(gr->visitas[v]==1)continue;

        gr->visitas[v]=1;

        if (prev[v] != -1) {
            addAresta(agm, prev[v], v, chave[v]);
            agm->custoTotal+= chave[v];
            agm->nArestas++;
        }
    
        no* adj= gr->adLists[v];

        while(adj != NULL) {

            int u= adj->vertice;

            if (!gr->visitas[u] && adj->peso < chave[u]) {
                chave[u] = adj->peso;
                prev[u] = v;

                if (heap->pos[u] == -1){
                    inserirHeap(heap, u, chave);
                }
                else{
                    decreaseKey(heap, u, chave);
                }
            }

            adj=adj->prox;
        }
    }

    free(prev);
    free(chave);
    free(heap->vertices);
    free(heap->pos);
    free(heap);

    return agm;

}

void liberarGrafo(grafo* g) {
    if (g == NULL) {
        return; 
    }

    for (int i = 0; i < g->nVertices; i++) {
        no* atual = g->adLists[i];
        while (atual != NULL) {
            no* proximo = atual->prox; 
            free(atual);
            atual = proximo;
        }
    }

    free(g->adLists);
    free(g->visitas);
    free(g);
}