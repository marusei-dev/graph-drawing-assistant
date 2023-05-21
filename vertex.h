
#ifndef VERTEX_H
#define VERTEX_H


#include <QWidget>
#include <QPoint>

/*
 * The Vertex class, objects of which will represent nodes in the graph on the screen.
 *
 * Inherited from QWidget to process mouse press events.
*/

class Vertex
{
    int ID;
    QString name;
    QPoint position;
public:
    Vertex(QString name, const QPoint& position, int ID);
    Vertex();
    QString getName() const;
    QPoint getPosition() const;
    int getID() const;
    void setID(int ID);
};

#endif // VERTEX_H
