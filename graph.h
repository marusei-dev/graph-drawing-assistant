
#ifndef GRAPH_H
#define GRAPH_H
#include "vertex.h"
#include "edge.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <iostream>

/*
 * Graph is a class that serves as a container for vertices and edges and is also designed to operate on them.
*/

class Graph
{
    Vertex** vertexSet;
    int vertexSetSize;
    Edge** edgeSet;
    int edgeSetSize;

public:
    Graph();

public slots:
    void addVertex(QString name, QPoint position);

};

#endif // GRAPH_H
