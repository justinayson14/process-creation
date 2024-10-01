#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

struct Child{
    int childId;
    struct Child* sibling;
};//end Child
typedef struct {
    int parentId;
    struct Child* child;

} PCB; //end PCB

PCB *allPCB[MAX_PROCESSES];

void printProcessHierarchy() {
   struct Child *ptr;

    printf("\nProcess list:\n");
    for(int i = 0; i < MAX_PROCESSES && allPCB[i] != NULL; i++) {
        printf("Process id: %d\n", i);

        if(allPCB[i]->parentId == -1)
            printf("\tNo parent process\n");
        else
            printf("\tParent process: %d\n", allPCB[i]->parentId);

        if(allPCB[i]->child == NULL)
            printf("\tNo child process\n");
        else
            ptr = allPCB[i]->child;
            while(ptr != NULL) {
                printf("\tChild process: %d\n", ptr->childId);
                ptr = ptr->sibling;
            }

    }
}// end printProcessHierarchy

void initializeProcessHierarchy() {
    allPCB[0] = (PCB*)malloc(sizeof(PCB));
    allPCB[0]->parentId = -1;
    allPCB[0]->child = NULL;
    for(int i = 1; i < MAX_PROCESSES; i++) {
        allPCB[i] = NULL;
    }
    printProcessHierarchy();

}// end initializeProcessHierarchy


int main(void) {

    char input;

    do {
        printf("\nPlease make your selection:\n");
        printf("=====================================\n");
        printf("1) Initialize process hierarchy\n");
        printf("2) Create a new child process\n");
        printf("3) Destroy all descendants of parent process\n");
        printf("4) Quit program and free memory\n\n");

        printf("Input: ");
        input = getchar();
        while (getchar() != '\n');

        switch (input)
        {
        case '1':
            printf("Initializing process hierarchy...\n");
            initializeProcessHierarchy();
            break;
        case '2':
            printf("Creating new child process...\n");
            break;
        case '3':
            printf("Destroying all descendants of parent process...\n");
            break;
        case '4':
            printf("Quitting program and freeing memory...\n");
            break;
        default:
            printf("INVALID INPUT! Please re-enter input...\n");
            break;
        }
    } while (input != '4');

    return 1;
}//end main

