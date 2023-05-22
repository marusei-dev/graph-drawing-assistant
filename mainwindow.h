
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
#include <QSplitter>
#include <QImage>
#include <QPixmap>
#include <QPalette>
#include "canvaswidget.h"
#include <QString>
#include <QCoreApplication>
#include <QShortcut>



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
