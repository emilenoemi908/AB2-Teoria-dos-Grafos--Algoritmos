#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/prim.h"


void printHelp() {
    printf("Uso: ./prim [opções]\n");
    printf("  -h           : mostra o help\n");
    printf("  -f <arquivo> : arquivo com o grafo de entrada\n");
    printf("  -i <vértice> : vértice inicial para o algoritmo de Prim\n");
    printf("  -s           : mostra a árvore geradora mínima (AGM)\n");
    printf("  -o <arquivo> : redireciona a saída para o arquivo\n");
}

grafo* carregarGrafo(const char* nomeArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    int nVertices,nArestas, origem, destino, peso;
    fscanf(f, "%d %d", &nVertices, &nArestas);

    grafo* g = criarGrafo(nVertices);

   for (int i = 0; i < nArestas; i++) { 
        fscanf(f, "%d %d %d", &origem, &destino, &peso);
        addAresta(g, origem - 1, destino - 1, peso); 
    }


    fclose(f);
    return g;
}

void imprimirAGM(grafo* agm) {
    for (int i = 0; i < agm->nVertices; i++) {
        no* aux = agm->adLists[i];
        while (aux) {
            if (i < aux->vertice) {
                printf("(%d,%d) ", i + 1, aux->vertice + 1);
            }
            aux = aux->prox;
        }
    }
    printf("\n");
}


int main(int argc, char* argv[]) {
    char *entrada = NULL, *saida = NULL;
    int verticeInicial = 0;
    int mostrarSolucao = 0;

   
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
        } else if (strcmp(argv[i], "-s") == 0) {
            mostrarSolucao = 1;
        }
    }

    if (!entrada) {
        fprintf(stderr, "Parâmetros obrigatórios ausentes. Use -h para ajuda.\n");
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

    grafo* g = carregarGrafo(entrada);
    grafo* agm = prim(g, verticeInicial);

    if (mostrarSolucao) {
        if (saida) fclose(out); 
        out = saida ? fopen(saida, "a") : stdout;
        for (int v = 0; v < agm->nVertices; v++) {
            no* temp = agm->adLists[v];
            while (temp) {
                if (v < temp->vertice) {
                    fprintf(out, "(%d,%d) ", v + 1, temp->vertice + 1);
                }
                temp = temp->prox;
            }
        }
        fprintf(out, "\n");
    }

    else{
        printf("%d\n",agm->custoTotal);
    }

    liberarGrafo(g);
    liberarGrafo(agm);

    if (saida && out != stdout) fclose(out);

    return 0;
}
