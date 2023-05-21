#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget* parent) : QWidget(parent), addNodeButtonClicked(false), vertexTextInputFieldConnected(false) {}

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
    QWidget* addVertexWindow = new QWidget();
    addVertexWindow->resize(250, 40);
    addVertexWindow->setWindowTitle("Add Node");

    QVBoxLayout* addVertexWindowLayout = new QVBoxLayout(addVertexWindow);
    QLineEdit* vertexNameTextField = new QLineEdit(addVertexWindow);
    vertexNameTextField->setPlaceholderText("Enter the name of the node and press Enter");
    addVertexWindowLayout->addWidget(vertexNameTextField);
    addVertexWindowLayout->setAlignment(Qt::AlignTop);
    addVertexWindowLayout->setContentsMargins(QMargins(2, 2, 2, 2));

    addVertexWindow->show();
    if (!vertexTextInputFieldConnected) {
           vertexTextInputFieldConnected = true;
           QObject::connect(vertexNameTextField, &QLineEdit::returnPressed, this, [&]() {
               //QString inputText = vertexNameTextField->text();
               //std::string inputTextStd = inputText.toStdString();
               std::cout << "Input Text: " << std::endl;
           });
    }
}

void CanvasWidget::onAddUndirectedEdgeButtonClick() {}

CanvasWidget::~CanvasWidget() {}
