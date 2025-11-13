#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() 
{
    Graph g;
    initGraph(&g);

    int choice, distance, limit, count;
    char src[50], dest[50], name[50];
    char again;

    while (1) 
{
    printf("\n=============================\n");
    printf("   TRAVEL PLANNER MENU  \n");
    printf("=============================\n");
    printf("1. Add City\n");
    printf("2. Add Route between Cities\n");
    printf("3. Find Possible Traversal Paths (DFS)\n"); 
    printf("4. Display Travel Map\n");
    printf("5. Find Shortest Path\n");
    printf("6. Suggest Alternate Routes\n");
    printf("7. Show Routes within Distance Limit\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            do 
            {
                printf("Enter city name: ");
                scanf("%s", name);
                addCity(&g, name);
                printf("Do you want to add another city? (y/n): ");
                scanf(" %c", &again);
            }
            while (again == 'y' || again == 'Y');
            break;

        case 2:
            do 
            {
                printf("Enter source city name: ");
                scanf("%s", src);
                printf("Enter destination city name: ");
                scanf("%s", dest);
                printf("Enter distance between them: ");
                scanf("%d", &distance);
                addRoute(&g, src, dest, distance);
                printf("Do you want to add another route? (y/n): ");
                scanf(" %c", &again);
            } 
            while (again == 'Y' || again == 'y');
            break;

        case 3:
            printf("Enter start city: ");
            scanf("%s", src);
            printf("Enter destination city: ");
            scanf("%s", dest);
            findAllPaths(&g, src, dest);
            break;

        case 4:
            displayGraph(&g);
            break;

        case 5:
            printf("Enter start city: ");
            scanf("%s", src);
            printf("Enter end city: ");
            scanf("%s", dest);
            shortestPath(&g, src, dest);
            break;

        case 6:
            printf("Enter start city: ");
            scanf("%s", src);
            printf("Enter end city: ");
            scanf("%s", dest);
            alternateRoutes(&g, src, dest);
            break;

        case 7:
            printf("Enter max distance limit: ");
            scanf("%d", &limit);
            handleConstraints(&g, limit);
            break;

        case 8:
            printf("Exiting Travel Planner... Safe travels!\n");
            freeGraph(&g);
            exit(0);

        default:
            printf("Invalid choice! Please try again.\n");
    }
}


    return 0;
}