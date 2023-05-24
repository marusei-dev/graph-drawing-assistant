#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget* parent) :
    QWidget(parent), addNodeButtonClicked(false),
    vertexWidgetSet(nullptr), edgeWidgetSet(nullptr), addVertexWindow(nullptr), vertexWidgetSetSize(0), savedPosition(0, 0), vertexRadius(0) {}

void CanvasWidget::onAddNodeButtonClick() {
    addNodeButtonClicked = true;
}

void CanvasWidget::mousePressEvent(QMouseEvent* event) {
    if (rect().contains(event->pos())) {
           emit mouseClickedOnCanvas(event);
    }
}

void CanvasWidget::onMousePressEvent(QMouseEvent* event) {
    if (addNodeButtonClicked) {
           addNodeButtonClicked = false;
           emit addNodeRequested(event->pos());
    }
}

void CanvasWidget::onAddNodeRequested(QPoint position) {
    // Creating the window
    addVertexWindow = new QWidget();
    addVertexWindow->resize(250, 40);
    addVertexWindow->setWindowTitle("Add Node");

    // Setting the layout for the window. Adding the QLineEdit text field.
    QVBoxLayout* addVertexWindowVerticalLayout = new QVBoxLayout(addVertexWindow);
    vertexNameTextField = new QLineEdit(addVertexWindow);
    vertexNameTextField->setPlaceholderText("Enter the name of the node and press Enter");
    addVertexWindowVerticalLayout->addWidget(vertexNameTextField);
    addVertexWindowVerticalLayout->setAlignment(Qt::AlignTop);
    addVertexWindowVerticalLayout->setContentsMargins(QMargins(2, 2, 2, 2));

    /*
     * Opening the window and saving the position of the mouse click which is passed as a parameter to this function. The latter is necessary because
     * otherwise the value of position is lost when entering the QObject::connect statement and, particularly, the lambda expression.
    */
    addVertexWindow->show();
    savedPosition = position;

    /*
     * Processing the Return button press on the keyboard. Checking if the text field is non-empty, in which case adding the vertex with the entered name to
     * the graph. Redrawing the graph to display the changes.
    */
    QObject::connect(vertexNameTextField, &QLineEdit::returnPressed, this, [&]() {
        QString inputText = vertexNameTextField->text();
        if (inputText.toStdString() != "") {
            graph.addVertex(inputText, savedPosition);
            addVertexWindow->close();
            redrawGraph();
        }
    });

    /*
     * Limiting the number of characters the user can enter. Done by simpling deleting the last character on an attempt to enter it if the length
     * of the input string is greater than 10.
    */
    QObject::connect(vertexNameTextField, &QLineEdit::textEdited, this, [&]() {
        QString inputText = vertexNameTextField->text();
        if (inputText.toStdString().length() > 10) {
            vertexNameTextField->setText(inputText.left(inputText.size() - 1));
        }
    });
}

void CanvasWidget::onAddUndirectedEdgeButtonClick() {
    // Creating the window
    addUndirectedEdgeWindow = new QWidget();
    addUndirectedEdgeWindow->resize(400, 200);
    addUndirectedEdgeWindow->setWindowTitle("Add Undirected Edge");
\
    // Adding two main layouts.
    QVBoxLayout* addUndirectedEdgeWindowVerticalLayout = new QVBoxLayout(addUndirectedEdgeWindow);
    QHBoxLayout* addUndirectedEdgeWindowHorizontalLayout = new QHBoxLayout(addUndirectedEdgeWindow);

    // Initialising three of four elements of the Add Undirected Edge window.
    startVertexComboBox = new QComboBox(addUndirectedEdgeWindow);
    QLabel* connectingText = new QLabel("----------------------------", addUndirectedEdgeWindow);
    endVertexComboBox = new QComboBox(addUndirectedEdgeWindow);

    // Creating a layout for the QLabel text in the center. It is necessary to position it in the center between two dropdown lists.
    QHBoxLayout* connectingTextHorizontalLayout = new QHBoxLayout();
    connectingTextHorizontalLayout->addWidget(connectingText);
    connectingTextHorizontalLayout->setAlignment(Qt::AlignHCenter);

    // Adding elements to the previously created layouts and setting the layouts to properly display elements.
    addUndirectedEdgeWindowHorizontalLayout->addWidget(startVertexComboBox);
    addUndirectedEdgeWindowHorizontalLayout->addLayout(connectingTextHorizontalLayout);
    addUndirectedEdgeWindowHorizontalLayout->addWidget(endVertexComboBox);
    addUndirectedEdgeWindowHorizontalLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    addUndirectedEdgeWindowHorizontalLayout->setContentsMargins(10, 10, 10, 10);
    addUndirectedEdgeWindowHorizontalLayout->setStretchFactor(startVertexComboBox, 10);
    addUndirectedEdgeWindowHorizontalLayout->setStretchFactor(connectingTextHorizontalLayout, 10);
    addUndirectedEdgeWindowHorizontalLayout->setStretchFactor(endVertexComboBox, 10);

    // Creating the confirmation button for the user to confirm addition of an edge after choosing endpoints.
    QPushButton* confirmationButton = new QPushButton("Confirm", addUndirectedEdgeWindow);
    addUndirectedEdgeWindowVerticalLayout->addLayout(addUndirectedEdgeWindowHorizontalLayout);
    addUndirectedEdgeWindowVerticalLayout->addWidget(confirmationButton);

    /*
     * Adding elements to the dropdown lists. The second dropdown list (the one located closer to the right edge of the window) has all elements but
     * the first one, to avoid the same vertex appearing simultaneously in both dropdown lists.
    */

    for (int i = 0; i < vertexWidgetSetSize; i++) {
           startVertexComboBox->addItem(vertexWidgetSet[i]->getName());
           if (i != 0) {
               endVertexComboBox->addItem(vertexWidgetSet[i]->getName());
           }
    }

    // Opening the window.
    addUndirectedEdgeWindow->show();

    /*
     * Every time the user chooses a vertex from the list of vertices in the first dropdown list, the other dropdown list gets rebuilt so that it
     * does not contain the vertex that is chosen in the first dropdown list.
    */
    QObject::connect(startVertexComboBox, &QComboBox::currentIndexChanged, this, [&]() {
        endVertexComboBox->clear();
        for (int i = 0; i < vertexWidgetSetSize; i++) {
            if (i != startVertexComboBox->currentIndex()) {
                endVertexComboBox->addItem(vertexWidgetSet[i]->getName());
            }
        }
    });

    /*
     * Responding to the confirmation button click. Before adding an edge with chosen vertices, the index of the end vertex must be corrected, because
     * the second dropdown list contains less elements than the first one, so it would be incorrect to just take that index for later usage.
    */
    QObject::connect(confirmationButton, &QPushButton::clicked, this, [&]() {
        addUndirectedEdgeWindow->close();
        int correctedEndVertexIndex = endVertexComboBox->currentIndex();
        if (endVertexComboBox->currentIndex() >= startVertexComboBox->currentIndex()) {
            correctedEndVertexIndex++;
        }
        graph.addEdge(startVertexComboBox->currentIndex(), correctedEndVertexIndex);
        redrawGraph();
    });
}

void CanvasWidget::redrawGraph() {
    // Cleaning the vertex widget set before filling it with new values.
    if (vertexWidgetSet != nullptr) {
           for (int i = 0; i < vertexWidgetSetSize; i++) {
               delete vertexWidgetSet[i];
           }
           delete[] vertexWidgetSet;
           vertexWidgetSet = nullptr;
    }

    // Obtaining the correct vertex set size to be used as the size for the vertex widget set.
    vertexWidgetSetSize = graph.getVertexSetSize();
    vertexWidgetSet = new VertexWidget*[vertexWidgetSetSize];

    /*
     * Copying vertices from the Graph graph attribute. Since the graph attribute containts vertices as objects of the class Vertex, we cannot simply
     * copy elements using the assignment operation. This is an issue that could be potentially solved using the conversion constructor. CAN BE IMPROVED.
    */
    for (int i = 0; i < vertexWidgetSetSize; i++) {
           vertexWidgetSet[i] = new VertexWidget(this);
           vertexWidgetSet[i]->setPosition(graph.vertexSet[i].getPosition());
           vertexWidgetSet[i]->setName(graph.vertexSet[i].getName());
           vertexWidgetSet[i]->setID(graph.vertexSet[i].getID());
           vertexWidgetSet[i]->resize(50, 50);
           vertexWidgetSet[i]->move(graph.vertexSet[i].getPosition());
           vertexWidgetSet[i]->rect().moveTo(graph.vertexSet[i].getPosition());
           vertexWidgetSet[i]->setParent(this);
           QObject::connect(vertexWidgetSet[i], &VertexWidget::mouseClickedOnVertex, vertexWidgetSet[i], &VertexWidget::onMouseClickedOnVertex);
           QObject::connect(vertexWidgetSet[i], &VertexWidget::deleteVertexRequested, this, &CanvasWidget::onDeleteVertexRequested);
           vertexWidgetSet[i]->show();
    }

    // Cleaning the edge widget set before filling it with new values.
    if (edgeWidgetSet != nullptr) {
           for (int i = 0; i < edgeWidgetSetSize; i++) {
               delete edgeWidgetSet[i];
           }
           delete[] edgeWidgetSet;
           edgeWidgetSet = nullptr;
    }

    // Obtaining the correct size of the edge widget set.
    edgeWidgetSetSize = graph.getEdgeSetSize();
    edgeWidgetSet = new EdgeWidget*[edgeWidgetSetSize];

    /*
     *     Copying vertices from the Graph graph attribute. Since the graph attribute containts vertices as objects of the class Vertex,
     *     we cannot simply copy elements using the assignment operation.This is an issue that could be potentially solved using the conversion
     *     constructor. CAN BE IMPROVED.
    */
    for (int i = 0; i < edgeWidgetSetSize; i++) {
           edgeWidgetSet[i] = new EdgeWidget(this);
           edgeWidgetSet[i]->addEnds(graph.edgeSet[i].getStartVertex(), graph.edgeSet[i].getEndVertex());
           edgeWidgetSet[i]->setParent(this);
           edgeWidgetSet[i]->move(QPoint((graph.edgeSet[i].getStartVertex()->getPosition().x() + graph.edgeSet[i].getEndVertex()->getPosition().x()) / 2, (graph.edgeSet->getStartVertex()->getPosition().y() + graph.edgeSet[i].getEndVertex()->getPosition().y()) / 2));
           edgeWidgetSet[i]->rect().moveTo(QPoint((graph.edgeSet[i].getStartVertex()->getPosition().x() + graph.edgeSet[i].getEndVertex()->getPosition().x()) / 2, (graph.edgeSet->getStartVertex()->getPosition().y() + graph.edgeSet[i].getEndVertex()->getPosition().y()) / 2));
           edgeWidgetSet[i]->resize(100, 100);
           QObject::connect(edgeWidgetSet[i], &EdgeWidget::mouseClickedOnEdge, edgeWidgetSet[i], &EdgeWidget::onMouseClickedOnEdge);
           QObject::connect(edgeWidgetSet[i], &EdgeWidget::deleteEdgeRequested, this, &CanvasWidget::onDeleteEdgeRequested);
           edgeWidgetSet[i]->show();
    }

    /*
     * update() causes the paintEvent(QPaintEvent* event) to execute, thus redrawing the updated graph. This is a method that CanvasWidget inherited
     * from the QWidget class.
    */
    update();
}

void CanvasWidget::paintEvent(QPaintEvent* event) {
    // Activating the painting functionality.
    QWidget::paintEvent(event);

    // Initialising the painter and providing initial settigs.
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    // Setting up the font for later use when drawing text.
    QFont font;
    font.setPointSize(8);
    painter.setFont(font);

    /*
     * Drawing ellipses for vertices and text for names of vertices.
    */
    for (int i = 0; i < vertexWidgetSetSize; i++) {
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::gray);
        painter.drawEllipse(vertexWidgetSet[i]->getPosition().toPointF(), 5, 5);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::black);
        QRectF textRect(vertexWidgetSet[i]->getPosition().x() - 30, vertexWidgetSet[i]->getPosition().y() - 28, 70, 14);
        painter.drawText(textRect, Qt::AlignCenter, vertexWidgetSet[i]->getName());
    }

    /*
     * Drawing edges. In simple terms, a line is drawn from the position of the starting vertex to the position of the end vertex.
    */
    for (int i = 0; i < edgeWidgetSetSize; i++) {
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::gray);
        painter.drawLine(edgeWidgetSet[i]->getStartVertex()->getPosition().toPointF(), edgeWidgetSet[i]->getEndVertex()->getPosition().toPointF());
    }
}

CanvasWidget::~CanvasWidget() {}

void CanvasWidget::onDeleteVertexRequested(int ID) {
    graph.deleteVertex(ID);
    redrawGraph();
}

void CanvasWidget::onDeleteEdgeRequested(int ID) {
    graph.deleteEdge(ID);
    redrawGraph();
}

/*
 * TO BE COMPLETED
*/
void CanvasWidget::onSaveGraphAction() {
    std::cout << "Tried to Save!\n";
    std::ofstream saveFile("LastGraph.txt", std::ios::out);
    if (saveFile.is_open()) {
        saveFile << graph.vertexSetSize;
        saveFile << "|";
        for (int i = 0; i < graph.vertexSetSize; i++) {
               saveFile << graph.vertexSet[i].getID() << "," << graph.vertexSet[i].getName().toStdString() << "," << graph.vertexSet[i].getPosition().x() << "," << graph.vertexSet[i].getPosition().y() << ";";
        }
        saveFile << "?";
        saveFile << graph.edgeSetSize;
        for (int i = 0; i < graph.edgeSetSize; i++) {
               saveFile << graph.edgeSet[i].getID() << "," << graph.edgeSet->getStartVertex()->getID() << "," << graph.edgeSet[i].getEndVertex()->getID() << ";";
        }
        std::cout << "Wrote to FILE!\n";
    }
}

void CanvasWidget::onLoadLastGraphAction() {}
