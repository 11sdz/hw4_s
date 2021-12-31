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
void delete_edges(pnode *curr);
void delete_edges_to(pnode *head,pnode curr);
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
/*
 * creating new Node
 * with id
 */
pnode new_node(pnode next,int id){
    pnode p =(pnode) malloc(sizeof(node));
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

void delete_node_cmd(pnode *head){
    int id = scanf("%d",&id);
    pnode curr= get_node(*head,id);
    delete_edges(&curr);
    pnode *h=head;
    while(*h){
        if((*h)!=curr) {
            delete_edges_to(h, curr);
        }
        h= &((*h)->next);
    }
    pnode prev;
    while((*h)->next!=curr){
        h= &((*h)->next);
    }
    prev=(*h);
    prev->next=prev->next->next;
    free(curr);

}
void delete_edges_to(pnode *head,pnode curr){
    pnode *h=head;
    while(*h){
        h= &((*h)->next);
        if((*h)==curr){
            h= &((*h)->next);
        }
        pedge *pe=&((*h)->edges);
        while(*pe){
            pedge p=*pe;
            *pe=(*pe)->next;
            if(p->endpoint==curr){

            }
        }
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

void deleteGraph_cmd(pnode* head){

}
void shortsPath_cmd(pnode head){

}
void TSP_cmd(pnode head){

}