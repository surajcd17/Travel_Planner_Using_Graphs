Topic : Travel Planner using Graphs -

This project is a simple Travel Planner built in C that uses Graph Data Structures to represent cities and routes between them. It allows users to add cities, connect them with routes, view all possible paths, find the shortest path using Dijkstra’s Algorithm, and visualize the overall travel network.



Files Included : 

1) main.c – Contains the main menu and handles user interaction.
2) graph.c – Implements all graph-related functionalities like adding cities, routes, DFS traversal, shortest path, etc.
3) graph.h – Header file containing function declarations and structure definitions.



How to Compile and Run :

1) Make sure you have a C compiler installed (like GCC).
2) Save all three files — main.c, graph.c, and graph.h — in the same folder.
3) Open your terminal or command prompt and navigate to that folder.
4) Compile the program using:
    gcc main.c graph.c -o travel_planner
5) Run the executable:
    ./travel_planner



Features : 

1) Add cities and routes interactively.
2) Display the entire travel map.
3) Find all possible paths between two cities using DFS.
4) Get the shortest route between cities (Dijkstra’s algorithm).
5) Suggest alternate connections and filter routes within a distance limit.
6) Fully dynamic memory allocation and cleanup.