
#ifndef VERTEXWIDGET_H
#define VERTEXWIDGET_H

#include <QWidget>
#include <QPainter>
#include <iostream>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QMouseEvent>


class VertexWidget : public QWidget
{
    Q_OBJECT
    int ID;
    QString name;
    QPoint position;
    int radius;
public:
    VertexWidget();
    VertexWidget(QWidget *parent = nullptr);
    VertexWidget(QString name, QPoint position, int ID, QWidget* parent = nullptr);
    QPoint getPosition();
    QString getName();
    int getID();
    void setPosition(QPoint position);
    void setName(QString name);
    void setID(int ID);

signals:
    void mouseClickedOnVertex(QMouseEvent* event);
    void deleteVertexRequested(int ID);
protected:
    void mousePressEvent(QMouseEvent* event) override;
public slots:
    void onMouseClickedOnVertex(QMouseEvent* event);
};

#endif // VERTEXWIDGET_H
