#ifndef PLOTWINDOW_H
#define PLOTWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QVector>
#include <QTimer>
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
    void OnBombPressed();
    void OnMirrorPressed();
    void OnWildPressed();

    void OnEndGamePressed();

public:
    //PlotWindow(QWidget *parent = nullptr); // testing
    PlotWindow(const QVector<QString>& names, const QVector<QColor>& colors, int count, QWidget* parent = nullptr);

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
    void RedrawBoard();
    void PlaceShapeOnBoard(Shape* shape, const QPoint& topLeft, QColor color, int player_id);

    // Helpers
    int GenerateUniqueShapeID();
    QVector<QPoint> FloodFillPiece(int start_r, int start_c, int pid, int sid, QSet<QPair<int, int>>& visited); // prototype pattern
    void UpdateAbilityButtons();
    void HighlightCurrentPlayer();
    void AdvanceTurn();

    // Abilities
        // Bombs
    void HandleBombClick(QMouseEvent* mouse_event);
    void UpdateBombPreview(int center_x, int center_y);
    void BombDetonate(int center_x, int center_y);
        // Copycat
    void HandleMirrorClick(QMouseEvent* mouse_event);

    // TODO: flesh out the wild creation
    // void HandleWildClick(QMouseEvent* mouse_event);

    //Skip
    void OnSkipTurnPressed();

    // End game
    bool AnyPlayerHasAvailableMoves();
    void GameOver();
    void RestartGame();

private:
    Ui::PlotWindow *ui;
    QGraphicsScene *scene_;
    QGraphicsScene *pieces_scene_;
    int rows_ = 20;
    int cols_ = 20;
    int cell_size_;
    QVector<ShapeItem*> board_shape_items_;

    QVector<ShapeItem*> shape_items_;     // all shape buttons in tray
    Shape* selected_shape_ = nullptr;     // current selected shape data
    QColor selected_color_;
    ShapeItem* preview_item_ = nullptr;   // ghost preview on main board

    // Game Setup
    Game * game_;

    // Ability states (put into one place to shunt in PlotWindow::eventFilter() properly
    enum class AbilityMode {
        None,
        Bomb,
        Mirror,
        Wild
    };

    AbilityMode ability_mode_ = AbilityMode::None;

    QGraphicsRectItem* bomb_preview_item_ = nullptr;

};

#endif // PLOTWINDOW_H
