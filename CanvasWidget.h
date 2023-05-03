#include <QWidget>
#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#include "graph.h"
#include <QMouseEvent>
#include <iostream>

/*

CanvasWidget is the class created to manage the area of the programme between two dock areas, where the graph will be drawn.

ATTRIBUTES

Graph graph - an object of the Graph class. graph will contain all vertices and edges, as well as interactions between the two.
bool addNodeButtonClicked - a flag that is switched to true when the "Add Node" button is pressed in the interface.

*/

class CanvasWidget : public QWidget {
    Q_OBJECT
    Graph graph;
    bool addNodeButtonClicked;
public:
    CanvasWidget(QWidget* parent = nullptr);
    void redrawGraph();
signals:
    void mouseClickedOnCanvas(QMouseEvent* event);
protected:
    void mousePressEvent(QMouseEvent* event) override;
public slots:
    void onAddNodeButtonClick();
    void onAddUndirectedEdgeButtonClick();
    void onAddDirectedEdgeButtonClick();
    void onMousePressEvent(QMouseEvent* event);
};

#endif // CANVASWIDGET_H
