
#include "vertex.h"

Vertex::Vertex(QString name, const QPoint& position, int ID)
    : ID(ID), name(name), position(position) {}

Vertex::Vertex() : ID(0), name("Unnamed"), position(QPoint(0, 0)) {}

QString Vertex::getName() const {return name;}
QPoint Vertex::getPosition() const {return position;}
int Vertex::getID() const {return ID;}
void Vertex::setID(int ID) {this->ID = ID;}
