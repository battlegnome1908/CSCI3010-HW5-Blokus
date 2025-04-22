#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVector>
#include "shapeitem.h"
#include "shape.h"
#include "game.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class PlotWindow;
}
QT_END_NAMESPACE

class PlotWindow : public QMainWindow {
    Q_OBJECT

private slots:

public:
    PlotWindow(QWidget *parent = nullptr);
    ~PlotWindow();

    // Interactables
    void OnShapeSelected(Shape* shape, QColor color);
    bool eventFilter(QObject* obj, QEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    // GUI
    void UpdatePlayerStats(int player_index, const Player* player);
    void DrawGrid(int rows, int cols, float cell_size);
    void DisplayAvailableShapes(const QVector<Shape*>& shapes, QColor color);
    void AdjustVisiblePlayers(int player_count);


private:
    Ui::PlotWindow *ui;
    QGraphicsScene *scene_;
    QGraphicsScene *pieces_scene_;
    int rows_ = 20;
    int cols_ = 20;
    int cell_size_;

    QVector<ShapeItem*> shape_items_;     // all shape buttons in tray
    Shape* selected_shape_ = nullptr;     // current selected shape data
    QColor selected_color_;
    ShapeItem* preview_item_ = nullptr;   // ghost preview on main board

    // Game Setup
    Game * game_;
};

#endif // PLOTWINDOW_H
