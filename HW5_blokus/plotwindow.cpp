#include <QGraphicsView>
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QMouseEvent> // for dragndrop

#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "shapefactory.h"
#include "shapeitem.h"
#include "game.h"


PlotWindow::PlotWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlotWindow)
{
    ui->setupUi(this);

    ui->boardGraphicsView->setRenderHint(QPainter::Antialiasing);
    scene_ = new QGraphicsScene;
    cell_size_ = 32;

    const float board_width = rows_ * cell_size_;
    const float board_height = cols_ * cell_size_;

    // Adding graphics
    QRadialGradient glow(board_width / 2, board_height / 2, board_width * 0.75);
    glow.setColorAt(0.0, QColor(120, 0, 75, 220));
    glow.setColorAt(0.75, QColor(20, 0, 20));
    scene_->setBackgroundBrush(QBrush(glow));
    ui->boardGraphicsView->setScene(scene_);
    DrawGrid(20, 20, cell_size_);

    pieces_scene_ = new QGraphicsScene(this);
    ui->piecesGraphicsView->setScene(pieces_scene_);
    ui->piecesGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->piecesGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // QVector<Shape*> test_shapes = ShapeFactory::PremadeShapes();
    // QColor test_color = QColor(0, 255, 255);

    // initializing game
    QVector<Shape*> shape_pool = ShapeFactory::PremadeShapes();

    game_ = new Game(this);

    Player* p1 = new Player(1, "Name1 test", Qt::cyan, shape_pool);
    Player* p2 = new Player(2, "Name2 test", Qt::yellow, shape_pool);
    Player* p3 = nullptr;
    Player* p4 = nullptr;

    game_->AddPlayer(p1);
    game_->AddPlayer(p2);

    AdjustVisiblePlayers(game_->GetAllPlayers().size());


    // For now, just display the current player's tray
    DisplayAvailableShapes(p1->GetRemainingShapes(), p1->GetColor());

    DrawGrid(rows_,cols_,cell_size_);
    //DisplayAvailableShapes(test_shapes, test_color);

    ui->boardGraphicsView->viewport()->setMouseTracking(true);
    ui->boardGraphicsView->viewport()->installEventFilter(this);

    // Updating player info
    UpdatePlayerStats(1, p1);
    UpdatePlayerStats(2, p2);
    if (game_->GetAllPlayers().size() > 2) UpdatePlayerStats(3, p3);
    if (game_->GetAllPlayers().size() > 3) UpdatePlayerStats(4, p4);
}

PlotWindow::~PlotWindow() {
    delete ui;
}

void PlotWindow::DrawGrid(int rows, int cols, float cell_size) {
    const float outer_margin = 10.0f;
    const float tile_gap = 2.0f;
    const float tile_size = cell_size - tile_gap;

    QPixmap tile_pix(":/assets/blankbutton.png");
    tile_pix = tile_pix.scaled(tile_size, tile_size, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = outer_margin + col * cell_size + tile_gap / 2.0f;
            float y = outer_margin + row * cell_size + tile_gap / 2.0f;
            QGraphicsPixmapItem* tile = scene_->addPixmap(tile_pix);
            tile->setPos(x, y);
        }
    }

    float total_width = outer_margin * 2 + cols * cell_size;
    float total_height = outer_margin * 2 + rows * cell_size;
    scene_->setSceneRect(0, 0, total_width, total_height);
    ui->boardGraphicsView->setFixedSize(total_width + 20, total_height + 20);
}

void PlotWindow::DisplayAvailableShapes(const QVector<Shape*>& shapes, QColor color) {
    pieces_scene_->clear();
    shape_items_.clear();

    const float cell_size = 24.0f;
    const float spacing = 10.0f;
    float x = 0;

    for (Shape* shape : shapes) {
        ShapeItem* item = new ShapeItem(shape, color, cell_size);
        item->setPos(x, 0);
        connect(item, &ShapeItem::ShapeClicked, this, &PlotWindow::OnShapeSelected);
        pieces_scene_->addItem(item);
        shape_items_.append(item);
        x += cell_size * 5 + spacing;
    }

    pieces_scene_->setSceneRect(0, 0, x, cell_size * 5);
}

void PlotWindow::OnShapeSelected(Shape* shape, QColor color) {
    for (ShapeItem* item : shape_items_) {
        item->SetHighlighted(item->GetShape() == shape);
    }

    if (preview_item_) {
        scene_->removeItem(preview_item_);
        delete preview_item_;
        preview_item_ = nullptr;
    }

    Shape* cloned = shape->Clone();
    preview_item_ = new ShapeItem(cloned, color, cell_size_);

    preview_item_->SetPreviewMode(true);
    preview_item_->setZValue(100);
    scene_->addItem(preview_item_);
    ui->boardGraphicsView->viewport()->setCursor(Qt::BlankCursor);
}

bool PlotWindow::eventFilter(QObject* obj, QEvent* event) {
    // Preview placement
    if (event->type() == QEvent::MouseMove && preview_item_) {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        QPointF scene_pos = ui->boardGraphicsView->mapToScene(mouse_event->pos());

        int snapped_x = 10+static_cast<int>(scene_pos.x() / cell_size_) * cell_size_;
        int snapped_y = 10+static_cast<int>(scene_pos.y() / cell_size_) * cell_size_;
        preview_item_->setPos(snapped_x, snapped_y);
        return false;
    }

    // Click to place:
    if (event->type() == QEvent::MouseButtonPress && preview_item_) {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        if (mouse_event->button() == Qt::LeftButton) {
            QPointF scene_pos = ui->boardGraphicsView->mapToScene(mouse_event->pos());

            // Grid position (remove margin)
            int grid_x = static_cast<int>((scene_pos.x() - 10) / cell_size_);
            int grid_y = static_cast<int>((scene_pos.y() - 10) / cell_size_);
            QPoint topLeft(grid_x, grid_y);


            Player* current = game_->GetCurrentPlayer();

            bool is_first_move = (current->GetPlacedCount() == 0);
            if (game_->GetBoard()->CanPlaceShape(preview_item_->GetShape(), topLeft, current->GetPID(), is_first_move)){
                game_->GetBoard()->PlaceShape(preview_item_->GetShape(), topLeft, current->GetColor(), current->GetPID());
                current->MarkPlaced();

                ShapeItem* placed = new ShapeItem(preview_item_->GetShape(), current->GetColor(), cell_size_);
                placed->setPos(10 + topLeft.x() * cell_size_, 10 + topLeft.y() * cell_size_);
                scene_->addItem(placed);
                qDebug() << "Placing " << current->GetColor() << " at " << grid_x << "x" << grid_y;
                current->removeRemainingByID(preview_item_->GetShape()->GetID());
                current->addPlaced(preview_item_->GetShape());

                scene_->removeItem(preview_item_);
                delete preview_item_;
                preview_item_ = nullptr;

                ui->boardGraphicsView->viewport()->unsetCursor();

                // Advance to next player
                game_->NextTurn();
                Player* next = game_->GetCurrentPlayer();

                // Show their pieces in the tray
                DisplayAvailableShapes(next->GetRemainingShapes(), next->GetColor());
                UpdatePlayerStats(next->GetPID(), next);

            }
            return true;
        }
    }

    return QMainWindow::eventFilter(obj, event);
}


void PlotWindow::keyPressEvent(QKeyEvent* event) {
    if (preview_item_ && event->key() == Qt::Key_R) {
        preview_item_->RotateCW();
    }
}

void PlotWindow::wheelEvent(QWheelEvent* event) {
    if (preview_item_) {
        preview_item_->RotateCW();  // clockwise for now
        event->accept();
    }
    qDebug() << "Rotating";
}


void PlotWindow::UpdatePlayerStats(int player_index, const Player* player) {
    if (!player) return;

    QLabel* nameLabel = nullptr;
    QLabel* placedLabel = nullptr;
    QLabel* remainingLabel = nullptr;

    switch (player_index) {
    case 1:
        nameLabel = ui->p1nameLabel;
        placedLabel = ui->placedLabel;
        remainingLabel = ui->remainingLabel;
        break;
    case 2:
        nameLabel = ui->p2nameLabel;
        placedLabel = ui->placedLabel_2;
        remainingLabel = ui->remainingLabel_2;
        break;
    case 3:
        nameLabel = ui->p3nameLabel;
        placedLabel = ui->placedLabel_3;
        remainingLabel = ui->remainingLabel_3;
        break;
    case 4:
        nameLabel = ui->p4nameLabel;
        placedLabel = ui->placedLabel_4;
        remainingLabel = ui->remainingLabel_4;
        break;
    }

    if (nameLabel) nameLabel->setText(player->GetName());
    if (placedLabel) placedLabel->setText(QString("Placed: %1").arg(player->GetPlacedCount()));
    if (remainingLabel) remainingLabel->setText(QString("Remaining: %1").arg(player->GetRemainingCount()));
}

void PlotWindow::AdjustVisiblePlayers(int player_count) {
    if (player_count < 4) {
        ui->p4label->hide();
        ui->p4nameLabel->hide();
        ui->placedLabel_4->hide();
        ui->remainingLabel_4->hide();
    }
    if (player_count < 3) {
        ui->p3label->hide();
        ui->p3nameLabel->hide();
        ui->placedLabel_3->hide();
        ui->remainingLabel_3->hide();
    }
}
