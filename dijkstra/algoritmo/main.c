#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/djikstra.h"


void printHelp() {
    printf("Uso: ./djikstra [opções]\n");
    printf("  -h           : mostra o help\n");
    printf("  -o <arquivo> : redireciona a saída para o arquivo\n");
    printf("  -f <arquivo> : arquivo com o grafo de entrada\n");
    printf("  -i <vértice> : vértice inicial para o algoritmo de Dijkstra (começa em 1)\n");
}

grafo* carregarGrafoComPesos(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    int nVertices, nArestas;
    fscanf(f, "%d %d", &nVertices, &nArestas);

    grafo* g = criarGrafo(nVertices);
    g->nArestas=nArestas;

    for (int i = 0; i < nArestas; i++) {
        int origem, destino, peso;
        fscanf(f, "%d %d %d", &origem, &destino, &peso);
        addAresta(g, origem -1, destino -1, peso);  // Ajuste para índice baseado em 0
    }

    fclose(f);
    return g;
}

int main(int argc, char *argv[]) {
    char* entrada = NULL;
    char* saida = NULL;
    int verticeInicial = -1;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printHelp();
            return 0;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            entrada = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            saida = argv[++i];
        } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            verticeInicial = atoi(argv[++i]) - 1; 
        }
    }

    if (!entrada) {
        fprintf(stderr, "Erro: Arquivo de entrada não especificado. Use -f <arquivo>.\n");
        return 1;
    }

    if (verticeInicial < 0) {
        verticeInicial = 0; 
    }

    FILE* out = stdout;
    if (saida) {
        out = fopen(saida, "w");
        if (!out) {
            perror("Erro ao abrir arquivo de saída");
            return 1;
        }
    }

    grafo* g = carregarGrafoComPesos(entrada);

    Dijkstra(g, verticeInicial);

    free(g);

    return 0;
}