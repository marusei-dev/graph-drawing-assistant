
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

    // Dock widgets and their layouts
    QDockWidget* dockToolbar;
    QWidget* toolbarWidget;
    QVBoxLayout* toolbarVerticalLayout;

    QDockWidget* dockProperties;
    QWidget* propertiesWidget;
    QVBoxLayout* propertiesVerticalLayout;

    // Dock widget buttons
    QPushButton* addNodeButton;
    QPushButton* addUndirectedEdgeButton;

    // CanvasWidget class variable
    CanvasWidget* canvasWidget;

    // Actions for the File menu in the top menu bar
    QAction* saveGraphAction;
    QAction* loadLastGraphAction;

    // Actions for the Edit menu in the top menu bar
    QAction* toggleDeletionModeAction;

    // Variables for displaying data in the properties widget
    QLabel* vertexNumberTextProperty;
    QLabel* edgeNumberTextProperty;
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
    ~MainWindow();
};

#endif // MAINWINDOW_H
