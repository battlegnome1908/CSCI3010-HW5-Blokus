/**
 * @file board.cpp
 * @brief Implementation of the Board class for the Blokus game
 */
#include "board.h"

/**
 * @brief Constructs a new Board with specified dimensions
 * @param rows Number of rows in the board
 * @param cols Number of columns in the board
 */
Board::Board(int rows, int cols)
    : rows_(rows), cols_(cols), grid_(rows, QVector<Cell>(cols)) {}

/**
 * @brief Checks if a cell at the specified position is occupied
 * @param row Row index of the cell
 * @param col Column index of the cell
 * @return true if the cell is occupied, false otherwise
 */
bool Board::IsCellOccupied(int row, int col) const {
    return grid_[row][col].occupied;
}

/**
 * @brief Gets the color of a cell at the specified position
 * @param row Row index of the cell
 * @param col Column index of the cell
 * @return QColor of the cell
 */
QColor Board::GetCellColor(int row, int col) const {
    return grid_[row][col].color;
}

/**
 * @brief Checks if a shape can be legally placed at the specified position
 * @param shape Pointer to the Shape to be placed
 * @param topLeft Top-left position where the shape would be placed
 * @param pid Player ID attempting to place the shape
 * @param is_first_move Whether this is the player's first move
 * @return true if the shape can be placed, false otherwise
 */
bool Board::CanPlaceShape(const Shape* shape, const QPoint& topLeft, int pid, bool is_first_move) const {
    if (is_first_move) {
        return true;  // first placement allowed anywhere (still has to be legal)
    }

    bool touches_corner = false;

    for (const QPoint& offset : shape->Blocks()) {
        int row = topLeft.y() + offset.y();
        int col = topLeft.x() + offset.x();

        // Bounds check
        if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
            return false;

        // Overlap check
        if (grid_[row][col].occupied)
            return false;

        // Adjacent edge (orthogonal) check — must not touch
        static const QVector<QPoint> edges = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
        for (const QPoint& dir : edges) {
            int r = row + dir.y();
            int c = col + dir.x();
            if (r >= 0 && r < rows_ && c >= 0 && c < cols_) {
                if (grid_[r][c].pid == pid) {
                    return false; // edge contact not allowed
                }
            }
        }

        // Diagonal check — at least one must match
        static const QVector<QPoint> corners = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };
        for (const QPoint& diag : corners) {
            int r = row + diag.y();
            int c = col + diag.x();
            if (r >= 0 && r < rows_ && c >= 0 && c < cols_) {
                if (grid_[r][c].pid == pid) {
                    touches_corner = true;
                }
            }
        }
    }

    return touches_corner;
}

/**
 * @brief Places a shape on the board at the specified position
 * @param shape Pointer to the Shape to be placed
 * @param topLeft Top-left position where the shape will be placed
 * @param color Color to fill the shape with
 * @param pid Player ID who is placing the shape
 */
void Board::PlaceShape(const Shape* shape, const QPoint& topLeft, const QColor& color, int pid){
    for (const QPoint& offset : shape->Blocks()) {
        int row = topLeft.y() + offset.y();
        int col = topLeft.x() + offset.x();

        grid_[row][col].occupied = true;
        grid_[row][col].color = color;
        grid_[row][col].pid = pid;
        grid_[row][col].shape_id = shape->GetShapeID();
    }
}

/**
 * @brief Removes the piece from cell specified at this row, col
 * @param row The row of the cell to be removed
 * @param col The col of the cell to be removed
 */
void Board::ClearCell(int row, int col) {
    if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
        grid_[row][col].occupied = false;
        grid_[row][col].color = Qt::transparent;
        grid_[row][col].pid = -1;
    }
}

/**
 * @brief Getter for cell pid
 * @param row of desired cell
 * @param col of desired cell
 * @return pid int
 */
int Board::GetCellPID(int row, int col) const {
    return grid_[row][col].pid;
}

/**
 * @brief Getter for shape's pid
 * @param row of desired cell
 * @param col of desired cell
 * @return shape id integer
 */
int Board::GetCellShapeID(int row, int col) const {
    return grid_[row][col].shape_id;
}

/**
 *  @brief Clears out the whole board for a new game.
 */
void Board::Reset() {
    for (int r = 0; r < rows_; ++r) {
        for (int c = 0; c < cols_; ++c) {
            grid_[r][c].occupied = false;
            grid_[r][c].color = Qt::transparent;
            grid_[r][c].pid = -1;
            grid_[r][c].shape_id = -1;
        }
    }
}
