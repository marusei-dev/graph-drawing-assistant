
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Q-classes
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDockWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QShortcut>
#include <QTreeWidget>
#include <QTreeWidgetItem>

// My classes
#include "canvaswidget.h"

class MainWindow : public QMainWindow

{
    Q_OBJECT

    // Top menu bar variable
    QMenuBar* topMenuBar;

    // Menus in the top menu bar
    QMenu* fileMenu;
    QMenu* editMenu;

    // Toolbar dock widget variables
    QDockWidget* dockToolbar;
    QWidget* toolbarWidget;
    QVBoxLayout* toolbarVerticalLayout;

    // Properties dock widget variables
    QDockWidget* dockProperties;
    QWidget* propertiesWidget;
    QVBoxLayout* propertiesWidgetLayout;

    QTreeWidget* propertiesTreeWidget;

    QTreeWidgetItem* generalCategoryTreeRoot;
    QTreeWidgetItem* vertexNumberItem;
    QTreeWidgetItem* edgeNumberItem;

    QTreeWidgetItem* colouringCategoryTreeRoot;
    QTreeWidgetItem* vertexChromaticNumberItem;
    QTreeWidgetItem* edgeChromaticNumberItem;

    // Dock widget buttons
    QPushButton* addNodeButton;
    QPushButton* addUndirectedEdgeButton;

    // CanvasWidget class variables
    CanvasWidget* canvasWidget;
    QHBoxLayout* mainLayout;
    QWidget* centralWidget;

    // Actions for the File menu in the top menu bar
    QAction* saveGraphAction;
    QAction* loadLastGraphAction;

    // Actions for the Edit menu in the top menu bar
    QAction* toggleDeletionModeAction;

    // Variables for displaying data in the general section of the properties widget
    QString edgeNumberText;
    QString vertexNumberText;

    // Shortcuts
    QShortcut* addNodeButtonShortcut;
    QShortcut* addUndirectedEdgeButtonShortcut;
    QShortcut* toggleDeletionModeActionShortcut;

public:
    MainWindow(QWidget *parent = nullptr);
    void initialiseGraphicalInterface();
    void initialiseShortcuts();
    void executeConnections();

    void updateProperties();
    ~MainWindow();
};

#endif // MAINWINDOW_H
