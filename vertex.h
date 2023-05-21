
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
    QString name;
    QPoint position;
public:
    Vertex(QString name, const QPoint& position);
    Vertex();
    Vertex(const Vertex& other);
};

#endif // VERTEX_H
