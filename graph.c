#include<stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include <limits.h>
#include "graph.h"


typedef enum bool {
    True=1,
    False=0
}bool;


pnode new_node(pnode next, int i);
pedge new_edge(pedge next,pnode dest,int weight);
pnode get_node(pnode head,int node_num);
pnode get_node_by_id(pnode *head,int id);
void insert_last_node(int id,pnode *head);
void insert_last_edge(pnode *curr, int source,int dest,int weight);
void delete_edges(pnode *curr);
void delete_edges_to(pedge *head,pnode curr);
void delete_all_node(pnode *curr);
int * adjancy_matrix(pnode *head,int size);
int dijkstra(int *adj_mat,int size,int src,int dest);
/*
 * Building Graph
 */
void build_graph_cmd(pnode *head){
    printf("----------BUILD GRAPH---------\n");
    int num=0;
    pnode *h=head;
    scanf("%d",&num);
    for (int i = 0; i < num; ++i) {
        insert_last_node(i,head);
    }
    printf("\n");
    int dest ,weight , id;
    for (int i = 0; i < num; ++i) {
        h=head;
        printf("enter n\n");
        char c='\n';
        while((c=getchar())!='n');
        printf("%d",(int)c);
        printf("\n");
        if(c=='n') {
            scanf("%d", &id);
        }
        pnode curr=get_node(*h,id);
        while(scanf("%d",&dest) && scanf("%d",&weight)){
            insert_last_edge(h,id, dest,weight);
        }
    }
}
/*
 * get node with index id
 */
pnode get_node(pnode head,int node_num){
    while (head){
        if((head->node_num)==node_num) {
            printf("\nfound node %d\n", head->node_num);
            return head;
        }
        head=head->next;
    }
    printf("no such node %d\n",node_num);
    return NULL;
}
/*
 * creating new Node
 * with id
 */
pnode new_node(pnode next,int id){
    pnode p =(pnode) malloc(sizeof(node));
    if(!p){
        printf("error");
        exit(1);
    }
    p->node_num=id;
    p->next=next;
    return p;
}
/*
 * insert new node to last of linked list
 */
void insert_last_node(int id,pnode *head){
    pnode *h=head;
    while(*h){
        h= &((*h)->next);
    }
    printf("new node= %d , ",id);
    *h= new_node(NULL,id);
}
/*
 * inserting edge to last index in linked list
 * curr pointer to the Node being worked on
 */
void insert_last_edge(pnode *curr, int source,int dest,int weight){
    pnode pn_source = get_node(*curr, source);
    pnode pn_dest = get_node(*curr, dest);
    pedge *h=&(pn_source->edges);
    while(*h){
        h= &((*h)->next);
    }
    printf("new edge from  %d to %d ,  ", pn_source->node_num, pn_dest->node_num);
    *h= new_edge(NULL, pn_dest, weight);
}
/*
 * creating new edge
 */
pedge new_edge(pedge next,pnode dest,int weight){
    pedge p =(pedge) malloc(sizeof(edge));
    if(!p){
        printf("error");
        exit(1);
    }
    p->weight=weight;
    p->endpoint=dest;
    p->next=next;
    return p;
}

void insert_node_cmd(pnode *head){
    printf("----------INSERT NODE CMD--------\n");
    int id,dest,weight;
    scanf("%d",&id);
    pnode curr=get_node(*head,id);
    if(curr) {
        delete_edges(&curr);
    }else{
        insert_last_node(id,head);
    }
    while (scanf("%d",&dest) && scanf("%d",&weight)){
        insert_last_edge(head,id,dest,weight);
    }
}
/*
 * Deleting edges for current node
 * and free memory
 */
void delete_edges(pnode *curr){
    pedge *h=&((*curr)->edges);
    if(!*h) return;
    pedge p=*h;
    while(*h){
        p=*h;
        *h=(*h)->next;
        free(p);
    }
}
void delete_all_node(pnode *curr){
    pnode *h=curr;
    if(!*h)return;
    pnode p=*h;
    while(*h){
        p=*h;
        *h=(*h)->next;
        free(p);
    }
}

void delete_node_cmd(pnode *head){
    printf("\n enter num of node to delete\n");
    int id = scanf("%d",&id);
    id=6;
    printf("\n DELETE NODE %d",id);
    pnode curr= get_node(*head,id);
    delete_edges(&curr);
    pnode *h=head;
    while(*h){
        if((*h)!=curr) {
            if((*h)->node_num==5){
                printf("\nNode 5 found debug !\n");
            }
            delete_edges_to(&((*h)->edges), curr);
        }
        h= &((*h)->next);
    }
    h=head;
    pnode prev;
    while((*h)!=curr){
        prev=(*h);
        h= &((*h)->next);
    }
    prev->next=(*h)->next;
    free(curr);

}
void delete_edges_to(pedge *head,pnode curr){
    if(!*head){
        return;
    }
    pedge *h=head;
    pedge p=*h;
    if((*h)->weight==70){
        printf("debug\n");
    }
    if((*h)->endpoint==curr){
        *h=p->next;
        free(p);
        return;
    }
    while((*h)->next){
        if((*h)->next->endpoint==curr){
            if((*h)->next->next==NULL){
                p=(*h)->next;
                (*h)->next=NULL;
                free(p);
                return;
            }
            *h=p->next;
            free(p);
            return;
        }
        p=*h;
        h=&((*h)->next);
    }
}
/*
 * PrintGraph_cmd for self debug
 * Self Debug
 */
void printGraph_cmd(pnode head){
    printf("printGraph_cmd\n");
    if(head == (pnode) NULL){
        return;
    }
    pnode current_node = head;
    pedge current_edge;
    int count=0;
    printf("Starting to Print!\n");
    while(current_node != (pnode) NULL){
        printf("current node: %d\n", (current_node)->node_num);
        current_edge = current_node->edges;
        while(current_edge != (pedge)NULL){
            printf("edge %d", count++);
            printf(" dest: %d, w: %d \n", current_edge->endpoint->node_num, current_edge->weight);
            current_edge = current_edge->next;
        }
        count = 0;
        current_node = (current_node)->next;
    }
}
/*
 * delete all edges then delete nodes
 */
void deleteGraph_cmd(pnode* head){
    pnode *h=head;
    while((*h)){
        delete_edges(h);
        h=&((*h)->next);
    }
    h=head;
    delete_all_node(head);
    printf("\n-----------DELETED GRAPHH---------\n");
}
/*
 * TO DO
 */
void shortsPath_cmd(pnode head){
    printf("\n-------SHORT PATH-------\n");
    int src,dest;
    scanf("%d",&src);
    scanf("%d",&dest);
    printf("distance from src %d to dest %d ",src,dest);
    pnode *h=head;
    int id=0;
    while((*h)){
        (*h)->index=id;
        if(src==(*h)->node_num){
            src=id;
        }else if(dest==(*h)->node_num){
            dest=id;
        }
        h=&((*h)->next);
        id++;
    }
    h=head;
}
/*
 * TO DO
 */
void TSP_cmd(pnode head){
    printf("\n-------TSP-------\n");
    int k=-1;
    scanf("%d",&k);
    int t[]={INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN};
    for (int i = 0; i < k; ++i) {
        scanf("%d",t[i]);
    }
    pnode *h=head;
    int id=0;
    while((*h)){
        (*h)->index=id;
        for (int i = 0; i < k; ++i) {
            if(t[i]==(*h)->node_num){
                t[i]=id;
            }
        }
        h=&((*h)->next);
        id++;
    }
    int size=id;
    int *adj_mat= adjancy_matrix(head,size);
    h=head;
    int ans= dijkstra()
}
int * adjancy_matrix(pnode *head,int size){
    int *adj_mat= malloc((size*size)*sizeof (int));
    pnode *h=head;
    while ((*h)){
        pedge *p=&((*h)->edges);
        int id=(*h)->index;
        while((*p)){
            int dest=(*p)->endpoint->index;
            int w=(*p)->weight;
            adj_mat[id*size + dest]=w;
            p=&((*p)->next);
        }
        h=&((*h)->next);
    }
    return adj_mat;
}
pnode get_node_by_id(pnode *head,int id){
    pnode *h=head;
    while (*h){
        if((*h)->index==id) {
            printf("\nfound node %d\n", (*h)->index);
            return *h;
        }
        h=&((*h)->next);
    }
    printf("no such node %d\n",id);
    return NULL;
}

int dijkstra(int *adj_mat,int size,int src,int dest){

}