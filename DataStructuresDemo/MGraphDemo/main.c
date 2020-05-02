//
//  main.c
//  MGraphDemo
//
//  Created by SK on 2020/5/1.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define INFINITYC 0
#define MAX_VERTEX_NUM 50
#define TRUE 1
#define FALSE 0

typedef int Status;
typedef char VertexType;
typedef int EdgeType;
typedef int Boolean;

typedef struct MGraph {
    VertexType vexs[MAX_VERTEX_NUM];
    EdgeType arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int numNodes, numEdges;
} MGraph;

void CreateMGraph(MGraph *G) {
    printf("输入顶点数和边数:\n");
    scanf("%d,%d", &G->numNodes, &G->numEdges);
    printf("顶点数:%d,边数:%d\n", G->numNodes, G->numEdges);
    
    int i, j, w;
    for (i = 0; i < G->numNodes; i++) {
        getchar();
        scanf("%c", &G->vexs[i]);
    }
    
    for (i = 0; i < G->numNodes; i++) {
        for (j = 0; j < G->numNodes; i++) {
            G->arc[i][j] = INFINITYC;
        }
    }
    
    for (int k = 0; k < G->numEdges; k++) {
        printf("输入边(vi, vj)上的下标i, 下标j, 权w\n");
        scanf("%d,%d,%d", &i, &j, &w);
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];
    }
    
    for (int i = 0; i < G->numNodes; i++) {
        printf("\n");
        for (int j = 0; j < G->numNodes; j++) {
            printf("%d ",G->arc[i][j]);
        }
    }
    printf("\n");
}

/*
 深度优先搜索
 */

Boolean visited[MAX_VERTEX_NUM];

void DFS(MGraph G, int v) {
    visited[v] = TRUE;
    printf("%c ", G.vexs[v]);
    
    for (int i = 0; i < G.numNodes; i++) {
        if (!visited[i] && G.arc[v][i] == 1) {
            DFS(G, i);
        }
    }
}

void DFSTraverse(MGraph G) {
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }
    
    for (int i = 0; i < G.numNodes; i++) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
    printf("\n");
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("邻接矩阵实现图的存储\n");
    MGraph G;
    CreateMGraph(&G);
    DFSTraverse(G);
    
    return 0;
}
