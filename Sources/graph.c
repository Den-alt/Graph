#include <stdio.h>
#include <stdlib.h>
#include "../Headers/info.h"

//!Initialize graph list element(type: struct) in dynamic memory
//!Return: pointer to current struct
s_list * InitGraphElement(void)
{
    s_list *element = (s_list*)malloc(sizeof(s_list));
    return element;
}
//!Add new element in general queue
//!Parameters: pointer to the next available element in queue and the number of vertex
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
//!Parameters: pointer to the next element in sublist, its number in the queue, value of the vertex and edge
//!Return: pointer to the previous element in sublist
s_list * UpdateElement(s_list **pSubList, int index, int vertex, int edge)
{
    if(index != 0)                      //!At first go through the list to the specified element
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
    }else                                               //!Then find the end of the sublist and update it
    {
        (*pSubList)->sublist = UpdateElement(&((*pSubList)->sublist), 0, vertex, edge);      //!Switch to the sublist element in queue
        if((*pSubList)->sublist == NULL)
            return NULL;
    }
    return (*pSubList);
}
//!Calc a number of vertices in graph
//!Parameters: the first vertix in graph(queue)
//!Return: a number of vertices
int CalcVertices(s_list * pList)
{
    static int counter;
    if(pList == NULL)
        return counter;
    counter++;
    return CalcVertices(pList->next);
}
//!Allocate dynamic memory for Hamiltonian cycle
//!Parameters: size of the array
//!Return: pointer to the array in dynamic memory
int * InitCycle(int size)
{
    int * array = (int*)malloc(size*sizeof(int));
    return array;
}
//!Find vertex in general queue by value
//!Parameters: next element in the list and a value of the vertex
//!Return: found element
s_list * FindElementByVertex(s_list *list, int vertex)
{
    if(list == NULL)
        return NULL;
    else if(vertex == list->data.vertex)
        return list;
    else
        return FindElementByVertex(list->next, vertex);
}
//!Check if exist an element in sublist for current vertex (found in function FindElementByVertex())
//!Parameters: next element in sublist for checking and a value of vertex
//!Return: found element or NULL if failed
s_list * CompareElement(s_list *sublist, int vertex)
{
    if(sublist == NULL)
        return NULL;
    if( vertex == sublist->data.vertex)
        return sublist;
    else
        return CompareElement(sublist->sublist, vertex);
}
//!Search a Hamiltonian cycle and calculation of the min length
//!Parameters: pointer to the graph with result, list and index of the checking element
void SearchHamiltonian(s_hamilton * pGraph, s_list * list, int index)
{
    static int * array;
    if(array == NULL)                                           //!Init an array for searching
    {
        array = (int*) malloc(pGraph->size*sizeof(int));
        if(array == NULL)
        {
            printf("Not enough memory for calculation\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < pGraph->size; ++i)                  //!Set default value (-1) in temporary array
            array[i] = -1;
        array[0] = pGraph->vertex;                              //!Start from user indicated vertex
    }
    while (1)
    {
        while (1)                                               //!Search the next possible vertex in cycle
        {
            array[index] = ( ( array[index] + 2 ) % (pGraph->size+1) ) - 1;         //![-1; pGraph->size value]
            if(array[index] == -1)                                                  //!If all vertex checked, exit from "while"
                break;
            if(CompareElement(FindElementByVertex(list, array[index - 1]), array[index]) != NULL)       //!Check if current vertex has an edge between previous
            {
                int i = 0;
                for (; i < index; ++i)
                {
                    if(array[i] == array[index])            //!To avoid repeating elements
                        break;
                }
                if(i == index)                              //!If none of element repeat
                    if( (index < pGraph->size-1) || (index == pGraph->size-1) && (CompareElement(FindElementByVertex(list, array[pGraph->size - 1]), array[0]) != NULL ))
                        break;
            }
        }
        if(array[index] == -1)                           //!If none of vertex can't be added in array return to prev element in array
            return;
        if(index == pGraph->size - 1)                   //!If array is completely filled
        {
            int sum = 0;
            for (int i = 1; i < pGraph->size; ++i)     //!Calc a sum of the array
            {
                s_list *element = CompareElement(FindElementByVertex(list, array[i - 1]), array[i]);
                sum += element->data.weight;
            }
            if(sum < pGraph->min || pGraph->min == 0)       //!If current sum < min update a result graph
            {
                pGraph->min = sum;
                for (int i = 0; i < pGraph->size; ++i)
                    pGraph->cycle[i] = array[i];
            }
        }
        else
            SearchHamiltonian(pGraph, list, index+1);
    }
}
//!Print all available vertices in queue and sublists
//!Parameters: pointer to the queue
void PrintList(s_list * pList)
{
    if( pList == NULL)
        return;
    //!Print data for current element
    printf("%d => %d(%d)", pList->data.vertex+1, pList->data.vertex+1, pList->data.weight);
    PrintSubList(pList->sublist);              //!Print sublist
    printf("\n");
    PrintList(pList->next);                   //!Switch to the next element
}
//!Print sublist for current vertix
//!Parameters: const pointer to the element of the sublist
void PrintSubList(const s_list* sublist)
{
    if(sublist == NULL)
        return;
    printf(" %d(%d)", sublist->data.vertex+1, sublist->data.weight);
    PrintSubList(sublist->sublist);
}
//!Free dynamic memory for queue of the vertices and sublists
//!Parameters: pointer to the start of the queue
void FreeListMemory(s_list ** pList)
{
    if(*pList == NULL)
        return;
    FreeListMemory(&(*pList)->next);
    FreeSubList(&(*pList)->sublist);                        //!Delete sublist for current element
    free((*pList));                                         //!Delete element from queue
}
//!Free dynamic memory for sublist
//!Parameters: pointer to the sublist
void FreeSubList(s_list **sublist)
{
    if(*sublist == NULL)
        return;
    FreeSubList(&(*sublist)->sublist);
    free((*sublist));
}