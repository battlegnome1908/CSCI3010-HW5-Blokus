#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QPoint>
#include <QColor>
#include "shape.h"

class Board {
public:
    Board(int rows, int cols);

    int Rows() const { return rows_; }
    int Cols() const { return cols_; }

    bool IsCellOccupied(int row, int col) const;
    QColor GetCellColor(int row, int col) const;

    bool CanPlaceShape(const Shape* shape, const QPoint& topLeft, int player_id, bool is_first_move) const;
    void PlaceShape(const Shape* shape, const QPoint& topLeft, const QColor& color, int player_id);

private:
    struct Cell {
        bool occupied = false;
        QColor color = Qt::transparent;
        int pid = -1; // pid
    };

    int rows_;
    int cols_;
    QVector<QVector<Cell>> grid_;
};

#endif // BOARD_H
