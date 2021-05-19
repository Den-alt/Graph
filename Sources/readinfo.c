#include <stdio.h>
#include <ctype.h>
#include "../Headers/info.h"
#define STRING 300

FILE *UserFile;                             //!Pointer to the stream of the user file

//!Read data from console
//!Parameters: Pointer to the queue of adjacency lists
//!Return: address of the queue if read or NULL if failed
s_list * ReadConsoleData(s_list ** pList)
{
    s_list* isNull;
    int value = 0, vertex, edge, index = 0, isVertex = 1;
    printf("\nCreate adjacency lists\nTo init a new line press \"0\".\nTo exit - press any not number symbol."
           "\n<Remember that you must enter all associated vertices for each vertex>\n");
    do {
        if(value == 0)                                            //!The end of line
        {
            index++;
            isNull = AddNewQueueElement(pList, 0);                   //!Switch(create) to the sublist
            if(isNull == NULL)                                      //!If sublist hasn't been created
            {
                FreeListMemory(pList);
                return NULL;
            }
            pList = &isNull;
            PrintList(pList);
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
                FreeListMemory(pList);
                return NULL;
            }
            pList = &isNull;
        }
        printf("Enter the value of the %s for %d sublist:\n", isVertex == 1 ? "vertex" : "edge", index);
    } while (scanf("%d", &value));          //!The end of data
    return *pList;
}

//!Read data from user file
//!Parameters: Pointer to the queue of adjacency lists
//!Return: address of the queue if read or NULL if failed
s_list * ReadFileData(s_list** pList)
{
    s_list* isNull;
    int value = 0, symbol, vertex, edge, index = 0, isVertex = 1;
    char path[STRING];
    printf("Enter the path to your file:\n");
    scanf("%s", path);
    printf("Opening file...\n");
    UserFile = fopen(path, "r");
    if(UserFile == NULL)
    {
        printf("File not found\n");
        return NULL;
    }
    printf("Reading data from file...\n");
    do {
        if(value == 0)                                              //!The end of line
        {
            index++;
            isNull = AddNewQueueElement(pList, 0);                   //!Switch(create) to the sublist
            if(isNull == NULL)                                      //!If sublist hasn't been created
            {
                FreeListMemory(pList);
                return NULL;
            }
            pList = &isNull;
        }else if(isVertex == 1)                                  //!Firstly save value of vertex
        {
            isVertex = !isVertex;
            vertex = value;
        }else                                               //!Get value of edge and update current sublist
        {
            isVertex = !isVertex;
            edge = value;
            isNull = UpdateElement(pList, index-1, vertex-1, edge);              //!Set data in adjacency list
            if(isNull == NULL)                                         //!If new element in sublist can't be added
            {
                FreeListMemory(pList);
                return NULL;
            }
            pList = &isNull;
        }
        value = 0;
        while(1)
        {
            symbol = fgetc(UserFile);
            if(feof(UserFile))
            {
                fclose(UserFile);                   //!Close file stream
                return *pList;
            }
            if(isdigit(symbol))
                value = value * 10 + (symbol - 48);     //!Formula of creating a number
            else
            {
                if(value != 0)
                    break;                              //!Save read value
                if(symbol == '\n')
                {
                    value = 0;                          //!For creating new element in queue
                    break;
                }
            }
        }
    }while (1);
}