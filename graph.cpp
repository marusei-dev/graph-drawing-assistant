
#include "graph.h"

Graph::Graph() : vertexSet(nullptr), vertexSetSize(0), edgeSet(nullptr), edgeSetSize(0)
{

}

void Graph::addVertex(QString name, QPoint position) {
    Vertex* temp = new Vertex[vertexSetSize];
    for (int i = 0; i < vertexSetSize; i++)
        temp[i] = vertexSet[i];
    vertexSet = new Vertex[++vertexSetSize];
    for (int i = 0; i < vertexSetSize - 1; i++)
        vertexSet[i] = temp[i];
    vertexSet[vertexSetSize - 1] = Vertex(name, position, vertexSetSize - 1);
    delete[] temp;
}

int Graph::getEdgeSetSize() {return edgeSetSize;}
int Graph::getVertexSetSize() {return vertexSetSize;}

void Graph::deleteVertex(int ID) {
    Vertex* temp = new Vertex[vertexSetSize];
    for (int i = 0; i < vertexSetSize; i++)
        temp[i] = vertexSet[i];
    vertexSet = new Vertex[--vertexSetSize];
    for (int i = 0, j = 0; i < vertexSetSize; i++) {
        if (j == ID)
            j++;
        vertexSet[i] = temp[j];
        vertexSet[i].setID(i);
        j++;
    }
    delete[] temp;
}
