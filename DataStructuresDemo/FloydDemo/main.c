//
//  main.c
//  FloydDemo
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
typedef int Patharc[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

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

void ShortestPath_Floyd(MGraph G, Patharc *P, ShortPathTable *D) {
    int v, w, k;
    for (v = 0; v < G.numVertexes; v++) {
        for (w = 0; w < G.numVertexes; w++) {
            (*D)[v][w] = G.arc[v][w];
            (*P)[v][w] = w;
        }
    }
    
    for (k = 0; k < G.numVertexes; k++) {
        for (v = 0; v < G.numVertexes; v++) {
            for (w = 0; w < G.numVertexes; w++) {
                if ((*D)[v][w] > (*D)[v][k] + (*D)[k][w]) {
                    (*D)[v][w] = (*D)[v][k] + (*D)[k][w];
                    (*P)[v][w] = (*P)[v][k];
                }
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("最短路径弗洛伊德Floyd算法\n");
    int v,w,k;
    MGraph G;
    
    Patharc P;
    ShortPathTable D;
    
    CreateMGraph(&G);
    ShortestPath_Floyd(G,&P,&D);
    
    printf("各顶点间最短路径如下:\n");
    for(v = 0; v < G.numVertexes; v++) {
        for( w = v + 1; w < G.numVertexes; w++) {
            printf("v%d-v%d weight: %d ", v, w, D[v][w]);
            k = P[v][w];
            printf(" path: %d", v);
            while(k != w) {
                printf(" -> %d", k);
                k = P[k][w];
            }
            printf(" -> %d\n",w);
        }
        printf("\n");
    }
    
    //打印最终变换后的最短路径D数组
    printf("最短路径D数组\n");
    for(v = 0; v < G.numVertexes; v++) {
        for(w = 0; w < G.numVertexes; w++) {
            printf("%d\t", D[v][w]);
        }
        printf("\n");
    }
    //打印最终变换后的最短路径P数组
    printf("最短路径P数组\n");
    for(v = 0; v < G.numVertexes; v++) {
        for(w = 0; w < G.numVertexes; w++) {
            printf("%d ", P[v][w]);
        }
        printf("\n");
    }
    return 0;
}
