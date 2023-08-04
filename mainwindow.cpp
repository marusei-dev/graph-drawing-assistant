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

    toolbarWidget = new QWidget(dockToolbar);
    toolbarVerticalLayout = new QVBoxLayout(toolbarWidget);
    addNodeButton = new QPushButton("Add Node", toolbarWidget);
    addUndirectedEdgeButton = new QPushButton("Add Undirected Edge", toolbarWidget);
    toolbarVerticalLayout->addWidget(addNodeButton);
    toolbarVerticalLayout->addWidget(addUndirectedEdgeButton);
    toolbarVerticalLayout->setAlignment(Qt::AlignTop);
    dockToolbar->setWidget(toolbarWidget);

    dockProperties = new QDockWidget("Properties", this);
    dockProperties->setAllowedAreas(Qt::RightDockWidgetArea);
    dockProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockProperties->setMinimumWidth(250);
    dockProperties->setMaximumWidth(300);


    propertiesWidget = new QWidget(dockProperties);
    propertiesWidgetLayout = new QVBoxLayout(dockProperties);


    propertiesTreeWidget = new QTreeWidget(propertiesWidget);
    propertiesTreeWidget->setStyleSheet("background-color: #F0F0F0; border: 0px");
    propertiesTreeWidget->setHeaderHidden(true);

    generalCategoryTreeRoot = new QTreeWidgetItem(propertiesTreeWidget, QStringList() << "General");
    vertexNumberItem = new QTreeWidgetItem(generalCategoryTreeRoot);
    edgeNumberItem = new QTreeWidgetItem(generalCategoryTreeRoot);
    vertexNumberItem->setText(0, "Number of Vertices: 0");
    edgeNumberItem->setText(0, "Number of Edges: 0");

    colouringCategoryTreeRoot = new QTreeWidgetItem(propertiesTreeWidget, QStringList() << "Colouring");
    vertexChromaticNumberItem = new QTreeWidgetItem(colouringCategoryTreeRoot);
    edgeChromaticNumberItem = new QTreeWidgetItem(colouringCategoryTreeRoot);
    vertexChromaticNumberItem->setText(0, "Vertex Chromatic Number: 1");
    edgeChromaticNumberItem->setText(0, "Edge Chromatic Number: 1");

    propertiesWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    propertiesWidgetLayout->addWidget(propertiesTreeWidget);
    propertiesWidgetLayout->setContentsMargins(0, 0, 0, 0);
    propertiesWidgetLayout->setAlignment(Qt::AlignTop);

    dockProperties->setWidget(propertiesWidget);

    addDockWidget(Qt::LeftDockWidgetArea, dockToolbar);
    addDockWidget(Qt::RightDockWidgetArea, dockProperties);

    QPalette backgroundPalette;
    backgroundPalette.setBrush(QPalette::Window, QBrush(Qt::white));

    canvasWidget = new CanvasWidget(this);
    canvasWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    canvasWidget->setAutoFillBackground(true);
    //canvasWidget->setPalette(backgroundPalette);

    mainLayout = new QHBoxLayout();
    mainLayout->addWidget(canvasWidget);
    mainLayout->setContentsMargins(QMargins(0, 0, 0, 0));

    centralWidget = new QWidget(this);
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
    QObject::connect(canvasWidget, &CanvasWidget::graphChanged, this, &MainWindow::updateProperties);
}
void MainWindow::updateProperties() {
    //vertexNumberText = QString("Number of Vertices: ") + QString::number(canvasWidget->getVertexSetSize());
    //edgeNumberText = QString("Number of Edges: ") + QString::number(canvasWidget->getEdgeSetSize());

    //vertexNumberItem->setText(0, vertexNumberText);
    //edgeNumberItem->setText(0, edgeNumberText);
}
MainWindow::~MainWindow() {}
