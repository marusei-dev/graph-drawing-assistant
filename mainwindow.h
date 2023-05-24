
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDockWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include "canvaswidget.h"
#include <QShortcut>

/*
 * MainWindow class is the class operating on the main window of the application. It's task is to generate the initial, particularly static
 * widgets of the interface in its constructor.
 *
 * ATTRIBUTES
 *
 * CanvasWidget* canvasWidget - a pointer to an object of CanvasWidget for the control of the main area of the programme in between two dock widgets.
 *
 * METHODS
 *
 * No methods except a constructor and a destructor typical for QWidget-derived classes (QMainWindow is derived from QWidget itself). The constructor is responsible for
 * generating initial interface appearance.
 *
 * |AN IMPORTANT REMARK!
 * |
 * |The destructors throughout the programme are empty for QWidget-derived classes, even though most of elements are created using dynamic memory
 * |allocation. That is because unless I allocated memory for objects of custom classes or for something which is not a unique part of the Qt framework,
 * |the Qt application manages proper memory management itself. That is, it deletes dynamically allocated elements on its own, so I did not have to write
 * |deallocation operation for each and every QWidget-derived element I used, of which there are many.
*/

class MainWindow : public QMainWindow

{
    Q_OBJECT
    CanvasWidget* canvasWidget;
    QAction* saveGraphAction;
    QAction* loadLastGraphAction;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif // MAINWINDOW_H
