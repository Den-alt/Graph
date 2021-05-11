#include <stdio.h>
#include "Headers/info.h"

int main()
{
    s_list *VertexList = NULL;             //!Dynamic queue of the first elements of the adjacency lists
    int check = 1;
    //!Get data
    printf("Enter the number of the input mode:\nConsole - 1\nFile - 2\nEnter: ");
    scanf("%d", &check);
    /*VertexList = InitGraphElement();                   //!Allocate memory for graph
    if(VertexList == NULL)
    {
        printf("Not enough memory for graph\n");
        return 0;
    }*/
    if(check == 1)
    {
        printf("You choose to enter the data from console\n");
        if(ReadConsoleData(&VertexList) == 1)
        {
            printf("Data read successfully\n");
        } else
        {
            printf("Error! Failed to read data!\n");
        }
    }else if(check == 2)
    {
        printf("You choose to enter the data from file\n");
    }
    else
    {
        printf("Incorect value... Enter data from console");
        if(ReadConsoleData(&VertexList) == 1)
        {
            printf("Data read successfully\n");
        } else
        {
            printf("Error! Failed to read data!\n");
        }
    }
    return 0;
}
