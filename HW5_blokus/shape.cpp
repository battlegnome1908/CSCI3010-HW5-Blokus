/**
 * @file shape.cpp
 * @brief Implementation of the Shape class for Blokus game pieces
 */
#include "shape.h"

/**
 * @brief Constructs a new Shape instance
 * @param id Unique identifier for the shape
 * @param blocks Vector of points defining the shape's blocks
 * @param name Display name of the shape
 */
Shape::Shape(int id, const QVector<QPoint>& blocks, const QString& name)
    : blocks_(blocks), shape_id_(id), name_(name) {}


/**
 * @brief Gets the blocks that make up this shape
 * @return Constant reference to the vector of points representing blocks
 */
const QVector<QPoint>& Shape::Blocks() const {
    return blocks_;
}

/**
 * @brief Gets the name of the shape
 * @return QString containing the shape's name
 */
QString Shape::Name() const {
    return name_;
}

/**
 * @brief Rotates the shape 90 degrees clockwise
 * Transforms each point in the shape using the rotation matrix
 */
void Shape::RotateCW() {
    for (QPoint& pt : blocks_) {
        pt = QPoint(-pt.y(), pt.x());  // 90 degree clockwise
    }
}

/**
 * @brief Calculates the bounding rectangle of the shape
 * @return QRect representing the minimal rectangle that contains all blocks
 */
QRect Shape::BoundingRect() const {
    if (blocks_.isEmpty()) return QRect();

    int min_x = blocks_[0].x(), max_x = blocks_[0].x();
    int min_y = blocks_[0].y(), max_y = blocks_[0].y();

    for (const QPoint& pt : blocks_) {
        min_x = std::min(min_x, pt.x());
        max_x = std::max(max_x, pt.x());
        min_y = std::min(min_y, pt.y());
        max_y = std::max(max_y, pt.y());
    }

    return QRect(min_x, min_y, max_x - min_x + 1, max_y - min_y + 1);
}

/**
 * @brief Creates a deep copy of this shape
 * @return Pointer to a new Shape instance with the same properties
 */
Shape* Shape::Clone() const {
    return new Shape(shape_id_ ,blocks_, name_);
}

void Shape::SetID(int id){
    shape_id_ = id;
}
