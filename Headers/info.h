#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H

typedef struct List_Inform{
    int vertex;                 //!The number of the vertex in graph
    int weight;                 //!A weight of the edge
}s_body;

typedef struct LIST{
    s_body data;
    struct LIST* sublist;          //!Pointer to the sublist vertex in the adjacency list
    struct LIST* next;             //!Pointer to the next element in queue
}s_list;

//!readinfo.c
s_list * ReadConsoleData(s_list **);
s_list * ReadFileData(s_list**);

//!graph.c
s_list * InitGraphElement(void);
s_list * AddNewQueueElement(s_list **, int);
s_list * UpdateElement(s_list **, int, int, int);
void PrintList(s_list **);
void PrintSubList(const s_list*);
void DeleteVertix(s_list **, int);
void FreeGraphMemory(s_list **);
void FreeSubList(s_list **);

#endif //!GRAPH_INFO_H
