#include <stdio.h>
#include "Headers/info.h"

int main()
{
    s_list *VertexList = NULL;             //!Dynamic queue of the first elements of the adjacency lists
    int input = 1;
    //!Get data
    printf("Enter the number of the input mode:\nConsole - 1\nFile - 2\nEnter: ");
    scanf("%d", &input);
    if(input == 1)
    {
        printf("You choose to enter the data from console\n");
        if( (VertexList = ReadConsoleData(&VertexList)) != NULL)
        {
            printf("Data read successfully\n");
        } else
        {
            printf("Error! Failed to read data!\n");
        }
    }else if(input == 2)
    {
        printf("You choose to enter the data from file\n");
        if((VertexList = ReadFileData(&VertexList)) != NULL)
        {
            printf("Data read successfully\n");
        } else
        {
            printf("Error! Failed to read data!\n");
        }
    }
    else
    {
        printf("Incorect value... Enter data from console");
        if((VertexList = ReadConsoleData(&VertexList)) != NULL)
        {
            printf("Data read successfully\n");
        } else
        {
            printf("Error! Failed to read data!\n");
        }
    }
    printf("Your adjacency list:\n");
    PrintList(&VertexList);                      //!Print current adjacency list
    FreeGraphMemory(&VertexList);
    return 0;
}
