#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/kosaraju.h"


no* criarNo(int vertice) {
    struct no* novoNo = malloc(sizeof(no));
    novoNo->vertice = vertice;
    novoNo->prox = NULL;
    return novoNo;
}

grafo* criarGrafo(int nVertices) {
    struct grafo* gr = malloc(sizeof(grafo));
    gr->nVertices = nVertices;
    gr->adLists = malloc(nVertices * sizeof(no*));
    gr->visitas = malloc(nVertices * sizeof(int));

    for (int i = 0; i < gr->nVertices; i++) {
        gr->adLists[i] = NULL;
        gr->visitas[i] = 0;  
    }

    return gr;
}

int pilha[MAX];
int topo = -1;

void empilhar(int v){
    pilha[++topo] = v;
}

int desempilhar(){
    return pilha[topo--];
}

void addAresta(struct grafo* gr, int s, int d) {
    struct no* noDestino = criarNo(d);
    noDestino->prox = gr->adLists[s];
    gr->adLists[s] = noDestino;
}

int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}


grafo* grafoReverso(grafo* gr){

    grafo* reverso= criarGrafo(gr->nVertices);

    for(int i=0; i<gr->nVertices; i++){

        no* aux= gr->adLists[i];

        while(aux != NULL){
            addAresta(reverso, aux->vertice, i);
            aux=aux->prox;
        }
    }

    return reverso;
}


void DFS(grafo* gr, int s){

    gr->visitas[s]=1;
    no* aux= gr->adLists[s];

    while(aux !=NULL){

        if(gr->visitas[aux->vertice]==0){
            DFS(gr, aux->vertice);
        }

        aux=aux->prox;
    }

    empilhar(s);
    
}

void DFSreverso(grafo* gr, int s, int* comp,  int* tamanho) {
    gr->visitas[s] = 1;
    comp[(*tamanho)++] = s + 1;

    no* aux = gr->adLists[s];
    while (aux != NULL) {
        if (gr->visitas[aux->vertice] == 0) {
            DFSreverso(gr, aux->vertice, comp, tamanho);
        }
        aux = aux->prox;
    }
}

int cmpC(const void* a, const void* b) {
    CFC* cfc1 = *(CFC**)a; 
    CFC* cfc2 = *(CFC**)b; 

   if (cfc1->tamanho == 1 && cfc1->menor_vertice == 1) {
        return -1; 
    }
    if (cfc2->tamanho == 1 && cfc2->menor_vertice == 1) {
        return 1; 
    }

    if (cfc1->tamanho != cfc2->tamanho) {
        return cfc2->tamanho - cfc1->tamanho;
    }

   return cfc1->menor_vertice - cfc2->menor_vertice;
}

void kosaraju(grafo* gr,  FILE *saida){

    CFC* cfcs[MAX];
    int nCfcs = 0;

    for(int i=0; i<gr->nVertices; i++){
        
        if(gr->visitas[i] == 0){
            DFS(gr,i);
        }
    }

    grafo* novo= grafoReverso(gr);

    for(int k=0; k<gr->nVertices; k++){
        gr->visitas[k]=0;
    }

    while(topo != -1){

       int s= desempilhar();

       if(novo->visitas[s] == 0) {
            int comp[MAX];
            int tamanho = 0;

            DFSreverso(novo, s, comp, &tamanho);

            qsort(comp, tamanho, sizeof(int), cmp);

            CFC* novo = (CFC*) malloc(sizeof(CFC));
            novo->vertices = (int*) malloc(tamanho * sizeof(int));
            memcpy(novo->vertices, comp, tamanho * sizeof(int));
            novo->tamanho = tamanho;
            novo->menor_vertice = comp[0]; 

            
            cfcs[nCfcs++] = novo;
       }
    }

    qsort(cfcs, nCfcs, sizeof(CFC*), cmpC);

    for (int i = 0; i < nCfcs; i++) {
        
        if (i > 0) {
            fprintf(saida, "\n");
        }

        for (int j = 0; j < cfcs[i]->tamanho; j++) {
            fprintf(saida, "%d ", cfcs[i]->vertices[j]);
        }
        
        free(cfcs[i]->vertices);
        free(cfcs[i]);
    }

   
}
