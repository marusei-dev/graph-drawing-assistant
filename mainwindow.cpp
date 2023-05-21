#include "mainwindow.h"

/*
 * MainWindow's constructor is the main working area of the programme.
 * Here are set up initial, mainly static elements.
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar* topMenuBar = new QMenuBar(this);

    QMenu* fileMenu = new QMenu("File", topMenuBar);
    QMenu* editMenu = new QMenu("Edit", topMenuBar);

    QAction* newCanvasAction = new QAction("New Canvas", fileMenu);

    fileMenu->addAction(newCanvasAction);

    topMenuBar->addMenu(fileMenu);
    topMenuBar->addMenu(editMenu);

    setMenuBar(topMenuBar);

    QDockWidget* dockToolbar = new QDockWidget("Tool Bar", this);
    dockToolbar->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockToolbar->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockToolbar->setMinimumWidth(150);
    dockToolbar->setMaximumWidth(250);
    dockToolbar->setStyleSheet("border-right: 2px solid grey");

    QDockWidget* dockProperties = new QDockWidget("Properties", this);
    dockProperties->setAllowedAreas(Qt::RightDockWidgetArea);
    dockProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockProperties->setMinimumWidth(250);
    dockProperties->setMaximumWidth(300);
    dockProperties->setStyleSheet("border-left: 2px solid grey");

    QWidget* toolbarWidget = new QWidget(dockToolbar);
    QVBoxLayout* toolbarVerticalLayout = new QVBoxLayout(toolbarWidget);
    QPushButton* addNodeButton = new QPushButton("Add Node", toolbarWidget);
    QPushButton* addUndirectedEdgeButton = new QPushButton("Add Undirected Edge", toolbarWidget);
    toolbarVerticalLayout->addWidget(addNodeButton);
    toolbarVerticalLayout->addWidget(addUndirectedEdgeButton);
    toolbarVerticalLayout->setAlignment(Qt::AlignTop);
    dockToolbar->setWidget(toolbarWidget);

    QWidget* propertiesWidget = new QWidget(dockProperties);
    QVBoxLayout* propertiesVerticalLayout = new QVBoxLayout(propertiesWidget);
    propertiesVerticalLayout->setAlignment(Qt::AlignTop);
    dockProperties->setWidget(propertiesWidget);

    addDockWidget(Qt::LeftDockWidgetArea, dockToolbar);
    addDockWidget(Qt::RightDockWidgetArea, dockProperties);

    QString backgroundPath = QCoreApplication::applicationDirPath() + "/src/dotted-background.png";
    QPixmap backgroundPixmap(backgroundPath);
    QPalette backgroundPalette;
    backgroundPalette.setBrush(QPalette::Window, backgroundPixmap);

    CanvasWidget* canvasWidget = new CanvasWidget(this);
    canvasWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    canvasWidget->setAutoFillBackground(true);
    canvasWidget->setPalette(backgroundPalette);

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(canvasWidget);
    mainLayout->setContentsMargins(QMargins(0, 0, 0, 0));

    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    /*
     * Below there are implemented connections between signals and slots in the programme.
     *
     * 1. Connection between addNodeButton click signal of QButton and onAddNodeButtonClick slot in CanvasWidget.
     *
     *    Made to update the addNodeButtonClicked boolean flag of CanvasWidget to true.
     *
     * 2. Connection between mouseClickedOnCanvas signal of CanvasWidget and onMousePressEvent slot in Canvas Widget.
     *
     *    Made to process mouse clicks on the canvas. mouseClickedOnCanvas is a signal that is emitted by the general overridden mousePressEvent signal
     *    of any QWidget class. onMousePressEvent is the slot in CanvasWidget that processes mouse clicks and checks which flag in CanvasWidget is
     *    raised to process it accordingly.
    */

    QObject::connect(addNodeButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::onAddNodeButtonClick);
    QObject::connect(canvasWidget, &CanvasWidget::mouseClickedOnCanvas, canvasWidget, &CanvasWidget::onMousePressEvent);
    QObject::connect(canvasWidget, &CanvasWidget::addNodeRequested, canvasWidget, &CanvasWidget::onAddNodeRequested);
}

MainWindow::~MainWindow() {}


