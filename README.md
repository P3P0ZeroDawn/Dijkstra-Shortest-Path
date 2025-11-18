# Dijkstra Shortest Path Program in C++

## Overview

This project implements a console-based graph management system in C++
capable of constructing graphs and calculating the shortest path between
two vertices using **Dijkstra's Algorithm**.\
The program allows users to add vertices, create weighted edges, display
graph information, and compute the shortest path interactively.

The graph is implemented using manually created linked lists for both
vertices and edges, providing full control over the data structure and
algorithmic execution.

------------------------------------------------------------------------

## Features

### Graph Management

1.  **Add Vertices**
    -   Users can insert labeled vertices.
    -   Vertices are stored as nodes in a linked list.
2.  **Add Edges**
    -   Allows creation of weighted edges between two existing vertices.
    -   Supports undirected graph structure.
    -   Weights are integer values.
3.  **Display Vertices**
    -   Prints all vertex labels currently stored in the graph.
4.  **Display Edges**
    -   Shows all edges with the following format:\
        `VERTEX1 --- WEIGHT --- VERTEX2`

### Dijkstra's Shortest Path Algorithm

-   Computes the shortest path between a selected origin and
    destination.
-   Uses temporary and permanent labels to evaluate paths.
-   Updates vertex labels dynamically based on the cumulative weight.
-   Outputs the shortest route in sequence, e.g.:\
    `A -> C -> F -> H`

------------------------------------------------------------------------

## How to Run the Program

1.  Make sure you have a **C++ compiler** such as GCC or MinGW.
2.  Save the code as `main.cpp` or any desired filename.
3.  Compile the program:

``` bash
g++ main.cpp -o dijkstra
```

4.  Run the executable:

``` bash
./dijkstra
```

### Menu Options

1.  Add a vertex\
2.  Add an edge\
3.  Display vertices\
4.  Display edges\
5.  Execute Dijkstra's shortest path algorithm\
6.  Exit the program

------------------------------------------------------------------------

## Technical Details

### Data Structures

1.  **Vertices (`Vertice`)**
    -   Contains:
        -   Label (`etiqueta`)
        -   Pointer to next vertex
        -   Temporary Dijkstra label
        -   Previous vertex in the route
        -   Flag for permanent label
2.  **Edges (`Arista`)**
    -   Contains:
        -   Weight (`peso`)
        -   Two vertex pointers
        -   Pointer to next edge
3.  **Linked Lists**
    -   `ConjuntoVertices`: manages vertices
    -   `ConjuntoAristas`: manages edges
4.  **Graph (`Grafica`)**
    -   Combines vertex and edge lists
    -   Contains Dijkstra implementation

### How Dijkstra Works in This Program

1.  The origin vertex receives label `0`.
2.  All other vertices start with label `-1` (unreached).
3.  The algorithm:
    -   Searches for adjacent vertices.
    -   Updates labels if a better route is found.
    -   Permanently marks the vertex with the smallest temporary label.
4.  Once the destination is permanently labeled:
    -   The path is reconstructed by following the `origenEtiqueta`
        chain.
    -   The final route is printed.

### Memory Management

-   Vertices and edges are dynamically allocated.
-   Before exiting, the program frees memory using:
    -   `vaciarListaVertices`
    -   `vaciarListaAristas`

------------------------------------------------------------------------

## Challenges and Learnings

-   Managing graphs through custom linked lists provides deeper insight
    into pointer-based data structures.
-   Implementing Dijkstra manually enhances understanding of:
    -   Label updates\
    -   Permanent vs. temporary selections\
    -   Path reconstruction logic\
-   Creating an interactive menu system reinforces modular programming
    practices.

------------------------------------------------------------------------

## Tools Used

-   **Language**: C++
-   **Compiler**: GCC / MinGW
-   **IDE/Text Editor**: DevCpp

------------------------------------------------------------------------

## Team Members

-   *Pedro Enrique Sánchez Rodríguez*\
-   *Jorge Araujo Hernández*\

------------------------------------------------------------------------

## Conclusion

This project demonstrates the construction of a graph and the
implementation of Dijkstra's shortest path algorithm using C++. Through
manual memory management, linked lists, and iterative logic, it offers
hands-on experience with core algorithmic principles and graph theory.

