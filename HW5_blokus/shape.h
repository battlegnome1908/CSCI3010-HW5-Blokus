#ifndef SHAPE_H
#define SHAPE_H

#include <QPoint>
#include <QString>
#include <QVector>
#include <QRect>

struct Block {
    int x;
    int y;
};

class Shape
{
public:
    Shape(int id, const QVector<QPoint>& blocks, const QString& name);

    int GetID() const {return shape_id_; };

    const QVector<QPoint>& Blocks() const;
    void RotateCW();
    QString Name() const;

    QRect BoundingRect() const ;
    Shape* Clone() const; // mwahahaha factory style


private:
    QVector<QPoint> blocks_;
    QString name_;
    int shape_id_;
};

#endif // SHAPE_H
