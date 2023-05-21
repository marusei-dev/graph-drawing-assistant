
#include "vertexwidget.h"

VertexWidget::VertexWidget(QWidget *parent)
    : QWidget{parent}, name("Unnamed"), position(QPoint(0, 0)), radius(50)
{

}

VertexWidget::VertexWidget() {}

VertexWidget::VertexWidget(QString name, QPoint position, int ID, QWidget* parent) : QWidget{parent}, ID(ID), name(name), position(position), radius(50) {}

int VertexWidget::getID() {return ID;}
QPoint VertexWidget::getPosition() {return position;}
QString VertexWidget::getName() {return name;}
void VertexWidget::setPosition(QPoint position) {this->position = position;}
void VertexWidget::setName(QString name) {this->name = name;}
void VertexWidget::setID(int ID) {this->ID = ID;}

void VertexWidget::mousePressEvent(QMouseEvent* event) {

    QRect widgetRect = rect();
    rect().adjust(20, 20, 20, 20);
    if (rect().contains(event->pos())) {
        std::cout << "Mouse clicked on a vertex" << std::endl;
        emit mouseClickedOnVertex(event);
    }
}

void VertexWidget::onMouseClickedOnVertex(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        std::cout << "Delete request sent" << std::endl;
        emit deleteVertexRequested(ID);
    }
}



