#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H
#include <QWidget>
#include <QMouseEvent>
#include <iostream>
#include "graph.h"
#include <QPoint>
#include "vertexwidget.h"
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include "edgewidget.h"
#include <fstream>

/*
 * CanvasWidget is the class responsible for the proper work of the canvas area between dock widgets which is used for drawing graphs.
 *
 * ATTRIBUTES
 *
 * Graph graph - an object of the Graph class, which is responsible for keeping data on vertices and edges. CanvasWidget simply fetches the data
 * from this object when drawing VertexWidgets and EdgeWidgets.
 *
 * bool addNodeButtonClicked - a flag which reflects the state of the "Add Node" button in the tool bar dock widget.
 *
 * QLineEdit* vertexNameTextField - an element of the interface of the window which is opened when the user desires to add a vertex to the graph.
 * Fetches the name of the vertex to be added from the user.
 *
 * |IMPORTANT REMARK!
 * |
 * |It seems to be not the best practice to keep transient interface elements as attributes of their parent class, however, the use of QObject::connect
 * |operations in pair with lambda functions inside them made it necessary to store these elements this way, otherwise their data is lost and the
 * |connections do not work.
 *
 * VertexWidget** vertexWidgetSet - the set of VertexWidget objects. It is updated every time redrawGraph() method is called, where it is rebuilt to
 * match the vertex set of the Graph graph attribute before being used to draw vertices on the canvas.
 *
 * EdgeWidget** edgeWidgetSet - the same idea as with the vertexWidgetSet.
 *
 * QWidget* addVertexWindow - the window that is opened after the user clicked on the "Add Node" button and clicked on the canvas afterwards. Prompts
 * the user to enter the name of the vertex they want to add.
 *
 * QWidget* addUndirectedEdgeWindow - the window that is opened after the user clicks on the "Add Undirected Edge" button in the tool bar dock widget.
 * Prompts the user to choose endpoints of the edge to be added.
 *
 * QComboBox* startVertexComboBox - a dropdown for the starting vertex of the edge to be added.
 *
 * QComboBox* endVertexComboBox - a dropdown for the end vertex of the edge to be added.
 *
 * int vertexWidgetSetSize - the number of the elements in the vertexWidgetSet.
 *
 * int edgeWidgetSetSize - the number of the elements in the edgeWidgetSet.
 *
 * QPoint savedPosition - yet another attribute created to avoid the loss of data when using lambda expressions in QObject::connect. "Saves" the position
 * of the mouse click.
 *
 * int vertexRadius - the attribute that speaks for itself. Keeps the vertex radius, created to quickly change this property of VertexWidgets that will
 * be drawn.
 *
 * METHODS
 *
 *
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
