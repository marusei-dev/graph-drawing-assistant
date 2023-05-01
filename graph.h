
#ifndef GRAPH_H
#define GRAPH_H
#include "vertex.h"
#include <QPoint>



class Graph
{
    Vertex* vertex;
public:
    Graph();
    bool addVertex(QPoint coordinate);
};

#endif // GRAPH_H
