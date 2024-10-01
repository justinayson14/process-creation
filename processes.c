#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 5

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
        else {
            ptr = allPCB[i]->child;
            while(ptr != NULL) {
                printf("\tChild process: %d\n", ptr->childId);
                ptr = ptr->sibling;
            }// end while
        }// end else
    }// end for

    return;
}// end printProcessHierarchy

void initializeProcessHierarchy() {
    allPCB[0] = (PCB*)malloc(sizeof(PCB));
    allPCB[0]->parentId = -1;
    allPCB[0]->child = NULL;
    for(int i = 1; i < MAX_PROCESSES; i++) {
        allPCB[i] = NULL;
    }
    printProcessHierarchy();

    return;
}// end initializeProcessHierarchy

void createChild() {
    int p, q;
    
    printf("Enter the parent process id: ");
    scanf("%d", &p);
    while (getchar() != '\n');

    if (allPCB[p] == NULL) { 
        printf("\nERROR: Process does not exist. Try again.\n");
        return;
    }

    for(q = p+1; q <= MAX_PROCESSES; q++) {
        if(allPCB[q] == NULL)
            break;
    }
    if (q == MAX_PROCESSES) {
        printf("\nERROR: No PCB's are available. Try again.\n");
        return;
    }

    allPCB[q] = (PCB*)malloc(sizeof(PCB));
    allPCB[q]->parentId = p;
    allPCB[q]->child = NULL; 

    struct Child *temp = (struct Child*)malloc(sizeof(struct Child));
    temp->childId = q;
    temp->sibling = NULL;

    if (allPCB[p]->child == NULL)
        allPCB[p]->child = temp;
    else {
        struct Child *ptr = allPCB[p]->child;
        while(ptr->sibling != NULL)
            ptr = ptr->sibling;
        
        ptr->sibling = temp;
    }

    printProcessHierarchy();
    return;

}

int main(void) {

    char input;

    do {
        printf("\nPlease make your selection:\n");
        printf("=====================================\n");
        printf("1) Initialize process hierarchy\n");
        printf("2) Create a new child process\n");
        printf("3) Destroy all descendants of parent process\n");
        printf("4) Quit program and free memory\n\n");

        printf("Selection: ");
        input = getchar();
        while (getchar() != '\n');

        switch (input)
        {
        case '1':
            printf("\nInitializing process hierarchy...\n");
            initializeProcessHierarchy();
            break;
        case '2':
            printf("\nCreating new child process...\n");
            createChild();
            break;
        case '3':
            printf("\nDestroying all descendants of parent process...\n");
            break;
        case '4':
            printf("\nQuitting program and freeing memory...\n");
            break;
        default:
            printf("\nINVALID INPUT! Please re-enter input...\n");
            break;
        }
    } while (input != '4');

    return 1;
}//end main

