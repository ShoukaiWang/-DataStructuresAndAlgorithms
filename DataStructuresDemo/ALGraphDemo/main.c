//
//  main.c
//  ALGraphDemo
//
//  Created by SK on 2020/5/2.
//  Copyright © 2020 SK_Wang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Queue.h"

#define MAX_VERTEX_NUM 50
#define true 1
#define false 0

typedef char Element;
typedef int BOOL;

typedef struct ArcNode {
    int adjvex;
    Element data;
    struct ArcNode *nextArc;
} ArcNode;

typedef struct VNode {
    Element data;
    ArcNode * firstedge;
} VertexNode, Adjlist[MAX_VERTEX_NUM];

typedef struct ALGraph {
    Adjlist adjlist;
    int arc_num;
    int node_num;
    BOOL is_directed;
} ALGraph, *GraphLink;

void CreateGraph(GraphLink *G) {
    printf("输入顶点数目, 边数和方向？：\n");
    scanf("%d %d %d", &(*G)->node_num, &(*G)->arc_num, &(*G)->is_directed);
    
    printf("输入顶点信息：\n");
    int i, j;
    for (i = 0; i < (*G)->node_num; i++) {
        getchar();
        scanf("%c", &(*G)->adjlist[i].data);
        (*G)->adjlist[i].firstedge = NULL;
    }
    
    ArcNode *p;
    printf("输入边信息：\n");
    for (int k = 0; k < (*G)->arc_num; k++) {
        getchar();
        scanf("%d %d", &i, &j);
        
        p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = j;
        p->nextArc = (*G)->adjlist[i].firstedge;
        (*G)->adjlist[i].firstedge = p;
        
        if (!(*G)->is_directed) {
            p = (ArcNode *)malloc(sizeof(ArcNode));
            p->adjvex = i;
            p->nextArc = (*G)->adjlist[j].firstedge;
            (*G)->adjlist[j].firstedge = p;
        }
    }
}

void putGraph(GraphLink G){
    printf("邻接表中存储信息:\n");
    for (int i = 0; i < G->node_num; i++) {
        ArcNode *p = G->adjlist[i].firstedge;
        while (p) {
            printf("%c->%c ", G->adjlist[i].data, G->adjlist[p->adjvex].data);
            p = p->nextArc;
        }
        printf("\n");
    }
}

/*
 邻接表深度优先搜索
 */

BOOL visited[MAX_VERTEX_NUM];

void DFS(ALGraph G, int v) {
    visited[v] = true;
    printf("%c", G.adjlist[v].data);
    
    ArcNode *p;
    p = G.adjlist[v].firstedge;
    
    while (p) {
        if (!visited[p->adjvex]) {
            DFS(G, p->adjvex);
        }
        p = p->nextArc;
    }
}

void DFSTraverse(ALGraph G) {
    for (int i = 0; i < G.node_num; i++) {
        visited[i] = false;
    }
    
    for (int i = 0; i < G.node_num; i++) {
        if (!visited[i]) {
            DFS(G, i);
        }
    }
    printf("\n");
}

/*
邻接表广度优先搜索
*/

void BFSTraverse(ALGraph G) {
    for (int i = 0; i < G.node_num; i++) {
        visited[i] = FALSE;
    }
    
    SqQueue Q;
    InitQueue(&Q);
    ArcNode *p;
    
    for (int i = 0; i < G.node_num; i++) {
        if (!visited[i]) {
            visited[i] = TRUE;
            printf("%c ", G.adjlist[i].data);
            
            EnQueue(&Q, i);
            while (!QueueEmpty(Q)) {
                DeQueue(&Q, &i);
                p = G.adjlist[i].firstedge;
                while (p) {
                    if (!visited[p->adjvex]) {
                        visited[p->adjvex] = TRUE;
                        printf("%c ", G.adjlist[p->adjvex].data);
                        EnQueue(&Q, p->adjvex);
                    }
                    p = p->nextArc;
                }
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    GraphLink g = (ALGraph *)malloc(sizeof(ALGraph));
    CreateGraph(&g);
    putGraph(g);
    return 0;
}
