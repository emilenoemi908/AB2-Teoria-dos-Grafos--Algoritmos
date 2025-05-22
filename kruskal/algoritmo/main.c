#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/kruskal.h" 


void printHelp() {
    printf("Uso: ./kruskal [opções]\n");
    printf("  -h           : mostra o help\n");
    printf("  -f <arquivo> : arquivo com o grafo de entrada\n");
    printf("  -s           : mostra a árvore geradora mínima (AGM)\n");
    printf("  -o <arquivo> : redireciona a saída para o arquivo\n");
}


void carregarArestasParaKruskal(const char* nomeArquivo, int* nVertices, int* nArestasArquivo) {
    FILE* f = fopen(nomeArquivo, "r");
    if (!f) {
        perror("Erro ao abrir arquivo");
        exit(EXIT_FAILURE); 
    }

    if (fscanf(f, "%d %d", nVertices, nArestasArquivo) != 2) {
        fprintf(stderr, "Erro ao ler V e E do arquivo %s\n", nomeArquivo);
        fclose(f);
        exit(EXIT_FAILURE);
    }

    extern int totalArestas; 
    totalArestas = 0; 

    for (int i = 0; i < *nArestasArquivo; i++) {
        int origem, destino, peso;
        if (fscanf(f, "%d %d %d", &origem, &destino, &peso) != 3) {
            fprintf(stderr, "Erro ao ler aresta %d do arquivo %s\n", i + 1, nomeArquivo);
            fclose(f);
            exit(EXIT_FAILURE);
        }
        
        addAresta(origem - 1, destino - 1, peso);
    }

    fclose(f);
}

void imprimirAGM_Kruskal(aresta* agm, int nArestasAgm, FILE* out) {
    for (int i = 0; i < nArestasAgm; i++) {
        fprintf(out, "(%d,%d) ", agm[i].verticeOrigem + 1, agm[i].verticeDestino + 1);
    }
    fprintf(out, "\n");
}

int main(int argc, char* argv[]) {
    char *entrada = NULL, *saida = NULL;
    int mostrarSolucao = 0; 
    int verticeInicial = -1;

    
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            printHelp();
            return 0;
        } 
        else if (strcmp(argv[i], "-f") == 0) {
            if (i + 1 < argc) {
                entrada = argv[++i];
            } 
            else {
                fprintf(stderr, "Erro: A opção -f requer um nome de arquivo.\n");
                return 1;
            }
        } 
        else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                saida = argv[++i];
            } 
            else {
                fprintf(stderr, "Erro: A opção -o requer um nome de arquivo.\n");
                return 1;
            }
        } 
        
        else if (strcmp(argv[i], "-i") == 0) { 
            if (i + 1 < argc) {
                verticeInicial = atoi(argv[++i]) - 1; // Captura e converte o vértice inicial para 0-based
            } 
            else {
                fprintf(stderr, "Erro: A opção -i requer um número de vértice.\n");
                return 1;
            }
        }
        else if (strcmp(argv[i], "-s") == 0) {
            mostrarSolucao = 1; // Ativa a exibição da AGM
        } 
        else {
            fprintf(stderr, "Opção inválida: %s. Use -h para ajuda.\n", argv[i]);
            return 1;
        }
    }

    if (!entrada) {
        fprintf(stderr, "Parâmetros obrigatórios ausentes. Use -h para ajuda.\n");
        return 1;
    }

    int nVertices, nArestas;
    
    carregarArestasParaKruskal(entrada, &nVertices, &nArestas);

    if (verticeInicial != -1 && nVertices > 0 && 
        (verticeInicial < 0 || verticeInicial >= nVertices)) {
        fprintf(stderr, "Aviso: Vértice inicial (%d) fora do alcance do grafo com %d vértices. Ignorando para Kruskal.\n", verticeInicial + 1, nVertices);
    }


   int nArestasAgm = 0;
    aresta* agm = kruskal(nVertices, &nArestasAgm);

    FILE* out = stdout;
    if (saida) {
        out = fopen(saida, "w");
        if (!out) {
            perror("Erro ao abrir arquivo de saída");
            free(agm); // Libera AGM antes de sair
            return 1;
        }
    }

    if (mostrarSolucao) {
        imprimirAGM_Kruskal(agm, nArestasAgm, out);
    }
    else {
        int pesoTotal = somarAgm(agm, nArestasAgm);
        fprintf(out, "%d\n", pesoTotal);
    }

    free(agm); 
    if (saida && out != stdout) fclose(out); 

    return 0; 
}
