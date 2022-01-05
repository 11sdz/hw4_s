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
void adjancy_matrix(pnode *head,int size,int *adj_mat);
int minimum_permutation(int* floyd_warshall,int size,int *tsp, int k,int fac);
void dijkstra(int *adj_mat,int *distance,int size,int src);
int minimum_distance(int *distance,bool *vis,int size);
void print_dist(int *dist ,int src, int size);
void print_adj(int *adj_mat, int size);
void relax(int *distance , int *adj_mat, bool *vis, int size ,int vm);
void swaper(int *perm , int l , int i);
void print_perm(int* perm, int k);
void print_tsp(int *t, int size);
/*-----------------------------------------------------
 * -------------------Building Graph-------------------
 * ----------------------------------------------------
 */
void build_graph_cmd(pnode *head){
    int num=0;
    pnode *h=head;
    scanf("%d",&num);
    for (int i = 0; i < num; ++i) {
        insert_last_node(i,head);
    }
    int dest ,weight , id;
    for (int i = 0; i < num; ++i) {
        h=head;
        char c='\n';
        while((c=getchar())!='n');
        if(c=='n') {
            scanf("%d", &id);
        }
        while(scanf("%d",&dest) && scanf("%d",&weight)){
            insert_last_edge(h,id, dest,weight);
        }
    }
}
/*-----------------------------------------------------
 * --------------get node with index id----------------
 */
pnode get_node(pnode head,int node_num){
    while (head){
        if((head->node_num)==node_num) {
            return head;
        }
        head=head->next;
    }
    return NULL;
}
/*------------------------------------
 * ----------------creating new Node
 * -------------------------with id
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
/*----------------------------------
 * insert new node to last of linked list
 */
void insert_last_node(int id,pnode *head){
    pnode *h=head;
    while(*h){
        h= &((*h)->next);
    }
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
/*-----------------------------------
 * add node with id from user
 * TO DO CHECK IF WORKING
 */
void insert_node_cmd(pnode *head){
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
/*
 * delete all nodes
 */
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
/*-----------------------------------
 * --------delete node-----------------
 * input node num= id--------------------
 * delete id EDITTTTTT
 */
void delete_node_cmd(pnode *head){
    int id;
    scanf("%d",&id);
    pnode curr= get_node(*head,id);
    delete_edges(&curr);
    pnode *h=head;
    while(*h){
        if((*h)!=curr) {
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
/*----------------------------------------------------------------------
 * ------------delete all edges endpoint to curr----------------------
 */
void delete_edges_to(pedge *head,pnode curr){
    if(!*head){
        return;
    }
    pedge *h=head;
    pedge p=*h;
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
/*-----------------------------------
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
}
/*---------------------------------------------------
 * ------------------find short path------------------
 * -----------------using dijkstra-------------------
 */
void shortsPath_cmd(pnode *head){
    int src,dest;
    scanf("%d",&src);
    scanf("%d",&dest);
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
    int size=id;
    int *adj_mat=malloc(size*size*sizeof(int));
    if(!adj_mat){
        printf("MALLOC ERROR");
        exit(1);
    }
    adjancy_matrix(head,size,adj_mat);
    int *distance= malloc(size*sizeof(int));
    if(!distance){
        printf("MALLOC ERROR");
        exit(1);
    }
    dijkstra(adj_mat,distance,size,src);
    int dist=distance[dest];
    if(dist==INT_MAX){
        dist=-1;
    }
    printf("Dijsktra shortest path: %d\n",distance[dest]);
    free(adj_mat);
    free(distance);

}
/*-------------------------------------------------------------------------------------
 * -------------TSP running dijkstra n times and calculating permutations taking the min
 */
void TSP_cmd(pnode *head){
    int k=-1;
    scanf("%d",&k);
    int *t = malloc(sizeof(int)*6);
    int factorial=1;
    for (int i = 0; i < 6; i++) {
        if(i<k) {
            scanf("%d", &t[i]);
            factorial = factorial * (i + 1);
        } else{
            t[i]=INT_MIN;
        }
    }
    pnode *h=head;
    int id=0;
    while((*h)){
        (*h)->index=id;
        for (int i = 0; i < k; i++) {
            if(t[i]==(*h)->node_num){
                t[i]=id;
            }
        }
        h=&((*h)->next);
        id++;
    }
    int size=id;
    int *adj_mat=malloc(size*size*sizeof(int));
    if(!adj_mat){
        printf("MALLOC ERROR");
        exit(1);
    }
    adjancy_matrix(head,size,adj_mat);
    h=head;
    int min = INT_MAX;
    int *distance = malloc(size * sizeof(int));
    if(!distance){
        printf("MALLOC ERROR");
        exit(1);
    }
    int *floyd_warshall = malloc(size * size * sizeof(int));
    if(!floyd_warshall){
        printf("MALLOC ERROR");
        exit(1);
    }
    for (int i = 0; i < size; ++i) {
        dijkstra(adj_mat, distance, size, i);
        for (int j = 0; j < size; ++j) {
            floyd_warshall[j * size + i] = distance[j];
        }
    }
    min = minimum_permutation(floyd_warshall, size, t, k, factorial);
    free(floyd_warshall);
    free(adj_mat);
    free(distance);
    free(t);
    if(min==INT_MAX){
        min=-1;
    }
    printf("TSP shortest path: %d\n",min);
}
/*
 * DEBUG
 */
void print_tsp(int *t, int size){
    for (int i = 0; i <size ; ++i) {
        printf(" %d ",t[i]);
    }
    printf("\n");
}

int minimum_permutation(int* floyd_warshall,int size,int *tsp, int k,int fac){
    int min=INT_MAX;
    int *perm= malloc(sizeof(int)*k);
    if(!perm){
        printf("MALLOC ERROR");
        exit(1);
    }
    for (int i = 0; i <k ; ++i) {
        perm[i]=tsp[i];
    }
    int *ind= malloc(sizeof(int)*k);
    if(!ind){
        printf("MALLOC ERROR");
        exit(1);
    }
    for (int i = 0; i < k; ++i) {
        ind[i]=0;
    }
    int val=0;
    for (int i = 0; i < k-1; ++i) {
        if(floyd_warshall[perm[i]*size+perm[i+1]]!=INT_MAX) {
            val = val + floyd_warshall[perm[i] * size + perm[i + 1]];
        }else{
            val=INT_MAX;
            break;
        }
    }
    min=(val<min) ? val : min;
    int i=0;
    while(i<k){
        val=0;
        if(ind[i]<i){
            int l= (i%2==0) ? 0 : ind[i];
            swaper(perm,l,i);
            for (int i = 0; i < k-1; ++i) {
                if(floyd_warshall[perm[i]*size+perm[i+1]]!=INT_MAX) {
                    val = val + floyd_warshall[perm[i] * size + perm[i + 1]];
                }else{
                    val=INT_MAX;
                    break;
                }
            }
            min=(val<min) ? val : min;
            ind[i]++;
            i=0;
        }else{
            ind[i]=0;
            i++;
        }
    }
    free(ind);
    free(perm);
    return min;
}
void swaper(int *perm , int l , int i){
    int temp=perm[l];
    perm[l]=perm[i];
    perm[i]=temp;
}
void print_perm(int* perm, int k){
    for (int i = 0; i <k ; ++i) {
        printf(" %d , ",perm[i]);
    }
    printf("\n");
}

void adjancy_matrix(pnode *head,int size,int *adj_mat){
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(i!=j) {
                adj_mat[i * size + j] = INT_MAX;
            }else{
                adj_mat[i * size + i] = 0;
            }
        }
    }
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
}
/*
 * get node by id
 */
pnode get_node_by_id(pnode *head,int id){
    pnode *h=head;
    while (*h){
        if((*h)->index==id) {
            return *h;
        }
        h=&((*h)->next);
    }
    return NULL;
}
/*
 * DEBUG PRINT ADJANCY MATRIX
 *
 */
void print_adj(int *adj_mat, int size){
    printf("\n--------TEST ADJANCY MATRIX---------\n");
    for (int i = 0; i < size ; ++i) {
        for (int j = 0; j < size ; ++j) {
            printf(", %d ",adj_mat[j*size+i]);
        }
        printf("\n");
    }
}
/*
 * debug print distance
 */
void print_dist(int *dist ,int src, int size){
    for (int i = 0; i < size ; ++i) {
        int d=dist[i];
        printf("\n %d to %d weight is = %d",src,i,d);
    }
    printf("\n");
}
/*
 * dijkstra algo
 */
void dijkstra(int *adj_mat,int* distance,int size,int src){
    printf("\n");
    bool *vis= malloc(size*sizeof(bool));
    if(!vis){
        printf("MALLOC ERROR");
        exit(1);
    }
    for (int i = 0; i < size; i++) {
        distance[i]=INT_MAX;
        vis[i]=False;
    }
    distance[src]=0;
    for (int i = 0; i < size ; i++) {
        int vm =minimum_distance(distance, vis, size);
        vis[vm]=True;
        relax(distance,adj_mat,vis,size,vm);
    }
    free(vis);
}

void relax(int *distance , int *adj_mat, bool *vis, int size ,int vm){
    for (int i = 0; i < size; i++) {
         if(!vis[i]){
             if(distance[vm]!=INT_MAX && adj_mat[vm*size+i]!=INT_MAX)
                 if(distance[i]>distance[vm]+adj_mat[vm*size+i]){
                    distance[i]=distance[vm]+adj_mat[vm*size+i];
             }
         }
    }
}

int minimum_distance(int *distance,bool *vis,int size){
    int min = INT_MAX;
    int min_id;
    for (int i = 0; i < size; i++) {
        if ((!vis[i]) && (distance[i] < min))
            min = distance[i], min_id = i;
    }
    return min_id;
}

