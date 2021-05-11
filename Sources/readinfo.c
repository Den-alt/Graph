#include <stdio.h>
#include "../Headers/info.h"

//!Read data from console
//!Parameters: Pointer to the array of adjacency lists
//!Return: number of sublists or -1 if failed
int ReadConsoleData(s_list ** pList)
{
    s_list* isNull;
    int value = 0, vertex, edge, index = 0, isVertex = 1;
    printf("\nCreate adjacency lists\nTo init a new line press \"0\".\nTo exit - press any not number symbol."
           "\n<Remember that you must enter all associated vertices for each vertex>\n");
    do {
        if(value == 0)                                            //!The end of line
        {
            index++;
            isNull = AddNewQueueElement(pList, 0);                   //!Switch(create) to the sublist sublist
            if(isNull == NULL)                                      //!If sublist hasn't been created
            {
                FreeGraphMemory(pList);
                return -1;
            }
            pList = &isNull;
            PrintList(pList, 1);
        }else if(isVertex == 1)                                  //!Firstly save value of vertex
        {
            isVertex = !isVertex;
            vertex = value;
        }else                                               //!Get value of edge and update current sublist
        {
            isVertex = !isVertex;
            edge = value;
            printf("Creating new element of sublist\n");
            isNull = UpdateElement(pList, index-1, vertex-1, edge);              //!Set data in adjacency list
            if(isNull == NULL)                                         //!If new element in sublist can't be added
            {
                FreeGraphMemory(pList);
                return -1;
            }
            pList = &isNull;
        }
        printf("Enter the value of the %s for %d sublist:\n", isVertex == 1 ? "vertex" : "edge", index);
    } while (scanf("%d", &value));          //!The end of data
    return 1;
}