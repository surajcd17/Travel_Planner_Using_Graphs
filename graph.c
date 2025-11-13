#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"

//basic case insensitive function 
int strCaseCompare(const char *a, const char *b)
{
    int i = 0;
    while (a[i] && b[i]) 
    {
        char c1 = tolower(a[i]);
        char c2 = tolower(b[i]);

        if (c1 != c2)
            return c1 - c2;
        i++;
    }
    return a[i] - b[i];
}

// FUNCTIONALITY 1: Represent cities and routes using a graph
void initGraph(Graph *g) 
{
    g->numCities = 0;
    g->capacity = 5; // start small, increase when needed
    g->cityNames = (char **)malloc(g->capacity * sizeof(char *));
    g->adjMatrix = (int **)malloc(g->capacity * sizeof(int *));
    for (int i = 0; i < g->capacity; i++) 
    {
        g->adjMatrix[i] = (int *)calloc(g->capacity, sizeof(int));
    }
}

// Returns the index of a city (used often)
int getCityIndex(Graph *g, char name[]) 
{
    for (int i = 0; i < g->numCities; i++) 
    {
        if (strCaseCompare(g->cityNames[i], name) == 0)
            return i;
    }
    return -1;
}

// Expands graph capacity when city limit is reached
void resizeGraph(Graph *g) 
{
    int newCap = g->capacity * 2;

    g->cityNames = realloc(g->cityNames, newCap * sizeof(char *));
    g->adjMatrix = realloc(g->adjMatrix, newCap * sizeof(int *));
    
    for (int i = 0; i < newCap; i++) 
    {
        if (i >= g->capacity)
            g->adjMatrix[i] = (int *)calloc(newCap, sizeof(int));
        else
            g->adjMatrix[i] = realloc(g->adjMatrix[i], newCap * sizeof(int));
    }
    g->capacity = newCap;
}

// Adds a new city into the graph
int addCity(Graph *g, char name[]) 
{
    if (getCityIndex(g, name) != -1) 
    {
        printf("City '%s' already exists!\n", name);
        return 0;
    }

    if (g->numCities >= g->capacity)
        resizeGraph(g);

    g->cityNames[g->numCities] = malloc(50 * sizeof(char));
    strcpy(g->cityNames[g->numCities], name);
    g->numCities++;

    printf("City '%s' added successfully.\n", name);
    return 1;
}

// FUNCTIONALITY 2: Add routes (edges) between two cities
int addRoute(Graph *g, char src[], char dest[], int distance) 
{
    int i = getCityIndex(g, src);
    int j = getCityIndex(g, dest);

    if (i == -1 || j == -1) 
    {
        printf("\n Source or destination city not entered yet.\n");
        printf("Please add both cities first using Option 1 before adding a route.\n\n");
        return 0;
    }
    if (i == j) 
    {
        printf("Cannot add a route from a city to itself.\n");
        return 0;
    }
    if (distance <= 0) 
    {
        printf("Distance must be positive.\n");
        return 0;
    }

    g->adjMatrix[i][j] = distance;
    g->adjMatrix[j][i] = distance; // undirected graph, A to B and B to A
    printf("Route added between %s and %s (Distance: %d)\n", src, dest, distance);
    return 1;
}


// FUNCTIONALITY 6: Visualize the travel graph
void displayGraph(Graph *g) 
{
    printf("\n========== TRAVEL MAP ==========\n");
    for (int i = 0; i < g->numCities; i++) 
    {
        printf("%s -> ", g->cityNames[i]);
        for (int j = 0; j < g->numCities; j++) 
        {
            if (g->adjMatrix[i][j] != 0)
                printf("%s(%d) ", g->cityNames[j], g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// FUNCTIONALITY 3: Find shortest path using Dijkstra’s algorithm
void shortestPath(Graph *g, char start[], char end[]) 
{
    int s = getCityIndex(g, start);
    int e = getCityIndex(g, end);
    if (s == -1 || e == -1) 
    {
        printf("Invalid city names.\n");
        return;
    }

    int *dist = malloc(g->numCities * sizeof(int));
    int *visited = malloc(g->numCities * sizeof(int));
    int *prev = malloc(g->numCities * sizeof(int));

    for (int i = 0; i < g->numCities; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }
    dist[s] = 0;

    for (int c = 0; c < g->numCities - 1; c++) 
    {
        int u = -1, min = INF;
        for (int i = 0; i < g->numCities; i++)
            if (!visited[i] && dist[i] < min) 
            {
                min = dist[i];
                u = i;
            }
        if (u == -1) break;

        visited[u] = 1;
        for (int v = 0; v < g->numCities; v++) 
        {
            if (g->adjMatrix[u][v] && dist[u] + g->adjMatrix[u][v] < dist[v]) 
            {
                dist[v] = dist[u] + g->adjMatrix[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[e] == INF) 
    {
        printf("No path found between %s and %s.\n", start, end);
    } 
    else 
    {
        printf("\nShortest path from %s to %s = %d\n", start, end, dist[e]);
        printf("Route: ");
        int path[g->numCities], count = 0, t = e;
        while (t != -1) 
        {
            path[count++] = t;
            t = prev[t];
        }
        for (int i = count - 1; i >= 0; i--)
            printf("%s ", g->cityNames[path[i]]);
        printf("\n");
    }

    free(dist);
    free(visited);
    free(prev);
}

// FUNCTIONALITY 4: Suggest alternate routes
void alternateRoutes(Graph *g, char start[], char end[]) 
{
    int s = getCityIndex(g, start);
    int e = getCityIndex(g, end);
    if (s == -1 || e == -1) 
    {
        printf("Invalid city names.\n");
        return;
    }

    printf("\nAlternate route suggestions:\n");
    int found = 0;
    for (int i = 0; i < g->numCities; i++) 
    {
        if (i != s && i != e && g->adjMatrix[s][i] && g->adjMatrix[i][e]) 
        {
            printf("%s -> %s -> %s\n", g->cityNames[s], g->cityNames[i], g->cityNames[e]);
            found = 1;
        }
    }
    if (!found)
        printf("No alternate routes found.\n");
}

// FUNCTIONALITY 5: Handle constraints (max distance filter)
void handleConstraints(Graph *g, int maxDistance) 
{
    printf("\nRoutes under %d distance:\n", maxDistance);
    for (int i = 0; i < g->numCities; i++) 
    {
        for (int j = i + 1; j < g->numCities; j++) 
        {
            if (g->adjMatrix[i][j] && g->adjMatrix[i][j] <= maxDistance)
                printf("%s -> %s (%d)\n", g->cityNames[i], g->cityNames[j], g->adjMatrix[i][j]);
        }
    }
}

// FUNCTIONALITY 2 (extension): Find all possible traversal paths between two cities using DFS
void dfsHelper(Graph *g, int current, int dest, int visited[], int path[], int pathIndex)
{
    visited[current] = 1;
    path[pathIndex] = current;
    pathIndex++;

    if (current == dest)
    {
        for (int i = 0; i < pathIndex; i++)
        {
            printf("%s", g->cityNames[path[i]]);
            if (i < pathIndex - 1)
                printf(" -> ");
        }
        printf("\n");
    }
    else
    {
        for (int i = 0; i < g->numCities; i++)
        {
            if (g->adjMatrix[current][i] && !visited[i])
                dfsHelper(g, i, dest, visited, path, pathIndex);
        }
    }

    visited[current] = 0; // backtrack
}

void findAllPaths(Graph *g, const char *start, const char *end)
{
    int s = getCityIndex(g, (char *)start);
    int e = getCityIndex(g, (char *)end);

    if (s == -1 || e == -1)
    {
        printf("Invalid city name(s).\n");
        return;
    }

    int *visited = (int *)calloc(g->numCities, sizeof(int));
    int *path = (int *)malloc(g->numCities * sizeof(int));

    printf("\nPossible traversal paths between %s and %s:\n", start, end);
    dfsHelper(g, s, e, visited, path, 0);

    free(visited);
    free(path);
}

// FUNCTIONALITY 6 (continue): Cleanup - free allocated memory
void freeGraph(Graph *g) 
{
    for (int i = 0; i < g->numCities; i++)
        free(g->cityNames[i]);
    free(g->cityNames);

    for (int i = 0; i < g->capacity; i++)
        free(g->adjMatrix[i]);
    free(g->adjMatrix);
}