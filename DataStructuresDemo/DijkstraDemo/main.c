//
//  main.c
//  DijkstraDemo
//
//  Created by SK on 2020/5/9.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXEDGE 20
#define MAXVEX 20
#define INFINITYC 65535

typedef int Status;
typedef int Patharc[MAXVEX];
typedef int ShortPathTable[MAXVEX];

typedef struct MGraph {
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

void CreateMGraph(MGraph *G) {
    int i, j;
    
    G->numEdges=16;
    G->numVertexes=9;
    
    for (i = 0; i < G->numVertexes; i++) {
        G->vexs[i] = i;
    }
    
    for (i = 0; i < G->numVertexes; i++) {
        for (j = 0; j < G->numVertexes; j++) {
            if (i == j)
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = G->arc[j][i] = INFINITYC;
        }
    }
    
    G->arc[0][1] = 1;
    G->arc[0][2] = 5;
    G->arc[1][2] = 3;
    G->arc[1][3] = 7;
    G->arc[1][4] = 5;
    
    G->arc[2][4] = 1;
    G->arc[2][5] = 7;
    G->arc[3][4] = 2;
    G->arc[3][6] = 3;
    G->arc[4][5] = 3;
    
    G->arc[4][6] = 6;
    G->arc[4][7] = 9;
    G->arc[5][7] = 5;
    G->arc[6][7] = 2;
    G->arc[6][8] = 7;
    
    G->arc[7][8] = 4;
    
    for(i = 0; i < G->numVertexes; i++) {
        for(j = i; j < G->numVertexes; j++) {
            G->arc[j][i] = G->arc[i][j];
        }
    }
}

/// 最短路径 - Dijkstra 算法
/// @param G 网图
/// @param v0 开始的顶点
/// @param P 前驱顶点下标
/// @param D 表示从V0到V的最短路径长度和
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc *P, ShortPathTable *D) {
    int v, w, k, min;
    k = 0;
    int final[MAXVEX];
    
    for (v = 0; v < G.numVertexes; v++) {
        final[v] = 0;
        (*D)[v] = G.arc[v0][v];
        (*P)[v] = 0;
    }
    
    final[v0] = 1;
    (*D)[v0] = 0;
    (*P)[v0] = -1;
    
    for (v = 1; v < G.numVertexes; v++) {
        min = INFINITYC;
        for (w = 0; w < G.numVertexes; w++) {
            if (!final[w] && (*D)[w] < min) {
                k = w;
                min = (*D)[w];
            }
        }
        
        final[k] = 1;
        
        for (w = 0; w < G.numVertexes; w++) {
            if (!final[w] && min + G.arc[k][w] < (*D)[w]) {
                (*D)[w] = min + G.arc[k][w];
                (*P)[w] = k;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("最短路径-Dijkstra算法\n");
    
    MGraph G;
    Patharc P;
    ShortPathTable D;
    int v0 = 0;
    
    CreateMGraph(&G);
    ShortestPath_Dijkstra(G, v0, &P, &D);
    
    printf("最短路径路线:\n");
    int i, j;
    for(i = 1; i < G.numVertexes; i++) {
        printf("v%d -> v%d : ", v0, i);
        j = i;
        while(P[j] != -1) {
            printf("%d ", P[j]);
            j = P[j];
        }
        printf("\n");
    }
    
    printf("\n最短路径权值和\n");
    for(i = 1; i < G.numVertexes; ++i)
        printf("v%d -> v%d : %d \n", G.vexs[0], G.vexs[i], D[i]);
    
    printf("\n");
    
    return 0;
}
