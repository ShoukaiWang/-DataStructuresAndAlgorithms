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
#include "Queue.h"

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

/*
邻接矩阵广度优先搜索
*/

void BFSTraverse(MGraph G) {
    for (int i = 0; i < G.numNodes; i++) {
        visited[i] = FALSE;
    }
    
    SqQueue Q;
    InitQueue(&Q);
    
    for (int i = 0; i < G.numNodes; i++) {
        if (!visited[i]) {
            visited[i] = TRUE;
            printf("%c ", G.vexs[i]);
            
            EnQueue(&Q, i);
            while (!QueueEmpty(Q)) {
                DeQueue(&Q, &i);
                for (int j = 0; j < G.numNodes; j++) {
                    if (G.arc[i][j] == 1 && !visited[j]) {
                        visited[j] = TRUE;
                        printf("%c ", G.vexs[j]);
                        EnQueue(&Q, j);
                    }
                }
            }
        }
    }
}



void CreateMGraphTest(MGraph *G) {
    int i, j;
    
    //1. 确定图的顶点数以及边数
    G->numEdges=15;
    G->numNodes=9;
    
    /*2.读入顶点信息，建立顶点表 */
    G->vexs[0]='A';
    G->vexs[1]='B';
    G->vexs[2]='C';
    G->vexs[3]='D';
    G->vexs[4]='E';
    G->vexs[5]='F';
    G->vexs[6]='G';
    G->vexs[7]='H';
    G->vexs[8]='I';
    
    /*3. 初始化图中的边表*/
    for (i = 0; i < G->numNodes; i++)
    {
        for ( j = 0; j < G->numNodes; j++)
        {
            G->arc[i][j]=0;
        }
    }
    
    /*4.将图中的连接信息输入到边表中*/
    G->arc[0][1]=1;
    G->arc[0][5]=1;
    
    G->arc[1][2]=1;
    G->arc[1][8]=1;
    G->arc[1][6]=1;
    
    G->arc[2][3]=1;
    G->arc[2][8]=1;
    
    G->arc[3][4]=1;
    G->arc[3][7]=1;
    G->arc[3][6]=1;
    G->arc[3][8]=1;
    
    G->arc[4][5]=1;
    G->arc[4][7]=1;
    
    G->arc[5][6]=1;
    
    G->arc[6][7]=1;
    
    /*5.无向图是对称矩阵.构成对称*/
    for(i = 0; i < G->numNodes; i++)
    {
        for(j = i; j < G->numNodes; j++)
        {
            G->arc[j][i] =G->arc[i][j];
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("邻接矩阵实现图的存储\n");
    MGraph G;
//    CreateMGraph(&G);
//    DFSTraverse(G);
    
    CreateMGraphTest(&G);
    BFSTraverse(G);
    printf("\n");
    
    return 0;
}
