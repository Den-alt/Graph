#include <stdio.h>
#include <time.h>
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
    if(CheckCondition(VertexList) != 0)                                     //!Check the Dirac's Theorem
    {
        printf("Condition false\n");
        FreeListMemory(&VertexList);
        return -1;
    }
    printf("Enter the pivot vertex: \n");                            //!Get value of the pivot vertex to find a Hamilton cycles
    if(input == 1)                                                          //!To avoid reading an enter symbol if read data from console
        getchar();
    scanf("%d", &pivot);
    TSP.vertex = pivot-1;
    TSP.min = 0;
    clock_t start = clock();
    TSP.size = CalcVertices(VertexList);
    if( (TSP.cycle = InitCycle(TSP.size)) == NULL )
    {
        printf("Program failed\nNot enough memory\n");
        FreeListMemory(&VertexList);
        return -1;
    }
    SearchHamiltonian(&TSP, VertexList, 1);
    if(TSP.min == 0)
        printf("Hamiltonian cycles don't exist\nTravelling Salesman Problem can't be solved\n");
    else
    {
        printf("The result = %d: vertices =>", TSP.min);
        for (int i = 0; i < TSP.size; ++i)
            printf(" %d", TSP.cycle[i]+1);
        printf("\n");

    }
    FreeListMemory(&VertexList);
    ClearGraph(&TSP);
    clock_t end = clock();
    printf("Time: %lf seconds\n", (double)(end - start) / CLOCKS_PER_SEC);
    getchar();
    return 0;
}
