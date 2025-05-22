#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/floydWarshall.h"


void floydWarshall(int** grafo, int** dist, int V){

    for(int i=0; i< V; i++){
        for(int j=0; j<V; j++){
            dist[i][j]= grafo[i][j];
        }
    }

    for(int k=0; k < V; k++){
        for(int i=0; i < V; i++){
            for(int j=0; j < V; j++){
                if((dist[i][k] + dist[k][j])< dist[i][j]){
                    dist[i][j]= dist[i][k] + dist[k][j];
                }
            }
        }
    }

}
