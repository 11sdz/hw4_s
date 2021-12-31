#include<stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include "graph.h"


typedef enum bool {
    True=1,
    False=0
}bool;


pnode new_node(pnode next, int i);
pedge new_edge(pedge next,pnode dest,int weight);
pnode get_node(pnode head,int id);
void insert_last_node(int id,pnode *head);
void insert_last_edge(pnode *curr, int source,int dest,int weight);
void delete_edges(pnode head);

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

pnode get_node(pnode head,int id){
    while (head){
        if((head->node_num)==id) {
            printf("\nfound node %d\n", head->node_num);
            return head;
        }
        head=head->next;
    }
    printf("no such node %d\n",id);
    return NULL;
}

pnode new_node(pnode next,int id){
    pnode p =(pnode) malloc(sizeof(node));
    p->node_num=id;
    p->next=next;
    return p;
}

void insert_last_node(int id,pnode *head){
    pnode *h=head;
    while(*h){
        h= &((*h)->next);
    }
    printf("new node= %d , ",id);
    *h= new_node(NULL,id);
}

void insert_last_edge(pnode *curr, int source,int dest,int weight){
    pnode pnsource = get_node(*curr,source);
    pnode pndest = get_node(*curr,dest);
    pedge *h=&(pnsource->edges);
    while(*h){
        h= &((*h)->next);
    }
    printf("new edge from  %d to %d ,  ",pnsource->node_num,pndest->node_num);
    *h= new_edge(NULL,pndest,weight);
}

pedge new_edge(pedge next,pnode dest,int weight){
    pedge p =(pedge) malloc(sizeof(edge));
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
        delete_edges(curr);
    }else{
        insert_last_node(id,head);
    }
    while (scanf("%d",&dest) && scanf("%d",&weight)){
        insert_last_edge(head,id,dest,weight);
    }
}

void delete_edges(pnode head){
    pedge *h=&(head->edges);
    if(!*h) return;
    pedge p=*h;
    while(*h){
        h=&((*h)->next);
        p=*h;
        free(p);
    }
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