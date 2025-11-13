#ifndef GRAPH_H
#define GRAPH_H

#define INF 9999

// Structure to store the travel network
typedef struct {
    int numCities;      // current number of cities
    char **cityNames;   // list of city names (dynamic)
    int **adjMatrix;    // adjacency matrix (stores distances)
    int capacity;       // current allocated sizee
} Graph;

// Function declarations
void initGraph(Graph *g);
void freeGraph(Graph *g);
int addCity(Graph *g, char name[]);
int addRoute(Graph *g, char src[], char dest[], int distance);
void findAllPaths(Graph *g, const char *start, const char *end);
void displayGraph(Graph *g);
void shortestPath(Graph *g, char start[], char end[]);
void alternateRoutes(Graph *g, char start[], char end[]);
void handleConstraints(Graph *g, int maxDistance);
int getCityIndex(Graph *g, char name[]);

#endif