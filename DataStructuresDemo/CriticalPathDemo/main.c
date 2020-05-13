//
//  main.c
//  CriticalPathDemo
//
//  Created by SK on 2020/5/13.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXEDGE 30
#define MAXVEX 30
#define INFINITYC 65535

typedef int Status;

typedef struct MGraph {
    int vexs[MAXVEX];
    int arc[MAXVEX][MAXVEX];
    int numVertexes, numEdges;
} MGraph;

typedef struct EdgeNode {
    int adjvex; //邻接点域，存储该顶点对应的下标
    int weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct VertexNode {
    int in;
    int data;
    EdgeNode *firstedge;
} VertexNode, AdjList[MAXVEX];

typedef struct {
    AdjList adjList;
    int numVertexes, numEdges;
} graphAdjList, *GraphAdjList;


void CreateMGraph(MGraph *G) {
    int i, j;
    
    G->numEdges = 13;
    G->numVertexes = 10;
    
    for (i = 0; i < G->numVertexes; i++) {
        G->vexs[i] = i;
    }
    
    for (i = 0; i < G->numVertexes; i++) {
        for (j = 0; j < G->numVertexes; j++) {
            if (i == j)
                G->arc[i][j] = 0;
            else
                G->arc[i][j] = INFINITYC;
        }
    }
    
    G->arc[0][1] = 3;
    G->arc[0][2] = 4;
    G->arc[1][3] = 5;
    G->arc[1][4] = 6;
    G->arc[2][3] = 8;
    G->arc[2][5] = 7;
    G->arc[3][4] = 3;
    G->arc[4][6] = 9;
    G->arc[4][7] = 4;
    G->arc[5][7] = 6;
    G->arc[6][9] = 2;
    G->arc[7][8] = 5;
    G->arc[8][9] = 3;
}

void CreateALGraph(MGraph G, GraphAdjList *GL) {
    int i, j;
    EdgeNode *e;
    
    *GL = (GraphAdjList)malloc(sizeof(graphAdjList));
    (*GL)->numVertexes = G.numVertexes;
    (*GL)->numEdges = G.numEdges;
    
    for(i = 0;i < G.numVertexes; i++) {
        (*GL)->adjList[i].in = 0;
        (*GL)->adjList[i].data = G.vexs[i];
        (*GL)->adjList[i].firstedge = NULL;
    }
    
    for(i = 0; i<G.numVertexes; i++) {
        for(j = 0; j<G.numVertexes; j++) {
            if (G.arc[i][j] != 0 && G.arc[i][j] < INFINITYC) {
                e = (EdgeNode *)malloc(sizeof(EdgeNode));
                e->adjvex = j;
                e->weight = G.arc[i][j];
                e->next = (*GL)->adjList[i].firstedge;
                (*GL)->adjList[i].firstedge = e;
                (*GL)->adjList[j].in++;
            }
        }
    }
}


int *etv, *ltv; // 事件最早发生时间和最迟发生时间数组，全局变量
int *stack2;    // 用于存储拓扑序列的栈
int top2;       // 用于stack2的指针

Status TopologicalSort(GraphAdjList GL) {
    int *stack = malloc(sizeof(int) * GL->numVertexes);
    int top = 0;
    for (int i = 0; i < GL->numVertexes; i++) {
        if (GL->adjList[i].in == 0) {
            stack[++top] = i;
        }
    }
    
    top2 = 0;
    stack2 = malloc(sizeof(int) * GL->numVertexes);
    etv = malloc(sizeof(int) * GL->numVertexes);
    for (int i = 0; i < GL->numVertexes; i++) {
        etv[i] = 0;
    }
    
    EdgeNode *e;
    int getTop, k;
    int count = 0;
    while (top != 0) {
        getTop = stack[top--];
        printf("%d -> ", GL->adjList[getTop].data);
        count++;
        
        stack2[++top2] = getTop;
        
        for (e = GL->adjList[getTop].firstedge; e; e = e->next) {
            k = e->adjvex;
            if (--GL->adjList[k].in == 0) {
                stack[++top] = k;
            }
            
            if (etv[getTop] + e->weight > etv[k]) {
                etv[k] = etv[getTop] + e->weight;
            }
        }
    }
    
    if (count < GL->numVertexes) {
        return ERROR;
    }
    
    return OK;
}

void CriticalPath(GraphAdjList GL) {
    int i, k, getTop;
    EdgeNode *e;
    
    TopologicalSort(GL);
    
    ltv = malloc(sizeof(int) * GL->numVertexes);
    for(i = 0; i < GL->numVertexes; i++) {
        ltv[i] = etv[GL->numVertexes - 1];
    }
    
    while (top2 != 0) {
        getTop = stack2[top2--];
        for (e = GL->adjList[getTop].firstedge; e; e = e->next) {
            k = e->adjvex;
            if (ltv[k] - e->weight < ltv[getTop]) {
                ltv[getTop] = ltv[k] - e->weight;
            }
        }
    }
    
    int ete,lte;
    for (int j = 0; j < GL->numVertexes; j++) {
        for (e = GL->adjList[j].firstedge; e; e = e->next) {
            k = e->adjvex;
            ete = etv[j];
            lte = ltv[k] - e->weight;
            if (ete == lte) {
                printf("<%d-%d> length:%d\n", GL->adjList[j].data, GL->adjList[k].data, e->weight);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("关键路径的求解!\n");
    MGraph G;
    GraphAdjList GL;
    CreateMGraph(&G);
    CreateALGraph(G, &GL);
    CriticalPath(GL);
    return 0;
}
