// Fall 2024 COMP 322 
// Lab 1 - Process Creation Hierarchy
<<<<<<< HEAD
=======
// Justin Ayson
>>>>>>> 94e7c82bc938b18157140afeda5b0491de8aa990
/*
    Program prints 4 actions for user to pick from. 
        1. To initialize PCB hierarchy and creates first parent
        2. Creates child processes for parent by user input
        3. Destroy descendent processes of parent by user input
        4. Destroy all PCB and child processes. Quits program
*/


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
    for(int i = 0; i < MAX_PROCESSES; i++) {
        if (allPCB[i] == NULL)
            continue;

        printf("Process id: %d\n", i);

        if(allPCB[i]->parentId == -1)
            printf("\tNo parent process\n");
        else
            printf("\tParent process: %d\n", allPCB[i]->parentId);

        if(allPCB[i]->child == NULL)
            printf("\tNo child process\n");
        else {
            ptr = allPCB[i]->child;
            while(ptr != NULL) { // print all child of i (each child linked to its sibling)
                printf("\tChild process: %d\n", ptr->childId);
                ptr = ptr->sibling;
            }// end while
        }// end else
    }// end for

    return;
}// end printProcessHierarchy

void initializeProcessHierarchy() {
    // initialize first parent PCB
    allPCB[0] = (PCB*)malloc(sizeof(PCB));
    allPCB[0]->parentId = -1;
    allPCB[0]->child = NULL;

    // initialize other PCB as null
    for(int i = 1; i < MAX_PROCESSES; i++) {
        allPCB[i] = NULL;
    } // end for
    
    printProcessHierarchy();
    return;
}// end initializeProcessHierarchy

void createChild() {
    int p, q;
    
    printf("Enter the parent process id: ");
    scanf("%d", &p);
    while (getchar() != '\n');

    if (allPCB[p] == NULL) { 
        printf("\nERROR: Parent process does not exist. Try again.\n");
        return;
    }//end if

    // q starts 1 after parent (all PCBs stored in array)
    for(q = p+1; q <= MAX_PROCESSES; q++) {
        if(allPCB[q] == NULL)
            break;
    }// end for
    if (q == MAX_PROCESSES) {
        printf("\nERROR: No PCB's are available. Try again.\n");
        return;
    }// end for

    // initialize PCB[q]
    allPCB[q] = (PCB*)malloc(sizeof(PCB));
    allPCB[q]->parentId = p;
    allPCB[q]->child = NULL; 

    // initialize Child q
    struct Child *temp = (struct Child*)malloc(sizeof(struct Child));
    temp->childId = q;
    temp->sibling = NULL;

    // p no child, make q first child
    if (allPCB[p]->child == NULL)
        allPCB[p]->child = temp;
    else { // p has child, make q sibling of p's youngest child
        struct Child *ptr = allPCB[p]->child;
        while(ptr->sibling != NULL) // find youngest child
            ptr = ptr->sibling;
        
        ptr->sibling = temp;
    }// end else

    printProcessHierarchy();
    return;

}// end createChild

void destroyChildren(struct Child *ptr) {

    if (ptr == NULL) // if end of linkedlist, return
        return;
    else {
        destroyChildren(ptr->sibling); // recursive to next node
        int q = ptr->childId;
        destroyChildren(allPCB[q]->child); // recursive to child of current node
        free(allPCB[q]);
        allPCB[q] = NULL;
        free(ptr); // free Child struct of ptr
        ptr = NULL;
    }// end else
    
}// end destroyChildren

void destroyDescendents() {
    int p;

    printf("Enter parent process whose descendents are to be destroyed: ");
    scanf("%d", &p);
    while (getchar() != '\n');

    destroyChildren(allPCB[p]->child);
    allPCB[p]->child = NULL; // reset children of PCB[p] to null
    
    printProcessHierarchy();
    return;
}// end destroyDescendents

void destroyAllPCB() {
    if (allPCB[0] != NULL) {
        if (allPCB[0]->child != NULL)
            destroyChildren(allPCB[0]->child);
        for(int i = 0; i < MAX_PROCESSES && allPCB[i] != NULL; i++)
            free(allPCB[i]);
    }
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
        while (getchar() != '\n'); // clear input buffer

        switch (input)
        {
        case '1':
            printf("Initializing process hierarchy...\n");
            initializeProcessHierarchy();
            break;
        case '2':
            printf("Creating new child process...\n");
            createChild();
            break;
        case '3':
            printf("Destroying all descendants of parent process...\n");
            destroyDescendents();
            break;
        case '4':
            printf("Quitting program and freeing memory...\n");
            destroyAllPCB();
            break;
        default:
            printf("INVALID INPUT! Please re-enter input...\n");
            break;
        }// end switch
    } while (input != '4'); // end do while

    return 1;
}//end main

