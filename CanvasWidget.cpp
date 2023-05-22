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
    addVertexWindow = new QWidget();
    addVertexWindow->resize(250, 40);
    addVertexWindow->setWindowTitle("Add Node");

    QVBoxLayout* addVertexWindowVerticalLayout = new QVBoxLayout(addVertexWindow);
    vertexNameTextField = new QLineEdit(addVertexWindow);
    vertexNameTextField->setPlaceholderText("Enter the name of the node and press Enter");
    addVertexWindowVerticalLayout->addWidget(vertexNameTextField);
    addVertexWindowVerticalLayout->setAlignment(Qt::AlignTop);
    addVertexWindowVerticalLayout->setContentsMargins(QMargins(2, 2, 2, 2));

    addVertexWindow->show();
    savedPosition = position;
    QObject::connect(vertexNameTextField, &QLineEdit::returnPressed, this, [&]() {
        QString inputText = vertexNameTextField->text();
        if (inputText.toStdString() != "") {
            graph.addVertex(inputText, savedPosition);
            addVertexWindow->close();
            redrawGraph();
        }
    });
    QObject::connect(vertexNameTextField, &QLineEdit::textEdited, this, [&]() {
        QString inputText = vertexNameTextField->text();
        if (inputText.toStdString().length() > 10) {
            vertexNameTextField->setText(inputText.left(inputText.size() - 1));
        }
    });
}

void CanvasWidget::onAddUndirectedEdgeButtonClick() {
    addUndirectedEdgeWindow = new QWidget();
    addUndirectedEdgeWindow->resize(400, 200);
    addUndirectedEdgeWindow->setWindowTitle("Add Undirected Edge");

    QVBoxLayout* addUndirectedEdgeWindowVerticalLayout = new QVBoxLayout(addUndirectedEdgeWindow);
    QHBoxLayout* addUndirectedEdgeWindowHorizontalLayout = new QHBoxLayout(addUndirectedEdgeWindow);

    startVertexComboBox = new QComboBox(addUndirectedEdgeWindow);
    QLabel* connectingText = new QLabel("----------------------------", addUndirectedEdgeWindow);
    endVertexComboBox = new QComboBox(addUndirectedEdgeWindow);

    QHBoxLayout* connectingTextHorizontalLayout = new QHBoxLayout();
    connectingTextHorizontalLayout->addWidget(connectingText);
    connectingTextHorizontalLayout->setAlignment(Qt::AlignHCenter);

    addUndirectedEdgeWindowHorizontalLayout->addWidget(startVertexComboBox);
    addUndirectedEdgeWindowHorizontalLayout->addLayout(connectingTextHorizontalLayout);
    addUndirectedEdgeWindowHorizontalLayout->addWidget(endVertexComboBox);
    addUndirectedEdgeWindowHorizontalLayout->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

    addUndirectedEdgeWindowHorizontalLayout->setContentsMargins(10, 10, 10, 10);
    addUndirectedEdgeWindowHorizontalLayout->setStretchFactor(startVertexComboBox, 10);
    addUndirectedEdgeWindowHorizontalLayout->setStretchFactor(connectingTextHorizontalLayout, 10);
    addUndirectedEdgeWindowHorizontalLayout->setStretchFactor(endVertexComboBox, 10);

    QPushButton* confirmationButton = new QPushButton("Confirm", addUndirectedEdgeWindow);
    addUndirectedEdgeWindowVerticalLayout->addLayout(addUndirectedEdgeWindowHorizontalLayout);
    addUndirectedEdgeWindowVerticalLayout->addWidget(confirmationButton);

    for (int i = 0; i < vertexWidgetSetSize; i++) {
           startVertexComboBox->addItem(vertexWidgetSet[i]->getName());
           if (i != 0) {
               endVertexComboBox->addItem(vertexWidgetSet[i]->getName());
           }
    }


    addUndirectedEdgeWindow->show();
    QObject::connect(startVertexComboBox, &QComboBox::currentIndexChanged, this, [&]() {
        endVertexComboBox->clear();
        for (int i = 0; i < vertexWidgetSetSize; i++) {
            if (i != startVertexComboBox->currentIndex()) {
                endVertexComboBox->addItem(vertexWidgetSet[i]->getName());
            }
        }
    });
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

    if (vertexWidgetSet != nullptr) {
           for (int i = 0; i < vertexWidgetSetSize; i++) {
               delete vertexWidgetSet[i];
           }
           delete[] vertexWidgetSet;
           vertexWidgetSet = nullptr;
    }

    vertexWidgetSetSize = graph.getVertexSetSize();
    vertexWidgetSet = new VertexWidget*[vertexWidgetSetSize];

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

    if (edgeWidgetSet != nullptr) {
           for (int i = 0; i < edgeWidgetSetSize; i++) {
               delete edgeWidgetSet[i];
           }
           delete[] edgeWidgetSet;
           edgeWidgetSet = nullptr;
    }

    edgeWidgetSetSize = graph.getEdgeSetSize();
    edgeWidgetSet = new EdgeWidget*[edgeWidgetSetSize];

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

    update();
}

void CanvasWidget::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::black);
    painter.setBrush(Qt::black);

    QFont font;
    font.setPointSize(8);
    painter.setFont(font);
    for (int i = 0; i < vertexWidgetSetSize; i++) {
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::gray);
        painter.drawEllipse(vertexWidgetSet[i]->getPosition().toPointF(), 5, 5);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::black);
        QRectF textRect(vertexWidgetSet[i]->getPosition().x() - 30, vertexWidgetSet[i]->getPosition().y() - 28, 70, 14);
        painter.drawText(textRect, Qt::AlignCenter, vertexWidgetSet[i]->getName());
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::gray);
        painter.drawEllipse(vertexWidgetSet[i]->getPosition().toPointF(), 5, 5);
    }
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
