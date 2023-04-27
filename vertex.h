
#ifndef VERTEX_H
#define VERTEX_H

#include <string>
#include "coordinate.h"
using namespace std;

enum Color {WHITE, GREY, GREEN};

class Vertex
{
    string name;
    Coordinate position;
    Color color;
    unsigned int outDegree;
    unsigned int inDegree;
public:
    Vertex(string name, Coordinate position, Color color = WHITE, unsigned int inDegree = 0, unsigned int outDegree = 0);
};

#endif // VERTEX_H
