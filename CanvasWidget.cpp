#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget* parent) :
    QWidget(parent), addNodeButtonClicked(false), deletionModeEnabled(false),
    vertexWidgetSet(nullptr), edgeWidgetSet(nullptr), addVertexWindow(nullptr), vertexWidgetSetSize(0), savedPosition(0, 0), vertexRadius(0) {
    emit graphChanged();
}

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
\
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
           edgeWidgetSet[i]->setID(graph.edgeSet[i].getID());
           edgeWidgetSet[i]->setParent(this);
           edgeWidgetSet[i]->move(QPoint((graph.edgeSet[i].getStartVertex()->getPosition().x() + graph.edgeSet[i].getEndVertex()->getPosition().x()) / 2, (graph.edgeSet->getStartVertex()->getPosition().y() + graph.edgeSet[i].getEndVertex()->getPosition().y()) / 2));
           edgeWidgetSet[i]->rect().moveTo(QPoint((graph.edgeSet[i].getStartVertex()->getPosition().x() + graph.edgeSet[i].getEndVertex()->getPosition().x()) / 2, (graph.edgeSet->getStartVertex()->getPosition().y() + graph.edgeSet[i].getEndVertex()->getPosition().y()) / 2));
           edgeWidgetSet[i]->resize(100, 100);
           QObject::connect(edgeWidgetSet[i], &EdgeWidget::mouseClickedOnEdge, edgeWidgetSet[i], &EdgeWidget::onMouseClickedOnEdge);
           QObject::connect(edgeWidgetSet[i], &EdgeWidget::deleteEdgeRequested, this, &CanvasWidget::onDeleteEdgeRequested);
           edgeWidgetSet[i]->show();
    }
    update();
    emit graphChanged();
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
        if (deletionModeEnabled) {
            Qt::PenStyle penStyle = Qt::DashLine;
            QPen pen(QColor(Qt::gray), 1, penStyle);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(vertexWidgetSet[i]->getPosition().x(), vertexWidgetSet[i]->getPosition().y(), vertexWidgetSet[i]->width(), vertexWidgetSet[i]->height());
        }
    }

    for (int i = 0; i < edgeWidgetSetSize; i++) {
        painter.setPen(Qt::gray);
        painter.setBrush(Qt::gray);
        painter.drawLine(edgeWidgetSet[i]->getStartVertex()->getPosition().toPointF(), edgeWidgetSet[i]->getEndVertex()->getPosition().toPointF());
        if (deletionModeEnabled) {
            Qt::PenStyle penStyle = Qt::DashLine;
            QPen pen(QColor(Qt::gray), 1, penStyle);
            painter.setPen(pen);
            painter.setBrush(Qt::NoBrush);
            painter.drawRect(edgeWidgetSet[i]->pos().x(), edgeWidgetSet[i]->pos().y(), edgeWidgetSet[i]->width(), edgeWidgetSet[i]->height());
        }
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

void CanvasWidget::onSaveGraphAction(bool checked) {
    QString saveFilePath = QCoreApplication::applicationDirPath() + "/" + "LastGraph.txt";
    try {
        std::ofstream saveFile(saveFilePath.toStdString(), std::ios::out);
        if (saveFile.is_open()) {
               for (int i = 0; i < graph.vertexSetSize; i++) {
                   saveFile << graph.vertexSet[i].getName().toStdString() << ","
                            << graph.vertexSet[i].getPosition().x() << ","
                            << graph.vertexSet[i].getPosition().y() << ";";
               }
               saveFile << "?";
               for (int i = 0; i < graph.edgeSetSize; i++) {
                   if (graph.edgeSet[i].getStartVertex() && graph.edgeSet[i].getEndVertex()) {
                       saveFile << graph.edgeSet[i].getStartVertex()->getID() << ","
                                << graph.edgeSet[i].getEndVertex()->getID() << ";";
                   }
               }
               saveFile.close();
        } else {
               throw std::runtime_error("Failed to open the file for writing.");
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error occurred while saving the graph: " << e.what() << std::endl;
    }
}

std::vector<std::string> splitString(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;

    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

void CanvasWidget::onLoadLastGraphAction(bool checked)
{
    QString loadFilePath = QCoreApplication::applicationDirPath() + "/" + "LastGraph.txt";
    std::ifstream loadFile(loadFilePath.toStdString(), std::ios::in);
    if (loadFile.is_open()) {
        std::cout << "File opened" << std::endl;
        std::string line;
        if (std::getline(loadFile, line)) { // Read the line containing vertex and edge information
               std::vector<std::string> tokens = splitString(line, '?'); // Split the line using the '?' separator

               if (tokens.size() == 2) {
                   std::vector<std::string> vertexTokens = splitString(tokens[0], ';'); // Split the vertex data using the ';' separator
                   for (const std::string& vertexToken : vertexTokens) {
                       std::vector<std::string> vertexFields = splitString(vertexToken, ','); // Split each vertex property using the ',' separator

                       if (vertexFields.size() == 3) {
                           std::string vertexName = vertexFields[0];
                           int vertexX, vertexY;
                           try {
                               vertexX = std::stoi(vertexFields[1]);
                               vertexY = std::stoi(vertexFields[2]);
                           }
                           catch (const std::invalid_argument& e) {
                               std::cerr << "Invalid vertex coordinate format: " << e.what() << std::endl;
                               return; // Abort loading if invalid coordinate format
                           }

                           graph.addVertex(QString::fromStdString(vertexName), QPoint(vertexX, vertexY));
                       } else {
                           std::cerr << "Invalid vertex field count: " << vertexFields.size() << std::endl;
                           return; // Abort loading if invalid vertex field count
                       }
                   }

                   std::vector<std::string> edgeTokens = splitString(tokens[1], ';'); // Split the edge data using the ';' separator
                   for (const std::string& edgeToken : edgeTokens) {
                       std::vector<std::string> edgeFields = splitString(edgeToken, ','); // Split each edge property using the ',' separator

                       if (edgeFields.size() == 2) {
                           int startVertexID, endVertexID;
                           try {
                               startVertexID = std::stoi(edgeFields[0]);
                               endVertexID = std::stoi(edgeFields[1]);
                           }
                           catch (const std::invalid_argument& e) {
                               std::cerr << "Invalid edge ID format: " << e.what() << std::endl;
                               return; // Abort loading if invalid edge ID format
                           }

                           graph.addEdge(startVertexID, endVertexID);
                       } else {
                           std::cerr << "Invalid edge field count: " << edgeFields.size() << std::endl;
                           return; // Abort loading if invalid edge field count
                       }
                   }
               } else {
                   std::cerr << "Invalid file format." << std::endl;
                   return; // Abort loading if invalid file format
               }
        } else {
               std::cerr << "Failed to read file." << std::endl;
               return; // Abort loading if failed to read file
        }

        loadFile.close();
        redrawGraph();
    } else {
        std::cerr << "Failed to open file for loading." << std::endl;
    }
}

void CanvasWidget::onToggleDeletionModeAction(bool status) {
    deletionModeEnabled = status ? true : false;
    redrawGraph();
}

int CanvasWidget::getEdgeSetSize() const {return graph.edgeSetSize;}
int CanvasWidget::getVertexSetSize() const {return graph.vertexSetSize;}
