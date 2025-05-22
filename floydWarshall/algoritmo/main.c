#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/floydWarshall.h"

void printHelp() {
    printf("Uso: ./floyd [opções]\n");
    printf("  -h            : mostra o help\n");
    printf("  -f <arquivo>  : arquivo com o grafo de entrada\n");
    printf("  -o <arquivo>  : redireciona a saída para o arquivo\n");
    printf("  -s            : mostra a matriz de distâncias mínimas\n");
}

int** carregarGrafo(const char* nomeArquivo, int* nVertices) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE); 
    }

    int nArestas;
    if (fscanf(f, "%d %d", nVertices, &nArestas) != 2) { 
        fprintf(stderr, "Erro ao ler número de vértices e arestas do arquivo %s\n", nomeArquivo);
        fclose(f);
        exit(EXIT_FAILURE);
    }

    int** grafo = malloc((*nVertices) * sizeof(int*));
    if (grafo == NULL) {
        perror("Erro ao alocar memória para linhas do grafo");
        fclose(f);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < *nVertices; i++) {
        grafo[i] = malloc((*nVertices) * sizeof(int));
        if (grafo[i] == NULL) {
            perror("Erro ao alocar memória para colunas do grafo");

            for (int k = 0; k < i; k++) {
                free(grafo[k]);
            }
            free(grafo);
            fclose(f);
            exit(EXIT_FAILURE);
        }
        
        for (int j = 0; j < *nVertices; j++) {
            grafo[i][j] = (i == j) ? 0 : INF;
        }
    }

    int origem, destino, peso;
    for (int i = 0; i < nArestas; i++) {
        if (fscanf(f, "%d %d %d", &origem, &destino, &peso) != 3) { 
            fprintf(stderr, "Erro ao ler aresta %d do arquivo %s\n", i + 1, nomeArquivo);
           
            for (int k = 0; k < *nVertices; k++) {
                free(grafo[k]);
            }
            free(grafo);
            fclose(f);
            exit(EXIT_FAILURE);
        }
        
        grafo[origem - 1][destino - 1] = peso;
    }

    fclose(f); 
    return grafo;
}

void imprimirMatriz(int** matriz, int V, FILE* out) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matriz[i][j] == INF) {
                fprintf(out, "INF "); 
            } else {
                fprintf(out, "%3d ", matriz[i][j]); 
            }
        }
        fprintf(out, "\n"); 
    }
}



int main(int argc, char* argv[]) {
    char *entrada = NULL, *saida = NULL;
    int mostrarSolucao = 0;

    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printHelp();
            return 0; 
        } else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                entrada = argv[++i]; 
            } else {
                fprintf(stderr, "Erro: A opção -f requer um nome de arquivo.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                saida = argv[++i];  
            } else {
                fprintf(stderr, "Erro: A opção -o requer um nome de arquivo.\n");
                return 1;
            }
        } else if (strcmp(argv[i], "-s") == 0) {
            mostrarSolucao = 1; 
        } else {
            fprintf(stderr, "Opção inválida: %s. Use -h para ajuda.\n", argv[i]);
            return 1; 
        }
    }

    if (!entrada) {
        fprintf(stderr, "Parâmetros obrigatórios ausentes. Use -h para ajuda.\n");
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

    int V; 
    int** grafo = carregarGrafo(entrada, &V);

    int** dist = malloc(V * sizeof(int*));
    if (dist == NULL) {
        perror("Erro ao alocar memória para linhas da matriz de distâncias mínimas (dist)");
        
        for (int i = 0; i < V; i++) {
            free(grafo[i]);
        }
        free(grafo);
        if (saida && out != stdout) fclose(out);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < V; i++) {
        dist[i] = malloc(V * sizeof(int));
        if (dist[i] == NULL) {
            perror("Erro ao alocar memória para colunas da matriz de distâncias mínimas (dist)");
           
            for (int k = 0; k < i; k++) {  
                free(dist[k]);
            }
            free(dist); 
            for (int k = 0; k < V; k++) {  
                free(grafo[k]);
            }
            free(grafo);
            if (saida && out != stdout) fclose(out);
            exit(EXIT_FAILURE);
        }
    }

    floydWarshall(grafo, dist, V);

    if (mostrarSolucao) {
        imprimirMatriz(dist, V, out);
    }


    for (int i = 0; i < V; i++) {
        free(grafo[i]); 
        free(dist[i]);  
    }
    free(grafo); 
    free(dist);   

    if (saida && out != stdout) fclose(out);

    return 0; 

}