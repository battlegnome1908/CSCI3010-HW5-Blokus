/**
 * @file shapefactory.cpp
 * @brief Implementation of the ShapeFactory class for creating Blokus game pieces
 */
#include "shapefactory.h"

/**
 * @brief Default constructor for ShapeFactory
 */
ShapeFactory::ShapeFactory() {}

/**
 * @brief Creates a vector of predefined shapes used in the Blokus game
 * @return QVector containing pointers to all predefined Shape instances
 */
QVector<Shape*> ShapeFactory::PremadeShapes(){
    QVector<Shape*> shapes;
    shapes.append(new Shape(1, {QPoint(0, 0)}, "Piece-1"));
    shapes.append(new Shape(2, {QPoint(0, 0), QPoint(1, 0)}, "Piece-2"));
    shapes.append(new Shape(3, {QPoint(0, 0), QPoint(1, 0), QPoint(2, 0)}, "Piece-3"));
    shapes.append(new Shape(4, {QPoint(0, 0), QPoint(0, 1), QPoint(1, 0)}, "Piece-4"));

    shapes.append(new Shape(5, {QPoint(0, 0), QPoint(1, 0), QPoint(2, 0), QPoint(3, 0)}, "Piece-5"));   // Piece-5: Line of 4
    shapes.append(new Shape(6, {QPoint(0, 0), QPoint(0, 1), QPoint(0, 2), QPoint(1, 2)}, "Piece-6"));   // Piece-6: 4-block L-shape
    shapes.append(new Shape(7, {QPoint(0, 0), QPoint(1, 0), QPoint(2, 0), QPoint(1, 1)}, "Piece-7"));   // Piece-7: T-shape (4-block)
    shapes.append(new Shape(8, {QPoint(0, 0), QPoint(1, 0), QPoint(0, 1), QPoint(1, 1)}, "Piece-8"));   // Piece-8: Square (2x2)
    shapes.append(new Shape(0, {QPoint(1, 0), QPoint(1, 1), QPoint(0, 1), QPoint(0, 2)}, "Piece-9"));   // Piece-9: Z-4 block

    shapes.append(new Shape(10, {QPoint(0, 0), QPoint(0, 1), QPoint(0, 2), QPoint(0, 3), QPoint(0,4)}, "Piece-10"));    // Piece-10: Vertical Line of 5

    //TODO 11-21

    return shapes;
}
