# Travel Planner Using Graphs (C)

A menu-driven **Travel Planner** built in **C** that models cities and routes as a **graph** (undirected, weighted). It lets you build a travel network interactively, explore possible paths, and compute the shortest route between two cities.

## Features

- **Add cities** to the network (case-insensitive city matching)
- **Add routes** (edges) between cities with a **distance** (weight)
- **Display travel map** (adjacency list-style printout from an adjacency matrix)
- **Find all possible paths** between two cities using **DFS**
- **Find shortest path** between two cities using **Dijkstra’s algorithm**
- **Suggest alternate routes** (simple 2-hop suggestions: `start -> mid -> end`)
- **Filter routes by distance limit** (show all edges with distance ≤ limit)
- Uses **dynamic memory allocation** with cleanup on exit

## Project Structure

- `main.c` — CLI menu and user interaction
- `graph.h` — `Graph` struct + function declarations
- `graph.c` — Graph implementation (add city/route, DFS paths, Dijkstra shortest path, etc.)

## How It Works (High Level)

- Cities are stored in a dynamic array: `cityNames`
- Routes/distances are stored in an **adjacency matrix**: `adjMatrix`
- City lookup uses **case-insensitive** comparison
- Shortest path is computed using **Dijkstra** over the adjacency matrix

## Build & Run

### Prerequisites
- GCC (or any C compiler)

### Compile
```bash
gcc main.c graph.c -o travel_planner
```

### Run
```bash
./travel_planner
```

## Usage

After running, you’ll see a menu like:

- Add City  
- Add Route between Cities  
- Find Possible Traversal Paths (DFS)  
- Display Travel Map  
- Find Shortest Path (Dijkstra)  
- Suggest Alternate Routes  
- Show Routes within Distance Limit  
- Exit  

### Notes / Limitations

- City names are read using `scanf("%s", ...)`, so **spaces are not supported** (use `NewYork` instead of `New York`).
- “Alternate routes” are direct 2-step suggestions only (not k-shortest paths).
- This is an in-memory program (no file saving/loading yet).

## Example (Quick Demo)

1. Add cities: `A`, `B`, `C`
2. Add routes: `A-B (5)`, `B-C (6)`, `A-C (20)`
3. Shortest path from `A` to `C` will return `A -> B -> C` with total `11`
