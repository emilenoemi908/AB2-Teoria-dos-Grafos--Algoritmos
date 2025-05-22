#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/kosaraju.h"

void printHelp() {
    printf("Uso: ./kosaraju [opções]\n");
    printf("  -h           : mostra o help\n");
    printf("  -o <arquivo> : redireciona a saída para o arquivo\n");
    printf("  -f <arquivo> : arquivo com o grafo de entrada\n");
}

grafo* carregarGrafo(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    int nVertices,nArestas;
    fscanf(f, "%d %d", &nVertices, &nArestas);

    grafo* g = criarGrafo(nVertices);

    for (int i = 0; i < nArestas; i++) {
        int origem, destino;
        fscanf(f, "%d %d", &origem, &destino);
        addAresta(g, origem - 1, destino - 1);
    }

    fclose(f);
    return g;
}

int main(int argc, char *argv[]) {
    char* entrada = NULL;
    char* saida = NULL;


    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printHelp();
            return 0;
        } else if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            entrada = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            saida = argv[++i];
        }
    }
           

    if (!entrada) {
        printf("Erro: Arquivo de entrada não especificado. Use -f <arquivo>.\n");
        return 1;
    }

    FILE* out = stdout;
    if (saida) {
        out = fopen(saida, "w");
        if (!out) {
            perror("Erro ao abrir arquivo de saída");
            return 1;
        }
    }

    grafo* g = carregarGrafo(entrada);

    kosaraju(g, out);

    if (saida) fclose(out);

    return 0;
}