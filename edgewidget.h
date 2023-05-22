
#ifndef EDGEWIDGET_H
#define EDGEWIDGET_H

#include <QWidget>
#include "vertex.h"
#include <QMouseEvent>


class EdgeWidget : public QWidget
{
    Q_OBJECT
    int ID;
    Vertex* startVertex;
    Vertex* endVertex;
public:
    EdgeWidget(QWidget *parent = nullptr);
    EdgeWidget(Vertex* startVertex, Vertex* endVertex, QWidget* parent = nullptr);
    void addEnds(Vertex* startVertex, Vertex* endVertex);
    Vertex* getStartVertex();
    Vertex* getEndVertex();
protected:
    void mousePressEvent(QMouseEvent* event) override;
signals:
    void mouseClickedOnEdge(QMouseEvent* event);
    void deleteEdgeRequested(int ID);
public slots:
    void onMouseClickedOnEdge(QMouseEvent* event);
};

#endif // EDGEWIDGET_H
