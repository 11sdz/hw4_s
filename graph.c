#include<stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include "graph.h"


typedef enum bool {
	True=1,
	False=0
	}bool;

typedef struct GRAPH_NODE_ *pnode;;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

void build_graph_cmd(pnode *head){
    int num=0,id=-1,weight=-1,dest=-1;
    scanf("%d",&num);
    char c=getchar();
    while(num>0){
        pedge p_edge =malloc(sizeof(pedge));
        scanf("%d",&id);
        node cur;
        cur.node_num=id;
        cur.edges=p_edge;
        while(scanf("%d",&id)){
            scanf("%d",&weight);
            edge curr_edge;
            curr_edge.endpoint=id;
            curr_edge.weight=weight;
            if(!head){
                head=&cur;
            }
            if(!cur.edges){
                
            }
        }
        num--;
    }

}
void insert_node_cmd(pnode *head){

}
void delete_node_cmd(pnode *head){

}
void printGraph_cmd(pnode head){

} //for self debug

void deleteGraph_cmd(pnode* head){

}
void shortsPath_cmd(pnode head){

}
void TSP_cmd(pnode head){

}