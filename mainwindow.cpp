
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Initialising key elements of the interface

    // Creating the top menu bar
    QMenuBar* topMenuBar = new QMenuBar(this);

    // Creating menu items to be added to the menu bar
    QMenu* fileMenu = new QMenu("File", topMenuBar);
    QMenu* editMenu = new QMenu("Edit", topMenuBar);

    // Creating actions for the File menu
    QAction* newCanvasAction = new QAction("New Canvas", fileMenu);

    // Adding action to the file menu
    fileMenu->addAction(newCanvasAction);

    // Adding menus to the top menu bar
    topMenuBar->addMenu(fileMenu);
    topMenuBar->addMenu(editMenu);

    // Setting the menu bar
    setMenuBar(topMenuBar);

    // Creating the dock widget to contain toolbar
    QDockWidget* dockToolbar = new QDockWidget("Tool Bar", this);
    dockToolbar->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockToolbar->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockToolbar->setMinimumWidth(150);
    dockToolbar->setMaximumWidth(250);
    dockToolbar->setStyleSheet("border-right: 2px solid grey");

    // Adding layout features
    QWidget* toolbarWidget = new QWidget(dockToolbar);
    QVBoxLayout* toolbarVerticalLayout = new QVBoxLayout(toolbarWidget);
    QPushButton* addNodeButton = new QPushButton("Add Node", toolbarWidget);
    QPushButton* addEdgeButton = new QPushButton("Add Edge", toolbarWidget);
    toolbarVerticalLayout->addWidget(addNodeButton);
    toolbarVerticalLayout->addWidget(addEdgeButton);
    toolbarVerticalLayout->setAlignment(Qt::AlignTop);
    dockToolbar->setWidget(toolbarWidget);

    // Adding the dock widget toolbar
    addDockWidget(Qt::LeftDockWidgetArea, dockToolbar);

    // Loading the background picture
    QPixmap backgroundPixmap("C:\\Qt\\Projects\\GraphDrawingAssistant\\src\\dotted-background.png");
    QPalette backgroundPalette;
    backgroundPalette.setBrush(QPalette::Window, backgroundPixmap);

    QWidget* canvasWidget = new QWidget(this);
    canvasWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    canvasWidget->setAutoFillBackground(true);
    canvasWidget->setPalette(backgroundPalette);


    // The main layout will allow canvas to take up all space that is not occupied by the dock widget
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(canvasWidget);
    mainLayout->setContentsMargins(QMargins(0, 0, 0, 0));

    // Central widget of the main window which will use the layout
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
}


