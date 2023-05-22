
#ifndef EDGE_H
#define EDGE_H
#include "vertex.h"



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
