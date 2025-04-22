#ifndef SHAPEITEM_H
#define SHAPEITEM_H

#include <QObject>
#include <QGraphicsObject>
#include "shape.h"


class ShapeItem : public QGraphicsObject {
    Q_OBJECT

public:
    ShapeItem(Shape* shape, QColor color, float cell_size);

    QRectF boundingRect() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) override;

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void SetPreviewMode(bool enabled);

    void SetHighlighted(bool enabled);
    Shape* GetShape() const;
    QColor GetColor() const;

    // for rotato
    void RotateCW();



signals:
    void DroppedOnBoard(QPoint board_pos);
    void ShapeClicked(Shape* shape, QColor color);

private:
    Shape* shape_;
    QColor color_;
    float cell_size_;

    // for pre-place
    bool highlighted_ = false;
    bool preview_mode_ = false;


};

#endif // SHAPEITEM_H
