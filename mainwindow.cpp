#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    initialiseGraphicalInterface();
    initialiseShortcuts();
    executeConnections();
    emit canvasWidget->graphChanged();
}
void MainWindow::initialiseGraphicalInterface() {
    /*
     * Creating and positioning elements of the GUI at the launch.
    */
    topMenuBar = new QMenuBar(this);

    fileMenu = new QMenu("File", topMenuBar);
    editMenu = new QMenu("Edit", topMenuBar);

    saveGraphAction = new QAction("Save Graph", fileMenu);
    loadLastGraphAction = new QAction("Load Graph", fileMenu);
    toggleDeletionModeAction = new QAction("Toggle Deletion Mode", editMenu);
    toggleDeletionModeAction->setCheckable(true);

    fileMenu->addAction(saveGraphAction);
    fileMenu->addAction(loadLastGraphAction);
    editMenu->addAction(toggleDeletionModeAction);

    topMenuBar->addMenu(fileMenu);
    topMenuBar->addMenu(editMenu);

    setMenuBar(topMenuBar);

    dockToolbar = new QDockWidget("Tool Bar", this);
    dockToolbar->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockToolbar->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockToolbar->setMinimumWidth(150);
    dockToolbar->setMaximumWidth(250);
    dockToolbar->setStyleSheet("border-right: 3px solid grey");

    dockProperties = new QDockWidget("Properties", this);
    dockProperties->setAllowedAreas(Qt::RightDockWidgetArea);
    dockProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockProperties->setMinimumWidth(250);
    dockProperties->setMaximumWidth(300);
    dockProperties->setStyleSheet("border-left: 3px solid grey");

    toolbarWidget = new QWidget(dockToolbar);
    toolbarVerticalLayout = new QVBoxLayout(toolbarWidget);
    addNodeButton = new QPushButton("Add Node", toolbarWidget);
    addUndirectedEdgeButton = new QPushButton("Add Undirected Edge", toolbarWidget);
    toolbarVerticalLayout->addWidget(addNodeButton);
    toolbarVerticalLayout->addWidget(addUndirectedEdgeButton);
    toolbarVerticalLayout->setAlignment(Qt::AlignTop);
    dockToolbar->setWidget(toolbarWidget);


    propertiesWidget = new QWidget(dockProperties);

    vertexNumberTextProperty = new QLabel(propertiesWidget);
    edgeNumberTextProperty = new QLabel(propertiesWidget);


    propertiesVerticalLayout = new QVBoxLayout(propertiesWidget);
    propertiesVerticalLayout->addWidget(vertexNumberTextProperty);
    propertiesVerticalLayout->addWidget(edgeNumberTextProperty);
    propertiesVerticalLayout->setAlignment(Qt::AlignTop);
    dockProperties->setWidget(propertiesWidget);


    addDockWidget(Qt::LeftDockWidgetArea, dockToolbar);
    addDockWidget(Qt::RightDockWidgetArea, dockProperties);

    QPalette backgroundPalette;
    backgroundPalette.setBrush(QPalette::Window, QBrush(Qt::white));

    canvasWidget = new CanvasWidget(this);
    canvasWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    canvasWidget->setAutoFillBackground(true);
    canvasWidget->setPalette(backgroundPalette);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(canvasWidget);
    mainLayout->setContentsMargins(QMargins(0, 0, 0, 0));

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}
void MainWindow::initialiseShortcuts() {
    addNodeButtonShortcut = new QShortcut(QKeySequence(Qt::Key_V), this);
    addUndirectedEdgeButtonShortcut = new QShortcut(QKeySequence(Qt::Key_E), this);
    toggleDeletionModeActionShortcut = new QShortcut(QKeySequence(Qt::Key_D), this);
}
void MainWindow::executeConnections() {
    QObject::connect(saveGraphAction, &QAction::triggered, canvasWidget, &CanvasWidget::onSaveGraphAction);
    QObject::connect(loadLastGraphAction, &QAction::triggered, canvasWidget, &CanvasWidget::onLoadLastGraphAction);
    QObject::connect(toggleDeletionModeAction, &QAction::toggled, canvasWidget, &CanvasWidget::onToggleDeletionModeAction);
    QObject::connect(addNodeButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::onAddNodeButtonClick);
    QObject::connect(canvasWidget, &CanvasWidget::mouseClickedOnCanvas, canvasWidget, &CanvasWidget::onMousePressEvent);
    QObject::connect(canvasWidget, &CanvasWidget::addNodeRequested, canvasWidget, &CanvasWidget::onAddNodeRequested);
    QObject::connect(addUndirectedEdgeButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::onAddUndirectedEdgeButtonClick);
    QObject::connect(addNodeButtonShortcut, &QShortcut::activated, addNodeButton, &QPushButton::click);
    QObject::connect(addUndirectedEdgeButtonShortcut, &QShortcut::activated, addUndirectedEdgeButton, &QPushButton::click);
    QObject::connect(toggleDeletionModeActionShortcut, &QShortcut::activated, toggleDeletionModeAction, &QAction::toggle);
    QObject::connect(canvasWidget, &CanvasWidget::graphChanged, this, [&]() {
        vertexNumberText = QString("Number of Vertices: ") + QString::number(canvasWidget->getVertexSetSize());
        edgeNumberText = QString("Number of Edges: ") + QString::number(canvasWidget->getEdgeSetSize());

        vertexNumberTextProperty->setText(vertexNumberText);
        edgeNumberTextProperty->setText(edgeNumberText);
    });
}
MainWindow::~MainWindow() {}
