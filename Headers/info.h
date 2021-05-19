#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

//!The path to demo file: ../inputdata.txt

typedef struct List_Inform{
    int vertex;                 //!The number of the vertex in graph
    int weight;                 //!A weight of the edge
}s_body;

typedef struct LIST{
    s_body data;
    struct LIST* sublist;          //!Pointer to the sublist vertex in the adjacency list
    struct LIST* next;             //!Pointer to the next element in queue
}s_list;

typedef struct GRAPH{
    int vertex;                     //!Current vertex
    int min;                        //!A weight of edge between parent and this
    int size;                       //!Number of the needed elements in Hamiltonian cycle
    int *cycle;                     //!Array of the elements in Hamiltonian path
}s_hamilton;

//!readinfo.c
s_list * ReadConsoleData(s_list **);
s_list * ReadFileData(s_list**);

//!graph.c
s_list * InitGraphElement(void);
s_list * AddNewQueueElement(s_list **, int);
s_list * UpdateElement(s_list **, int, int, int);
int CalcVertices(s_list *);
int * InitCycle(int );
s_list * FindElementByVertex(s_list *, int );
s_list * CompareElement(s_list *, int );
void SearchHamiltonian(s_hamilton * , s_list * , int );
void PrintList(s_list *);
void PrintSubList(const s_list*);
void FreeListMemory(s_list **);
void FreeSubList(s_list **);

#endif //!GRAPH_INFO_H
