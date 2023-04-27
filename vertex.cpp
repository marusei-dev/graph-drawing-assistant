
#include "vertex.h"

Vertex::Vertex(string name, Coordinate position, Color color, unsigned int inDegree, unsigned int outDegree) :
    name(name), position(position), color(color), outDegree(outDegree), inDegree(inDegree) {}

