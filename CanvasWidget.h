#include <QWidget>
#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#include <QMouseEvent>
#include <iostream>
#include "graph.h"
#include <QPoint>

/*
 * CanvasWidget is a manually created class that is derived from QWidget.
 *
 * It was necessary because of the restrictions of data access when using slots of a general QWidget class.
*/

class CanvasWidget : public QWidget {
    Q_OBJECT
    Graph graph;
    bool addNodeButtonClicked;
    bool vertexTextInputFieldConnected;
public:
    CanvasWidget(QWidget* parent = nullptr);
    ~CanvasWidget();
    /*
     * redrawGraph method updates the graph shown on screen.
     * It is called whenever a mouse is clicked on the canvas.
    */
    void redrawGraph();
signals:
    void mouseClickedOnCanvas(QMouseEvent* event);
    void addNodeRequested(QPoint position);
protected:
    void mousePressEvent(QMouseEvent* event) override;
public slots:
    void onAddNodeButtonClick();
    void onAddUndirectedEdgeButtonClick();
    void onMousePressEvent(QMouseEvent* event);
    void onAddNodeRequested(QPoint position);
};

#endif // CANVASWIDGET_H
