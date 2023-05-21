#include <QWidget>
#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#include <QMouseEvent>
#include <iostream>
#include "graph.h"
#include <QPoint>
#include <QPlainTextEdit>
#include "vertexwidget.h"

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
    QLineEdit* vertexNameTextField;
    VertexWidget** vertexWidgetSet;
    QWidget* addVertexWindow;
    int vertexWidgetSetSize;
    QPoint savedPosition;
    int vertexRadius;
public:
    CanvasWidget(QWidget* parent = nullptr);
    ~CanvasWidget();
    void redrawGraph();
signals:
    void mouseClickedOnCanvas(QMouseEvent* event);
    void addNodeRequested(QPoint position);
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
public slots:
    void onAddNodeButtonClick();
    void onAddUndirectedEdgeButtonClick();
    void onMousePressEvent(QMouseEvent* event);
    void onAddNodeRequested(QPoint position);
    void onDeleteVertexRequested(int ID);
};

#endif // CANVASWIDGET_H
