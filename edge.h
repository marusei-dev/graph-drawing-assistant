
#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"

/*
 * class Edge is a class that represents an edge and is used by the object of the Graph class.
 *
 * ATTRIBUTES
 *
 * int ID - the ID of the edge, represents the position of the latter in the edge set.
 *
 * Vertex* startVertex - startVertex pointer points to the start vertex of the edge. For an undirected edge such as this, it could as well be named
 * as firstVertex or vertexOne.
 *
 * Vertex* endVertex - same as the previous attribute, but this pointer points to the end vertex of the edge.
 *
 * METHODS
 *
 *
*/

class Edge
{
    int ID;
    Vertex* startVertex;
    Vertex* endVertex;

public:
    Edge(int ID, Vertex* startVertex, Vertex* endVertex);
    Edge();
    Vertex* getStartVertex();
    Vertex* getEndVertex();
    void setID(int ID);
    int getID();
};

#endif // EDGE_H
