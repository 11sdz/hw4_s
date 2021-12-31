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
    while(func!= EOF){
        func=getchar();
        if(func='A'){
            if(head){
                deleteGraph_cmd(head);
            }
            build_graph_cmd(head);
        }else if (func='B'){
            insert_node_cmd(head);
        }else if (func='D'){
            deleteGraph_cmd(head);
        }else if (func='T'){
            TSP_cmd(head);
        }else if (func='S'){
            shortsPath_cmd(head);
        }else{
            printGraph_cmd(head);
        }
    }
}