#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    struct Pcb* parent;
    struct Pcb* child;

} Pcb;

int main(void) {

    char input;

    do {
        printf("\nPlease make your selection:\n");
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


    return 0;
}

