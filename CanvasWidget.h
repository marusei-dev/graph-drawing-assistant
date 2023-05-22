#include <QWidget>
#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#include <QMouseEvent>
#include <iostream>
#include "graph.h"
#include <QPoint>
#include <QPlainTextEdit>
#include "vertexwidget.h"
#include <QComboBox>
#include <QStringList>
#include <QLabel>
#include <QSpacerItem>
#include <QPushButton>
#include <QStringListModel>
#include "edgewidget.h"
#include <fstream>

/*
 * CanvasWidget is a manually created class that is derived from QWidget.
 *
 * It was necessary because of the restrictions of data access when using slots of a general QWidget class.
*/

class CanvasWidget : public QWidget {
    Q_OBJECT
    Graph graph;
    bool addNodeButtonClicked;
    QLineEdit* vertexNameTextField;
    VertexWidget** vertexWidgetSet;
    EdgeWidget** edgeWidgetSet;
    QWidget* addVertexWindow;
    QWidget* addUndirectedEdgeWindow;
    QComboBox* startVertexComboBox;
    QComboBox* endVertexComboBox;
    int vertexWidgetSetSize;
    int edgeWidgetSetSize;
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
    void onDeleteEdgeRequested(int ID);
    void onSaveGraphAction();
    void onLoadLastGraphAction();
};

#endif // CANVASWIDGET_H
