
#include "edgewidget.h"

EdgeWidget::EdgeWidget(QWidget *parent)
    : QWidget{parent}
{

}

EdgeWidget::EdgeWidget(Vertex* startVertex, Vertex* endVertex, QWidget* parent) : QWidget{parent}, startVertex(startVertex), endVertex(endVertex) {}

void EdgeWidget::addEnds(Vertex* startVertex, Vertex* endVertex) {
    this->startVertex = startVertex;
    this->endVertex = endVertex;
}

Vertex* EdgeWidget::getStartVertex() {return startVertex;}
Vertex* EdgeWidget::getEndVertex() {return endVertex;}

void EdgeWidget::mousePressEvent(QMouseEvent* event) {
    if (rect().contains(event->pos())) {
        emit mouseClickedOnEdge(event);
    }
}

void EdgeWidget::onMouseClickedOnEdge(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        emit deleteEdgeRequested(ID);
    }
}

int EdgeWidget::getID() const {return ID;}
void EdgeWidget::setID(int ID) {this->ID = ID;}
