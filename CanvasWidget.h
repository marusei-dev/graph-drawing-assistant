#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

// Q-classes
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>
#include <QFile>

// C++ classes
#include <fstream>
#include <iostream>

// My classes
#include "graph.h"
#include "vertexwidget.h"
#include "edgewidget.h"

class CanvasWidget : public QWidget {
    Q_OBJECT

    // Graph class variable
    Graph graph;


    bool addNodeButtonClicked;
    bool deletionModeEnabled;
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
    int getVertexSetSize() const;
    int getEdgeSetSize() const;
signals:
    void mouseClickedOnCanvas(QMouseEvent* event);
    void addNodeRequested(QPoint position);
    void graphChanged();
protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
public slots:
    void onAddNodeButtonClick();
    void onToggleDeletionModeAction(bool status);
    void onAddUndirectedEdgeButtonClick();
    void onMousePressEvent(QMouseEvent* event);
    void onAddNodeRequested(QPoint position);
    void onDeleteVertexRequested(int ID);
    void onDeleteEdgeRequested(int ID);
    void onSaveGraphAction(bool checked);
    void onLoadLastGraphAction(bool checked);
};

#endif // CANVASWIDGET_H
