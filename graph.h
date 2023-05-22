
#ifndef GRAPH_H
#define GRAPH_H
#include "vertex.h"
#include "edge.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <iostream>

/*
 * Graph is a class that serves as a container for vertices and edges and is also designed to operate on them.
*/

class Graph
{
    Vertex* vertexSet;
    int vertexSetSize;
    Edge* edgeSet;
    int edgeSetSize;

public:
    Graph();
    int getVertexSetSize();
    int getEdgeSetSize();
    friend class CanvasWidget;
public slots:
    void addVertex(QString name, QPoint position);
    void addEdge(int ID1, int ID2);
    void deleteVertex(int ID);
    void deleteEdge(int ID);

};

#endif // GRAPH_H
