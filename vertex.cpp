
#include "vertex.h"

Vertex::Vertex(QString name, const QPoint& position)
    : name(name), position(position) {}

Vertex::Vertex() : name("Unnamed"), position(QPoint(0, 0)) {}

Vertex::Vertex(const Vertex& other) {
    name = other.name;
    position = other.position;
}
