/**
 * @file shapeitem.cpp
 * @brief Implementation of the ShapeItem class for visual representation of shapes
 */
#include "shapeitem.h"
#include "shape.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

/**
 * @brief Constructs a new ShapeItem instance
 * @param shape Pointer to the Shape this item represents
 * @param color Color to render the shape with
 * @param cell_size Size of each cell in the shape grid
 */
ShapeItem::ShapeItem(Shape* shape, QColor color, float cell_size)
    : shape_(shape), color_(color), cell_size_(cell_size) {
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable, false);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
    setFlag(QGraphicsItem::ItemUsesExtendedStyleOption, true);
}

/**
 * @brief Calculates the bounding rectangle for the shape item
 * @return QRectF representing the item's bounding rectangle in scene coordinates
 */
QRectF ShapeItem::boundingRect() const {
    QRect bounds = shape_->BoundingRect();  // min/max of rotated shape
    return QRectF(bounds.x() * cell_size_,
                  bounds.y() * cell_size_,
                  bounds.width() * cell_size_,
                  bounds.height() * cell_size_);
}

/**
 * @brief Paints the shape item
 * @param painter Pointer to the QPainter to use for drawing
 * @param option Style options for the item
 * @param widget Widget being painted on
 */
void ShapeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setPen(Qt::NoPen);

    QColor fill = color_;
    if (preview_mode_) {
        fill.setAlpha(150);
    } else if (highlighted_ && preview_mode_== false) {
        fill = Qt::white;
    }

    painter->setBrush(fill);
    painter->setPen(Qt::NoPen);

    for (const QPoint& pt : shape_->Blocks()) {
        QRectF rect(pt.x() * cell_size_, pt.y() * cell_size_, cell_size_, cell_size_);

        if (preview_mode_) {
            // White glow for preview
            painter->setPen(QPen(Qt::white, 2));
            painter->setBrush(Qt::NoBrush);
            painter->drawRect(rect);

            // Translucent fill
            QColor translucent = color_;
            translucent.setAlpha(150);
            painter->setPen(Qt::NoPen);
            painter->setBrush(translucent);
            painter->drawRect(rect);
        } else {
            // Darker outline for placed pieces
            QColor outline = color_.darker(150);
            painter->setPen(QPen(outline, 2));
            painter->setBrush(color_);
            painter->drawRect(rect);

            if (highlighted_ ) {
                // Add a semi-transparent white highlight overlay
                painter->setPen(Qt::NoPen);
                painter->setBrush(QColor(255, 255, 255, 200));  // translucent white
                QRectF inner = rect.adjusted(2, 2, -2, -2);    // slightly inset
                painter->drawRect(inner);
            }
        }
    }


}

/**
 * @brief Handles mouse press events
 * @param event Mouse event information
 * Emits ShapeClicked signal when the item is clicked
 */
void ShapeItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mousePressEvent(event);
    emit ShapeClicked(shape_, color_);
}

/**
 * @brief Handles mouse move events
 * @param event Mouse event information
 */
void ShapeItem::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseMoveEvent(event);
}

/**
 * @brief Handles mouse release events
 * @param event Mouse event information
 */
void ShapeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mouseReleaseEvent(event);
}

/**
 * @brief Sets whether the item is in preview mode
 * @param enabled True to enable preview mode, false to disable
 */
void ShapeItem::SetPreviewMode(bool enabled) {
    preview_mode_ = enabled;
    update();
}

/**
 * @brief Sets whether the item is highlighted
 * @param enabled True to highlight the item, false to unhighlight
 */
void ShapeItem::SetHighlighted(bool enabled) {
    highlighted_ = enabled;
    update();
}

/**
 * @brief Gets the shape this item represents
 * @return Pointer to the Shape
 */
Shape* ShapeItem::GetShape() const {
    return shape_;
}

/**
 * @brief Gets the color of this shape item
 * @return QColor of the item
 */
QColor ShapeItem::GetColor() const {
    return color_;
}

/**
 * @brief Rotates the shape clockwise
 * Updates the visual representation after rotation
 */
void ShapeItem::RotateCW() {
    prepareGeometryChange();       // notify Qt we're changing shape bounds
    shape_->RotateCW();            // rotate shape data
    update();                      // trigger repaint
}
