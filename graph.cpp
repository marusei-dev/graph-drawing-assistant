
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
    int i = 0;
    while (i < edgeSetSize) {
        if (edgeSet[i].getStartVertex()->getID() == vertexSet[ID].getID() || edgeSet[i].getEndVertex()->getID() == vertexSet[ID].getID()) {
            deleteEdge(i);
            i = 0;
        }
        else {
            i++;
        }
    }
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


void Graph::addEdge(int ID1, int ID2) {
    Edge* temp = new Edge[edgeSetSize];
    for (int i = 0; i < edgeSetSize; i++) {
        temp[i] = edgeSet[i];
    }
    edgeSet = new Edge[++edgeSetSize];
    for (int i = 0; i < edgeSetSize - 1; i++) {
        edgeSet[i] = temp[i];
    }
    edgeSet[edgeSetSize - 1] = Edge(edgeSetSize - 1, &vertexSet[ID1], &vertexSet[ID2]);
    edgeSet[edgeSetSize - 1].setID(edgeSetSize - 1);
    delete[] temp;

    std::cout << "Current state of the edge set:" << std::endl;
    for (int i = 0; i < edgeSetSize; i++) {
        std::cout << "Edge with ID = " << edgeSet[i].getID() << std::endl;
    }
}

void Graph::deleteEdge(int ID) {
    Edge* temp = new Edge[edgeSetSize];
    for (int i = 0; i < edgeSetSize; i++)
        temp[i] = edgeSet[i];
    edgeSet = new Edge[--edgeSetSize];
    for (int i = 0, j = 0; i < edgeSetSize; i++) {
        if (j == ID)
            j++;
        edgeSet[i] = temp[j];
        edgeSet[i].setID(i);
        j++;
    }
    delete[] temp;
}
