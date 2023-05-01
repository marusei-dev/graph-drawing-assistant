#include <QWidget>
#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#include "graph.h"
#include <QMouseEvent>
#include <iostream>

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
