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
#include <QCoreApplication>
#include <QFile>
#include <QStandardPaths>
#include <QDir>

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
 * | IMPORTANT REMARK!
 * |
 * | It seems to be not the best practice to keep transient interface elements as attributes of their parent class, however, the use of QObject::connect
 * | operations in pair with lambda functions inside them made it necessary to store these elements this way, otherwise their data is lost and the
 * | connections do not work.
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
 * Constructor and destructor - the former provides some attributes with initial values.
 *
 * void redrawGraph() - a method that is used to update the drawn vertices and edges. Fetches the information about the vertices and edges from the
 * Graph graph attribute, and forces the CanvasWidget to update(), which launches the overriden paintEvent function.
 *
 * SIGNALS
 *
 * void mouseClickedOnCanvas(QMouseEvent* event) - a signal that is emitted from the mousePressEvent overriden protected method.
 *
 * void addNodeRequested(QPoint position) - a signal that is emitted when the addNodeButtonClicked is true and when the mouseClickedOnCanvas signal
 * is received. QPoint position is the position of the mouse click on the canvas.
 *
 * PROTECTED PART - OVERRIDEN METHODS FROM Q WIDGET
 *
 * void mousePressEvent(QMouseEvent* event) override - a method every QWidget and QWidget-derived class has. Is launched when a mouse press on the widget is
 * detected.
 *
 * void paintEvent(QPaintEvent* event) override - paintEvent is launched whenever a widget is shown or is updated. Used to draw vertices and edges to the
 * canvas.
 *
 * SLOTS:
 *
 * void onAddNodeButtonClick() - the slot that simply changes the bool addNodeButtonClicked to true.
 *
 * void onAddUndirectedEdgeButtonClick() - the slot that is launched when the Add Undirected Edge button in the tool bar dock widget is clicked.
 * Used to open the window where the user can choose from which vertex to which vertex to draw an edge.
 *
 * void onMousePressEvent(QMouseEvent* event) - the slot that checks which flag is true (which for now only means which button is pressed), and emits
 * an appropriate signal.
 *
 * void onAddNodeRequested(QPoint position) - the slot that opens the window which prompts the user to enter the name for their vertex that is to be
 * added. Then, in this same slot, the vertex with the entered name is added to the Graph graph.
 *
 * void onDeleteVertexRequested(int ID) - the slot that implements the deletion of vertices. Is called by a right button click on any of vertices. Then,
 * the vertex which was clicked sends its ID (which is, in fact, its position in the vertex set of the Graph graph attribute) along with emitting the
 * deleteVertexRequested signal.
 *
 * void onDeleteEdgeRequested(int ID) - the slot which deals with the deletion of edges. It has a similar functionality to the previous slot.
 *
 * INCOMPLETE - TO BE CONTINUED
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
    void onAddUndirectedEdgeButtonClick();
    void onMousePressEvent(QMouseEvent* event);
    void onAddNodeRequested(QPoint position);
    void onDeleteVertexRequested(int ID);
    void onDeleteEdgeRequested(int ID);
    void onSaveGraphAction(bool checked);
    void onLoadLastGraphAction(bool checked);
};

#endif // CANVASWIDGET_H
