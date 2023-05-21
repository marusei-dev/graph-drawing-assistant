#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget* parent) :
    QWidget(parent), addNodeButtonClicked(false), vertexTextInputFieldConnected(false),
    vertexWidgetSet(nullptr), addVertexWindow(nullptr), vertexWidgetSetSize(0), savedPosition(0, 0), vertexRadius(0) {}

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

    QVBoxLayout* addVertexWindowLayout = new QVBoxLayout(addVertexWindow);
    vertexNameTextField = new QLineEdit(addVertexWindow);
    vertexNameTextField->setPlaceholderText("Enter the name of the node and press Enter");
    addVertexWindowLayout->addWidget(vertexNameTextField);
    addVertexWindowLayout->setAlignment(Qt::AlignTop);
    addVertexWindowLayout->setContentsMargins(QMargins(2, 2, 2, 2));

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

void CanvasWidget::onAddUndirectedEdgeButtonClick() {}

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
           vertexWidgetSet[i]->resize(100, 100);
           vertexWidgetSet[i]->move(graph.vertexSet[i].getPosition());
           vertexWidgetSet[i]->rect().moveTo(graph.vertexSet[i].getPosition());
           vertexWidgetSet[i]->setParent(this);
           QObject::connect(vertexWidgetSet[i], &VertexWidget::mouseClickedOnVertex, vertexWidgetSet[i], &VertexWidget::onMouseClickedOnVertex);
           QObject::connect(vertexWidgetSet[i], &VertexWidget::deleteVertexRequested, this, &CanvasWidget::onDeleteVertexRequested);
           vertexWidgetSet[i]->show();

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
}

CanvasWidget::~CanvasWidget() {}

void CanvasWidget::onDeleteVertexRequested(int ID) {
    graph.deleteVertex(ID);
    redrawGraph();
}
