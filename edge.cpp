
#include "edge.h"

Edge::Edge() : ID(0), startVertex(nullptr), endVertex(nullptr)
{

}

Edge::Edge(int ID, Vertex* startVertex, Vertex* endVertex) : ID(ID), startVertex(startVertex), endVertex(endVertex) {}

Vertex* Edge::getStartVertex() {return startVertex;}
Vertex* Edge::getEndVertex() {return endVertex;}

void Edge::setID(int ID) {this->ID = ID;}
int Edge::getID() {return ID;}
