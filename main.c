#include <stdio.h>
#include "Headers/info.h"

int main()
{
    s_list *VertexList = NULL;             //!Dynamic queue of the first elements of the adjacency lists
    s_hamilton TSP;                        //!Result of calculation
    int input = 1, pivot = 0;
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
            return -1;
        }
    }
    else if(input == 2)
    {
        printf("You choose to enter the data from file\n");
        if((VertexList = ReadFileData(&VertexList)) != NULL)
        {
            printf("Data read successfully\n");
        } else
        {
            printf("Error! Failed to read data!\n");
            return -1;
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
            return -1;
        }
    }
    printf("Your adjacency list:\n");
    PrintList(VertexList);                                                 //!Print current adjacency list
    printf("Enter the pivot vertex: \n");                            //!Get value of the pivot vertex to find a Hamilton cycles
    scanf("%d", &pivot);
    TSP.vertex = pivot-1;
    TSP.min = 0;
    TSP.size = CalcVertices(VertexList);
    if( (TSP.cycle = InitCycle(TSP.size)) == NULL )
    {
        printf("Program failed\nNot enough memory\n");
        FreeListMemory(&VertexList);
        return -1;
    }
    SearchHamiltonian(&TSP, VertexList, 1);
    printf("The result = %d: vertices =>", TSP.min);
    for (int i = 0; i < TSP.size; ++i)
        printf(" %d", TSP.cycle[i]+1);
    printf("\n");
    FreeListMemory(&VertexList);
    getchar();
    return 0;
}
