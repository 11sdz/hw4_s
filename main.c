#include<stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include "graph.h"

typedef enum bool {
    True=1,
    False=0
}bool;


int main(){
    char func = 'Z';
    pnode *head = malloc(sizeof(pnode));
    if(!head){
        printf("Malloc error");
        exit(1);
    }
    *head=NULL;
    while(func!=EOF){
        func=getchar();
        if(func=='A'){
            if(*head){
                deleteGraph_cmd(head);
            }
            build_graph_cmd(head);
        }if (func=='B'){
            insert_node_cmd(head);
        }if (func=='D'){
            delete_node_cmd(head);
        }if (func=='T'){
            TSP_cmd(head);
        }if (func=='S'){
            shortsPath_cmd(head);
        }if (func=='Q'){
            /*
             * DEBUG
             */
            printf("\n------------PRINT GRAPH----------\n");
            printGraph_cmd(*head);
        }
    }
    deleteGraph_cmd(head);
    free(head);
}