#include <stdio.h>
#include <stdlib.h>
#include "../Headers/info.h"

//!Initialize graph element(type: struct) in dynamic memory
//!Return: pointer to current struct
s_list * InitGraphElement(void)
{
    s_list *element = (s_list*)malloc(sizeof(s_list));
    return element;
}

//!Add new element in general queue
//!Parameters: pointer to the next available element in queue
//!Return: address of the created element
s_list * AddNewQueueElement(s_list ** pList, int vertex)
{
    if((*pList) == NULL)
    {
        s_list * temp = InitGraphElement();
        temp->data.vertex = vertex;
        return temp;
    }
    (*pList)->next = AddNewQueueElement(&(*pList)->next, vertex+1);
    return (*pList);
}

//!Update sublist of connected vertices for element in queue
//!Parameters: pointer to the next element in sublist, value of the vertex and edge
//!Return: pointer to the previous element in sublist
s_list * UpdateElement(s_list **pSubList, int index, int vertex, int edge)
{
    if(index != 0)
    {
        (*pSubList)->next = UpdateElement(&((*pSubList)->next), index-1, vertex, edge);      //!Switch to the next element in queue
    }else if((*pSubList) == NULL)                            //!If there isn't elements - create new one and init data
    {
        if(( (*pSubList) = InitGraphElement() ) == NULL)
            return NULL;                                //!If not enough memory - return NULL and finish program
        (*pSubList)->sublist = NULL;
        (*pSubList)->data.vertex = vertex;
        (*pSubList)->data.weight = edge;
        return *pSubList;
    }else
    {
        (*pSubList)->sublist = UpdateElement(&((*pSubList)->sublist), 0, vertex, edge);      //!Switch to the sublist element in queue
        if((*pSubList)->sublist == NULL)
            return NULL;
    }
    return (*pSubList);
}

//!Print all available vertices in queue and sublists
//!Parameters: pointer to the queue and a current vertex
void PrintList(s_list ** pList, int index)
{
    if( (*pList) == NULL)
        return;
    printf("%d => %d(%d)", index, (*pList)->data.vertex+1, (*pList)->data.weight);        //!Print data for current element
    PrintSubList((*pList)->sublist);                                                            //!Print sublist
    printf("\n");
    PrintList(&(*pList)->next, index +1);                   //!Switch to the next element
}

//!Print sublist for current vertix
//!Parameters: pointer to the element of the sublist
void PrintSubList(const s_list* sublist)
{
    if(sublist == NULL)
        return;
    printf(" %d(%d)", sublist->data.vertex+1, sublist->data.weight);
    PrintSubList(sublist->sublist);
}

//!Free dynamic memory for queue of the vertices and sublists
//!Parameters: pointer to the start of the queue
void FreeGraphMemory(s_list **pList)
{
    if(pList == NULL)
        return;
    FreeGraphMemory(&(*pList)->next);
    FreeSubList(&(*pList)->sublist);                        //!Delete sublist for current element
    free((*pList));                                         //!Delete element from queue
}

//!Free dynamic memory for sublist
//!Parameters: pointer to the sublist
void FreeSubList(s_list **sublist)
{
    if(sublist == NULL)
        return;
    FreeSubList(&(*sublist)->sublist);
    free((*sublist));
}