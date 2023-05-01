#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget* parent) : QWidget(parent), addNodeButtonClicked(false) {
    graph = new Graph;
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

    }
}

void CanvasWidget::onAddDirectedEdgeButtonClick() {}
void CanvasWidget::onAddUndirectedEdgeButtonClick() {}
