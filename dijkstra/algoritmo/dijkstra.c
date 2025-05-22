#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../headers/djikstra.h"

no* criarNo(int vertice, int peso){

    no* novoNo=malloc(sizeof(no));
    novoNo->vertice=vertice;
    novoNo->peso = peso;
    novoNo->prox=NULL;

    return novoNo;
}

grafo* criarGrafo(int nVertices){

    grafo* gr=malloc(sizeof(grafo));
    gr->nVertices=nVertices;
    gr->adLists=malloc(nVertices * sizeof(no*));
    gr->visitas= malloc(nVertices * sizeof(int));

    for(int i=0; i<gr->nVertices; i++){

        gr->adLists[i]=NULL;
        gr->visitas[i]=0;
    }

    return gr;

}

void addAresta(grafo* gr, int  s, int d, int peso){

    no* noDestino = criarNo(d, peso);
    noDestino->prox = gr->adLists[s];
    gr->adLists[s] = noDestino;

    no* noOrigem = criarNo(s, peso);
    noOrigem->prox = gr->adLists[d];
    gr->adLists[d] = noOrigem;
}

minHeap* criarHeap(int capacidade){

    minHeap* minH= malloc(sizeof(minHeap));
    minH->capacidade= capacidade;
    minH->tamanho=0;
    minH->heapArray = malloc(capacidade * sizeof(elem));
    minH->pos = (int*) malloc(capacidade * sizeof(int));
    
    for (int i = 0; i < capacidade; i++){
        minH->pos[i] = -1;
    }
    return minH;
}

void trocar(minHeap* minH, int a, int b){
    elem aux = minH->heapArray[a];

    minH->heapArray[a] = minH->heapArray[b];
    minH->heapArray[b] = aux;

    minH->pos[minH->heapArray[a].conteudo] = a;
    minH->pos[minH->heapArray[b].conteudo] = b;
}

void heapifyD(minHeap* min, int i){

    int menor=i;
    int filhoD= 2* i + 2;
    int filhoE= 2* i + 1;

    if(filhoE < min->tamanho && min->heapArray[filhoE].chave< min->heapArray[menor].chave) {
        menor=filhoE;
    }

    if (filhoD < min->tamanho && min->heapArray[filhoD].chave < min->heapArray[menor].chave){
        menor=filhoD;
    }

    if(menor != i){
        trocar(min, i, menor);
        heapifyD(min, menor);
    }
    
}

void heapifyU(minHeap* min, int i) {
    while (i > 0 && min->heapArray[(i-1)/2].chave > min->heapArray[i].chave) {
        trocar(min, i, (i-1)/2);
        i = (i-1)/2;
    }
}

void inserirHeap(minHeap* min, int chave, int vertice){

    if(min->pos[vertice] != -1){
        if (chave < min->heapArray[min->pos[vertice]].chave){
             decreaseKey(min, vertice, chave); 
        }
        return;
    }

    int i = min->tamanho++;
    min->heapArray[i].chave = chave;
    min->heapArray[i].conteudo = vertice;
    min->pos[vertice] = i;
    heapifyU(min, i);

}

void decreaseKey(minHeap* min, int vertice, int novaChave){
    int i = min->pos[vertice];
    min->heapArray[i].chave = novaChave;
    heapifyU(min, i);
}


elem removeMin(minHeap* min){

    elem minimo = min->heapArray[0];
    min->pos[minimo.conteudo] = -1;
    min->heapArray[0]= min->heapArray[--min->tamanho];
    min->pos[min->heapArray[0].conteudo] = 0;
    heapifyD(min, 0);
    return minimo;

}

void relaxar(minHeap* min, int* dist, int* pred, int u, int v, int peso) {
    if (dist[v] > dist[u] + peso) {
        dist[v] = dist[u] + peso;
        pred[v] = u;
        
        if(min->pos[v] == -1){
            inserirHeap(min, dist[v], v);
        } else {
            decreaseKey(min, v, dist[v]);
        }
    }
}

void Dijkstra(grafo* gr, int s){

    int dist[gr->nVertices];
    int pred[gr->nVertices]; 

    for(int i=0; i< gr->nVertices; i++){

        dist[i]=INT_MAX;
        pred[i]=-1;
    }

    dist[s]=0;

    minHeap* heapMin= criarHeap(gr->nVertices);
    inserirHeap(heapMin, 0, s);

    while(heapMin->tamanho > 0){
        elem menor= removeMin(heapMin);
        int u = menor.conteudo;

        
        if (gr->visitas[u]) continue;

        gr->visitas[u]=1;
        
        no* aux=gr->adLists[u];
        while(aux){
        
            int v=aux->vertice;
            int peso= aux->peso;
            
            if(!gr->visitas[v]){
                relaxar(heapMin, dist, pred, u, v, peso);
            }

            aux=aux->prox;
        }
        
    }
    for (int i = 0; i < gr->nVertices; i++) {
        if (dist[i] == INT_MAX)
            printf("%d:-1 ", i+1);
        else
            printf("%d:%d ", i+1, dist[i]);
    }
    
    free(heapMin->heapArray);
    free(heapMin->pos);
    free(heapMin);
}