#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Creating the top menu bar.
    QMenuBar* topMenuBar = new QMenuBar(this);

    // Creating menu options for the top menu bar.
    QMenu* fileMenu = new QMenu("File", topMenuBar);
    QMenu* editMenu = new QMenu("Edit", topMenuBar);

    // Creating actions for the "File" menu in the top menu bar.
    saveGraphAction = new QAction("Save Graph", fileMenu);
    loadLastGraphAction = new QAction("Load Graph", fileMenu);

    // Adding actions above to the "File" menu.
    fileMenu->addAction(saveGraphAction);
    fileMenu->addAction(loadLastGraphAction);

    // Adding menu options to the top menu bar.
    topMenuBar->addMenu(fileMenu);
    topMenuBar->addMenu(editMenu);

    // Adding the menu bar created above to the main window.
    setMenuBar(topMenuBar);

    // Creating and setting up the tool bar dock widget on the left.
    QDockWidget* dockToolbar = new QDockWidget("Tool Bar", this);
    dockToolbar->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockToolbar->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockToolbar->setMinimumWidth(150);
    dockToolbar->setMaximumWidth(250);
    dockToolbar->setStyleSheet("border-right: 3px solid grey");

    // Creating and setting up the properties dock widget on the right.
    QDockWidget* dockProperties = new QDockWidget("Properties", this);
    dockProperties->setAllowedAreas(Qt::RightDockWidgetArea);
    dockProperties->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dockProperties->setMinimumWidth(250);
    dockProperties->setMaximumWidth(300);
    dockProperties->setStyleSheet("border-left: 3px solid grey");

    // Adjusting the layout of the tool bar dock widget and adding buttons to it.
    QWidget* toolbarWidget = new QWidget(dockToolbar);
    QVBoxLayout* toolbarVerticalLayout = new QVBoxLayout(toolbarWidget);
    QPushButton* addNodeButton = new QPushButton("Add Node", toolbarWidget);
    QPushButton* addUndirectedEdgeButton = new QPushButton("Add Undirected Edge", toolbarWidget);
    toolbarVerticalLayout->addWidget(addNodeButton);
    toolbarVerticalLayout->addWidget(addUndirectedEdgeButton);
    toolbarVerticalLayout->setAlignment(Qt::AlignTop);
    dockToolbar->setWidget(toolbarWidget);

    // Adjusting the layout of the properties dock widget.
    QWidget* propertiesWidget = new QWidget(dockProperties);
    QVBoxLayout* propertiesVerticalLayout = new QVBoxLayout(propertiesWidget);
    propertiesVerticalLayout->setAlignment(Qt::AlignTop);
    dockProperties->setWidget(propertiesWidget);

    // Adding two dock widgets to the main window.
    addDockWidget(Qt::LeftDockWidgetArea, dockToolbar);
    addDockWidget(Qt::RightDockWidgetArea, dockProperties);

    // Preparing a palette to draw the white background of the canvas widget.
    QPalette backgroundPalette;
    backgroundPalette.setBrush(QPalette::Window, QBrush(Qt::white));

    // Creating the canvas widget and drawing its background.
    canvasWidget = new CanvasWidget(this);
    canvasWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    canvasWidget->setAutoFillBackground(true);
    canvasWidget->setPalette(backgroundPalette);

    // Adjusting the main layout of the main window. Created with the purpose of making the canvas widget take up all the space between two dock widgets.
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addWidget(canvasWidget);
    mainLayout->setContentsMargins(QMargins(0, 0, 0, 0));

    // Creating and setting the central widget which will enforce the main layout.
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    /*
     * Adding shortcuts for conveniency of the user.
     *
     * addNodeButtonShortcut - Add Node button can be pressed by pressing 'V' on the keyboard.
     * addUndirectedEdgeButtonShortcut - Add Undirected Edge button can be pressed by pressing 'E' on the keyboard.
    */
    QShortcut* addNodeButtonShortcut = new QShortcut(QKeySequence(Qt::Key_V), this);
    QShortcut* addUndirectedEdgeButtonShortcut = new QShortcut(QKeySequence(Qt::Key_E), this);

    /*
     * Below there are implemented some of the connections between signals and slots in the programme.
     *
     * 1. Connection between addNodeButton click signal of QButton and onAddNodeButtonClick slot in CanvasWidget.
     *
     *    Made to update the addNodeButtonClicked boolean flag of CanvasWidget to true.
     *
     * 2. Connection between mouseClickedOnCanvas signal of CanvasWidget and onMousePressEvent slot in CanvasWidget.
     *
     *    Made to process mouse clicks on the canvas. mouseClickedOnCanvas is a signal that is emitted by the general overridden mousePressEvent signal
     *    of any QWidget class. onMousePressEvent is the slot in CanvasWidget that processes mouse clicks and checks which flag in CanvasWidget is
     *    raised to process it accordingly.
     *
     * 3. Connection between addNodeRequested signal of CanvasWidget and onAddNodeRequested slot in CanvasWidget
     *
     *    onMousePressEvent checks which flag is raised. If the addNodeButtonClicked attribute-flag in CanvasWidget is true, CanvasWidget will send
     *    the addNodeRequested signal to be processed in the onAddNodeRequested slot in the same class, which is responsible for opening a dialogue
     *    with the user about node addition.
     *
     * 4. Connection between clicked signal of addUndirectedEdgeButton and onAddUndirectedEdgeButtonClick slot in CanvasWidget
     *
     *    Made to process "Add Undirected Edge" button click in CanvasWidget. Opens a dialogue with the user about edge addition.
     *
     * 5 and 6. Connections to enable shortcuts.
    */

    QObject::connect(addNodeButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::onAddNodeButtonClick);
    QObject::connect(canvasWidget, &CanvasWidget::mouseClickedOnCanvas, canvasWidget, &CanvasWidget::onMousePressEvent);
    QObject::connect(canvasWidget, &CanvasWidget::addNodeRequested, canvasWidget, &CanvasWidget::onAddNodeRequested);
    QObject::connect(addUndirectedEdgeButton, &QPushButton::clicked, canvasWidget, &CanvasWidget::onAddUndirectedEdgeButtonClick);
    QObject::connect(addNodeButtonShortcut, &QShortcut::activated, addNodeButton, &QPushButton::click);
    QObject::connect(addUndirectedEdgeButtonShortcut, &QShortcut::activated, addUndirectedEdgeButton, &QPushButton::click);
    /*
        Connection between actions in the menu fails for some reason. I need to save the current graph to a file
        using the respective action in the file menu. And load it.
    */
}

MainWindow::~MainWindow() {}


