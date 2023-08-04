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

    // Bool flags
    bool addNodeButtonClicked;
    bool deletionModeEnabled;

    // Add Vertex window components
    QWidget* addVertexWindow;
    QLineEdit* vertexNameTextField;
    QVBoxLayout* addVertexWindowVerticalLayout;

    // Add Undirected edge window components
    QWidget* addUndirectedEdgeWindow;
    QComboBox* startVertexComboBox;
    QComboBox* endVertexComboBox;
    QVBoxLayout* addUndirectedEdgeWindowVerticalLayout;
    QHBoxLayout* addUndirectedEdgeWindowHorizontalLayout;
    QLabel* connectingText;
    QHBoxLayout* connectingTextHorizontalLayout;
    QPushButton* confirmationButton;
    int correctedEndVertexIndex;


    // Vertex Widget set variables
    VertexWidget** vertexWidgetSet;
    int vertexRadius;
    int vertexWidgetSetSize;
    QPoint savedPosition;

    // Edge Widget set variables
    EdgeWidget** edgeWidgetSet;
    int edgeWidgetSetSize;

    // Save & Load graph actions variables
    QString saveFilePath;
    QString loadFilePath;

public:
    CanvasWidget(QWidget* parent = nullptr);
    ~CanvasWidget();

    void createAddVertexWindow();

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
