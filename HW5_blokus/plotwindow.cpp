#include <QGraphicsView>
#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QMouseEvent> // for dragndrop
#include <QMessageBox> // for endgame
#include <QGraphicsDropShadowEffect> // for polishing names

#include "plotwindow.h"
#include "ui_plotwindow.h"
#include "shapefactory.h"   // factory design pattern
// #include "shapecreationdialog.h" // if DIY is implemented
#include "shapeitem.h"
#include "game.h"

/** @brief this was used during testing.
 *  Uncommment and change main.cpp to save time on picking player names / colors between tests
 *  This is better commented
 */
/* PlotWindow::PlotWindow(QWidget *parent)
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


    // Abilities
    connect(ui->bombPushButton, &QPushButton::clicked, this, &PlotWindow::OnBombPressed);
    connect(ui->mirrorPushButton, &QPushButton::clicked, this, &PlotWindow::OnMirrorPressed);
    connect(ui->WildPushButton, &QPushButton::clicked, this, &PlotWindow::OnWildPressed);
    connect(ui->SkipPushButton, &QPushButton::clicked, this, &PlotWindow::OnSkipTurnPressed);
    connect(ui->EndGamePushButton, &QPushButton::clicked, this, &PlotWindow::OnEndGamePressed);

}
*/

PlotWindow::PlotWindow(const QVector<QString>& names, const QVector<QColor>& colors, int count, QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::PlotWindow)
{
    ui->setupUi(this);

    ui->boardGraphicsView->setRenderHint(QPainter::Antialiasing);
    scene_ = new QGraphicsScene;
    pieces_scene_ = new QGraphicsScene(this);
    cell_size_ = 32;
    rows_ = 20;
    cols_ = 20;

    // Create scene background
    const float board_width = rows_ * cell_size_;
    const float board_height = cols_ * cell_size_;
    QRadialGradient glow(board_width / 2, board_height / 2, board_width * 0.75);
    glow.setColorAt(0.0, QColor(120, 0, 75, 220));
    glow.setColorAt(0.75, QColor(20, 0, 20));
    scene_->setBackgroundBrush(QBrush(glow));

    ui->boardGraphicsView->setScene(scene_);
    ui->piecesGraphicsView->setScene(pieces_scene_);
    ui->piecesGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->piecesGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Create shapes + players
    QVector<Shape*> shape_pool = ShapeFactory::PremadeShapes();
    game_ = new Game(this);

    for (int i = 0; i < count; ++i) {
        Player* player = new Player(i + 1, names[i], colors[i], shape_pool);
        game_->AddPlayer(player);
    }
    // if less than 4 players
    AdjustVisiblePlayers(game_->GetAllPlayers().size());
    if (count >= 1) ui->p1nameLabel->setText(names[0]);
    if (count >= 2) ui->p2nameLabel->setText(names[1]);
    if (count >= 3) ui->p3nameLabel->setText(names[2]);
    if (count >= 4) ui->p4nameLabel->setText(names[3]);

    DisplayAvailableShapes(game_->GetCurrentPlayer()->GetRemainingShapes(), game_->GetCurrentPlayer()->GetColor());
    HighlightCurrentPlayer();
    UpdateAbilityButtons();

    ui->boardGraphicsView->viewport()->setMouseTracking(true);
    ui->boardGraphicsView->viewport()->installEventFilter(this);

    // Connect buttons
    connect(ui->bombPushButton, &QPushButton::clicked, this, &PlotWindow::OnBombPressed);
    connect(ui->mirrorPushButton, &QPushButton::clicked, this, &PlotWindow::OnMirrorPressed);
    connect(ui->WildPushButton, &QPushButton::clicked, this, &PlotWindow::OnWildPressed);
    connect(ui->SkipPushButton, &QPushButton::clicked, this, &PlotWindow::OnSkipTurnPressed);
    connect(ui->EndGamePushButton, &QPushButton::clicked, this, &PlotWindow::OnEndGamePressed);

    DrawGrid(rows_, cols_, cell_size_);
    UpdateAbilityButtons();
    HighlightCurrentPlayer();
}


PlotWindow::~PlotWindow() {
    delete ui;
}

void PlotWindow::PlaceShapeOnBoard(Shape* shape, const QPoint& topLeft, QColor color, int /*player_id*/) {
    // Create a new ShapeItem to represent the entire piece
    ShapeItem* placed_item = new ShapeItem(shape, color, cell_size_);

    placed_item->setPos(10 + topLeft.x() * cell_size_, 10 + topLeft.y() * cell_size_);
    placed_item->setZValue(20);
    scene_->addItem(placed_item);
    board_shape_items_.append(placed_item);
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

/**
 * @brief The "guts"
 * @param obj which obj is being focused on
 * @param event which event is being run (mouse click / move / keys )
 * @return
 */
bool PlotWindow::eventFilter(QObject* obj, QEvent* event) {

    // For mouse movement
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        QPointF scene_pos = ui->boardGraphicsView->mapToScene(mouse_event->pos());

        // Ignore movement outside the board
        int grid_x = static_cast<int>((scene_pos.x() - 10) / cell_size_);
        int grid_y = static_cast<int>((scene_pos.y() - 10) / cell_size_);
        if (grid_x < 0 || grid_y < 0 || grid_x >= game_->GetBoard()->Cols() || grid_y >= game_->GetBoard()->Rows()) {
            return false;
        }


        // Check if the player is currently using ability
        if (ability_mode_ == AbilityMode::Bomb) {
            int grid_x = static_cast<int>((scene_pos.x() - 10) / cell_size_);
            int grid_y = static_cast<int>((scene_pos.y() - 10) / cell_size_);
            UpdateBombPreview(grid_x, grid_y);
            return false;
        }else if (ability_mode_ == AbilityMode::Mirror) {
            // Clear previous highlights
            for (ShapeItem* item : board_shape_items_) {
                item->SetHighlighted(false);
            }

            // Find if hovering over any board shape
            QList<QGraphicsItem*> items = scene_->items(scene_pos);
            for (QGraphicsItem* item : items) {
                ShapeItem* shape_item = dynamic_cast<ShapeItem*>(item);
                if (shape_item && board_shape_items_.contains(shape_item)) {
                    shape_item->SetHighlighted(true);
                    break;
                }
            }
            return false;
        }

        if (preview_item_) {
            int snapped_x = 10 + static_cast<int>(scene_pos.x() / cell_size_) * cell_size_;
            int snapped_y = 10 + static_cast<int>(scene_pos.y() / cell_size_) * cell_size_;
            preview_item_->setPos(snapped_x, snapped_y);
            return false;
        }
    }

    if (event->type() == QEvent::MouseButtonPress) {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        QPointF scene_pos = ui->boardGraphicsView->mapToScene(mouse_event->pos());

        if (mouse_event->button() == Qt::RightButton) {
            if (ability_mode_ != AbilityMode::None) {
                ability_mode_ = AbilityMode::None;
                ui->boardGraphicsView->viewport()->unsetCursor();
                qDebug() << "Ability canceled by right-click.";
                return true;
            }
            else if (preview_item_) {
                // If we are placing a previewed shape (Mirror copy), cancel that too
                scene_->removeItem(preview_item_);
                delete preview_item_;
                preview_item_ = nullptr;
                ui->boardGraphicsView->viewport()->unsetCursor();
                qDebug() << "Preview canceled by right-click.";
                return true;
            }
        }

        if (ability_mode_ == AbilityMode::Bomb) {
            HandleBombClick(mouse_event);
            return true;
        }
        else if (ability_mode_ == AbilityMode::Mirror) {
            HandleMirrorClick(mouse_event);
            return true;
        }
        else if (ability_mode_ == AbilityMode::Wild) {
            //HandleWildClick(mouse_event);
            return true;
        }
        else if (preview_item_) {
            if (mouse_event->button() == Qt::LeftButton) {
                int grid_x = static_cast<int>((scene_pos.x() - 10) / cell_size_);
                int grid_y = static_cast<int>((scene_pos.y() - 10) / cell_size_);
                QPoint topLeft(grid_x, grid_y);

                Player* current = game_->GetCurrentPlayer();
                bool is_first_move = (current->GetPlacedCount() == 0);

                if (game_->GetBoard()->CanPlaceShape(preview_item_->GetShape(), topLeft, current->GetPID(), is_first_move)) {
                    game_->GetBoard()->PlaceShape(preview_item_->GetShape(), topLeft, current->GetColor(), current->GetPID());
                    current->MarkPlaced();

                    // ShapeItem* placed = new ShapeItem(preview_item_->GetShape(), current->GetColor(), cell_size_);
                    // placed->setPos(10 + topLeft.x() * cell_size_, 10 + topLeft.y() * cell_size_);
                    // scene_->addItem(placed);
                    PlaceShapeOnBoard(preview_item_->GetShape(), topLeft, current->GetColor(), current->GetPID());


                    current->removeRemainingByID(preview_item_->GetShape()->GetShapeID());
                    current->addPlaced(preview_item_->GetShape());

                    scene_->removeItem(preview_item_);
                    delete preview_item_;
                    preview_item_ = nullptr;

                    if (ability_mode_ == AbilityMode::None && selected_shape_) {
                        if (selected_shape_->Name() == "WildShape") {
                            current->setWild(false);
                        } else if (selected_shape_->Name() == "Mirror") {
                            current->setMirror(false);
                        }
                    }

                    ui->boardGraphicsView->viewport()->unsetCursor();

                    // Advance to next player
                    AdvanceTurn();
                }
                return true;
            }
        }
    }

    return QMainWindow::eventFilter(obj, event);
}


/**
 * @brief handles "extra" consequences like exiting out of abilities meaning rever cursor / removing preview
 * @param event Which event was triggered
 */
void PlotWindow::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Escape) {
        if (ability_mode_ != AbilityMode::None) {
            ability_mode_ = AbilityMode::None;
            ui->boardGraphicsView->viewport()->unsetCursor();
            qDebug() << "Ability canceled by Escape key.";
            return;
        }
    }

    // Existing shape preview rotation
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
        ui->p4line->hide();
    }
    if (player_count < 3) {
        ui->p3label->hide();
        ui->p3nameLabel->hide();
        ui->placedLabel_3->hide();
        ui->remainingLabel_3->hide();
        ui->p3line->hide();
    }
}

void PlotWindow::OnBombPressed() {
    qDebug() << "Bomb ability used!";
    Player* current = game_->GetCurrentPlayer();
    if (!current->GetBomb()) {
        qDebug() << "Bomb already used!";
        return;
    }

    ability_mode_ = AbilityMode::Bomb;
    ui->boardGraphicsView->viewport()->setCursor(Qt::CrossCursor);  // change cursor to crosshair
    qDebug() << "Bomb mode activated! Click a spot to detonate.";
}

void PlotWindow::OnMirrorPressed() {
    qDebug() << "Mirror ability used!";
    Player* current = game_->GetCurrentPlayer();
    if (!current->GetMirror()) {
        qDebug() << "Mirror already used!";
        return;
    }

    ability_mode_ = AbilityMode::Mirror;
    ui->boardGraphicsView->viewport()->setCursor(Qt::PointingHandCursor);  // or CrossCursor
    qDebug() << "Mirror mode activated! Hover over a placed shape to copy.";
}


void PlotWindow::OnWildPressed() {
    qDebug() << "Design Your Own ability used!";
    // Future: Let the player create a new custom shape
}

void PlotWindow::HandleBombClick(QMouseEvent* mouse_event) {
    if (mouse_event->button() != Qt::LeftButton) return;

    QPointF scene_pos = ui->boardGraphicsView->mapToScene(mouse_event->pos());
    int grid_x = static_cast<int>((scene_pos.x() - 10) / cell_size_);
    int grid_y = static_cast<int>((scene_pos.y() - 10) / cell_size_);

    // ✅ SAFETY CHECK: Make sure click is inside the board
    if (grid_x < 0 || grid_y < 0 || grid_x >= game_->GetBoard()->Cols() || grid_y >= game_->GetBoard()->Rows()) {
        qDebug() << "Clicked outside board — canceling bomb preview.";

        if (bomb_preview_item_) {
            if (bomb_preview_item_->scene()) {
                scene_->removeItem(bomb_preview_item_);
            }
            delete bomb_preview_item_;
            bomb_preview_item_ = nullptr;
        }

        ability_mode_ = AbilityMode::None;
        ui->boardGraphicsView->viewport()->unsetCursor();
        return;
    }

    // 🧨 Normal bomb detonation flash
    const float preview_size = cell_size_ * 3;
    const float offset_x = 10 + (grid_x - 1) * cell_size_;
    const float offset_y = 10 + (grid_y - 1) * cell_size_;

    QGraphicsRectItem* flash_rect = scene_->addRect(offset_x, offset_y, preview_size, preview_size,
                                                    QPen(Qt::red, 3), QBrush(QColor(255,0,0,200)));
    flash_rect->setZValue(100);  // On top of everything

    // Remove bomb preview
    if (bomb_preview_item_) {
        if (bomb_preview_item_->scene()) {
            scene_->removeItem(bomb_preview_item_);
        }
        delete bomb_preview_item_;
        bomb_preview_item_ = nullptr;
    }

    // Set a timer to remove flash and actually explode
    QTimer::singleShot(600, this, [=]() {
        if (flash_rect->scene()) {
            scene_->removeItem(flash_rect);
        }
        delete flash_rect;

        BombDetonate(grid_x, grid_y);
    });
}

void PlotWindow::BombDetonate(int center_x, int center_y) {
    QSet<QPair<int, int>> affected_shapes;

    // 1. Detonate 3x3
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int r = center_y + dy;
            int c = center_x + dx;

            if (r >= 0 && r < game_->GetBoard()->Rows() && c >= 0 && c < game_->GetBoard()->Cols()) {
                if (game_->GetBoard()->IsCellOccupied(r, c)) {
                    int pid = game_->GetBoard()->GetCellPID(r, c);
                    int sid = game_->GetBoard()->GetCellShapeID(r, c);
                    affected_shapes.insert(qMakePair(pid, sid));
                }
                game_->GetBoard()->ClearCell(r, c);
            }
        }
    }

    // 2. Check which original pieces are fully destroyed
    for (const auto& pair : affected_shapes) {
        int pid = pair.first;
        int sid = pair.second;

        bool survives = false;
        for (int r = 0; r < game_->GetBoard()->Rows(); ++r) {
            for (int c = 0; c < game_->GetBoard()->Cols(); ++c) {
                if (game_->GetBoard()->IsCellOccupied(r, c) &&
                    game_->GetBoard()->GetCellPID(r, c) == pid &&
                    game_->GetBoard()->GetCellShapeID(r, c) == sid) {
                    survives = true;
                    break;
                }
            }
            if (survives) break;
        }

        if (!survives) {
            Player* p = game_->FindPlayerByPID(pid);
            if (p) {
                p->removePlacedByID(sid);
                qDebug() << "Player" << pid << "'s piece" << sid << "was fully destroyed.";
            }
        }
    }

    // 3. Reset bomb ability and cursor
    game_->GetCurrentPlayer()->setBomb(false);
    ability_mode_ = AbilityMode::None;
    ui->boardGraphicsView->viewport()->unsetCursor();
    if (bomb_preview_item_) {
        if (bomb_preview_item_->scene()) {
            scene_->removeItem(bomb_preview_item_);
        }
        delete bomb_preview_item_;
        bomb_preview_item_ = nullptr;
    }

    // Find + save broken mini-pieces for copying / removing later
    QSet<QPair<int, int>> visited;

    for (int r = 0; r < game_->GetBoard()->Rows(); ++r) {
        for (int c = 0; c < game_->GetBoard()->Cols(); ++c) {
            if (game_->GetBoard()->IsCellOccupied(r, c) && !visited.contains(qMakePair(r, c))) {
                int pid = game_->GetBoard()->GetCellPID(r, c);
                int sid = game_->GetBoard()->GetCellShapeID(r, c);

                // Flood fill the connected piece
                QVector<QPoint> block_offsets = FloodFillPiece(r, c, pid, sid, visited);

                if (!block_offsets.isEmpty()) {
                    Shape* new_shape = new Shape(GenerateUniqueShapeID(), block_offsets, "Fragment");

                    // No adding to remaining shapes!
                    qDebug() << "Bomb created dead fragment for player" << pid;

                    // Still place the debris visually
                    int min_x = INT_MAX, min_y = INT_MAX;
                    for (const QPoint& pt : block_offsets) {
                        min_x = std::min(min_x, pt.x());
                        min_y = std::min(min_y, pt.y());
                    }

                    for (QPoint& pt : block_offsets) {
                        pt.setX(pt.x() - min_x);
                        pt.setY(pt.y() - min_y);
                    }

                    Player* p = game_->FindPlayerByPID(pid);
                    if (p) {
                        PlaceShapeOnBoard(new_shape, QPoint(min_x, min_y), p->GetColor(), pid);
                    }

                    PlaceShapeOnBoard(new_shape, QPoint(min_x, min_y), p->GetColor(), pid);
                }
            }
        }
    }

    // 5. Redraw board
    RedrawBoard();

    // 6. Advance turn
    AdvanceTurn();

    qDebug() << "Bomb detonated and turn advanced.";
}

/**
 * @brief Moves left to right to find any unconnected blocks after bomb ability is used
 *          any pieces found unconnected are made to be their own shape.
 * @param start_r starting row
 * @param start_c starting column
 * @param pid   player id whose pieces are currently searched
 * @param sid   shape id of piece being searched
 * @param visited already checked cells
 * @return
 */
QVector<QPoint> PlotWindow::FloodFillPiece(int start_r, int start_c, int pid, int sid, QSet<QPair<int, int>>& visited) {
    QVector<QPoint> blocks;
    QVector<QPair<int, int>> queue;
    queue.append(qMakePair(start_r, start_c));
    visited.insert(qMakePair(start_r, start_c));

    while (!queue.isEmpty()) {
        auto current = queue.takeFirst();
        int r = current.first;
        int c = current.second;

        blocks.append(QPoint(c, r));  // x = col, y = row

        // Explore 4 directions
        const int dr[] = {-1, 1, 0, 0};
        const int dc[] = {0, 0, -1, 1};

        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (nr >= 0 && nr < game_->GetBoard()->Rows() && nc >= 0 && nc < game_->GetBoard()->Cols()) {
                if (!visited.contains(qMakePair(nr, nc)) &&
                    game_->GetBoard()->IsCellOccupied(nr, nc) &&
                    game_->GetBoard()->GetCellPID(nr, nc) == pid &&
                    game_->GetBoard()->GetCellShapeID(nr, nc) == sid) {

                    queue.append(qMakePair(nr, nc));
                    visited.insert(qMakePair(nr, nc));
                }
            }
        }
    }

    return blocks;
}



void PlotWindow::HandleMirrorClick(QMouseEvent* mouse_event) {
    if (mouse_event->button() != Qt::LeftButton) return;

    QPointF scene_pos = ui->boardGraphicsView->mapToScene(mouse_event->pos());
    QList<QGraphicsItem*> items = scene_->items(scene_pos);

    for (QGraphicsItem* item : items) {
        ShapeItem* shape_item = dynamic_cast<ShapeItem*>(item);
        if (shape_item && board_shape_items_.contains(shape_item)) {
            // clone its shape
            Shape* cloned_shape = shape_item->GetShape()->Clone();
            cloned_shape->SetID(GenerateUniqueShapeID()); // new shape to not overlap

            // new preview item
            if (preview_item_) {
                scene_->removeItem(preview_item_);
                delete preview_item_;
            }

            preview_item_ = new ShapeItem(cloned_shape, game_->GetCurrentPlayer()->GetColor(), cell_size_);
            preview_item_->SetPreviewMode(true);
            preview_item_->setZValue(100);
            scene_->addItem(preview_item_);

            selected_shape_ = cloned_shape;
            selected_color_ = game_->GetCurrentPlayer()->GetColor();

            // Exit Mirror mode
            ability_mode_ = AbilityMode::None;

            // set cursor to Blank
            ui->boardGraphicsView->viewport()->setCursor(Qt::BlankCursor);

            qDebug() << "Mirror: Shape copied! Now place it.";
            // clear all highlights after selecting a shape
            for (ShapeItem* item : board_shape_items_) {
                item->SetHighlighted(false);
            }

            return;
        }
    }
}

// TODO: implement
// void PlotWindow::HandleWildClick(QMouseEvent* mouse_event) {
//     if (mouse_event->button() != Qt::LeftButton) return;

//     ShapeCreationDialog dialog(this);

//     if (dialog.exec() == QDialog::Accepted) {
//         QVector<QPoint> blocks = dialog.GetSelectedBlocks();

//         if (blocks.size() == 5) {
//             Shape* custom_shape = new Shape(GenerateUniqueShapeID(), blocks, "WildShape");

//             Player* current = game_->GetCurrentPlayer();

//             preview_item_ = new ShapeItem(custom_shape, current->GetColor(), cell_size_);
//             preview_item_->SetPreviewMode(true);
//             preview_item_->setZValue(100);
//             scene_->addItem(preview_item_);

//             selected_shape_ = custom_shape;
//             selected_color_ = current->GetColor();

//             ability_mode_ = AbilityMode::None;
//             ui->boardGraphicsView->viewport()->setCursor(Qt::BlankCursor);

//             current->setWild(false); // Use up Wild ability
//         }
//     }
// }


void PlotWindow::UpdateBombPreview(int center_x, int center_y) {
    if (bomb_preview_item_) {
        scene_->removeItem(bomb_preview_item_);
        delete bomb_preview_item_;
        bomb_preview_item_ = nullptr;
    }

    const float preview_size = cell_size_ * 3;
    const float offset_x = 10 + (center_x - 1) * cell_size_;
    const float offset_y = 10 + (center_y - 1) * cell_size_;

    bomb_preview_item_ = scene_->addRect(offset_x, offset_y, preview_size, preview_size,
                                         QPen(Qt::red), QBrush(QColor(255,0,0,50)));
    bomb_preview_item_->setZValue(50); // Put it above grid
}

void PlotWindow::RedrawBoard() {
    // Remove all items (except background tiles)
    QList<QGraphicsItem*> items = scene_->items();
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<QGraphicsPixmapItem*>(item)) continue;
        scene_->removeItem(item);
        delete item;
    }

    board_shape_items_.clear();

    // Redraw all surviving ShapeItems based on the board state
    for (int r = 0; r < game_->GetBoard()->Rows(); ++r) {
        for (int c = 0; c < game_->GetBoard()->Cols(); ++c) {
            if (game_->GetBoard()->IsCellOccupied(r, c)) {
                int pid = game_->GetBoard()->GetCellPID(r, c);
                Player* player = game_->FindPlayerByPID(pid);
                if (player) {
                    QColor color = player->GetColor();

                    // Create a dummy single-block Shape
                    QVector<QPoint> block;
                    block.append(QPoint(0, 0));
                    Shape* temp_shape = new Shape(GenerateUniqueShapeID(), block, "RegenBlock");

                    // Place at correct grid cell
                    PlaceShapeOnBoard(temp_shape, QPoint(c, r), color, pid);

                    // Note: there's a small amount of Shape memory leak here
                }
            }
        }
    }
}


/**
 * @brief returns a new shape id for creation / copying shapes
 * @return new shape id
 */
int PlotWindow::GenerateUniqueShapeID() {
    static int next_id = 1000; // would not do to save mem if >10 shapes. here we have a max of 8
    return next_id++;
}

void PlotWindow::UpdateAbilityButtons() {
    Player* current = game_->GetCurrentPlayer();

    if (current->GetBomb()) {
        ui->bombPushButton->setEnabled(true);
        ui->bombPushButton->setStyleSheet("");
    } else {
        ui->bombPushButton->setEnabled(false);
        ui->bombPushButton->setStyleSheet("color: gray;");
    }

    if (current->GetMirror()) {
        ui->mirrorPushButton->setEnabled(true);
        ui->mirrorPushButton->setStyleSheet("");
    } else {
        ui->mirrorPushButton->setEnabled(false);
        ui->mirrorPushButton->setStyleSheet("color: gray;");
    }

    // TODO: Same idea for Wild ability
    // if (current->GetWild())...
}

void PlotWindow::HighlightCurrentPlayer() {
    int current_pid = game_->GetCurrentPlayer()->GetPID();

    // List of all player labels
    QVector<QLabel*> nameLabels = {
        ui->p1nameLabel,
        ui->p2nameLabel,
        ui->p3nameLabel,
        ui->p4nameLabel
    };

    for (int i = 0; i < nameLabels.size(); ++i) {
        QLabel* label = nameLabels[i];
        if (!label) continue; // skip nulls

        if (i == current_pid - 1) { // current player's label
            QColor color = game_->GetCurrentPlayer()->GetColor();
            QString styletext = "font-weight: bold; color: " + color.name() + ";";
            label->setStyleSheet(styletext);

            // Add glow effect
            QGraphicsDropShadowEffect* glow = new QGraphicsDropShadowEffect(this);
            glow->setColor(Qt::white);// white glow
            glow->setBlurRadius(10);
            glow->setOffset(0); // centering
            label->setGraphicsEffect(glow);
        } else {
            label->setStyleSheet("font-weight: normal; color: grey;");

            // Remove any old glow effect
            label->setGraphicsEffect(nullptr);
        }
    }

}

void PlotWindow::AdvanceTurn() {
    game_->NextTurn();

    if (!AnyPlayerHasAvailableMoves()) {
        GameOver();
        return;
    }

    Player* next = game_->GetCurrentPlayer();
    DisplayAvailableShapes(next->GetRemainingShapes(), next->GetColor());
    UpdatePlayerStats(next->GetPID(), next);
    UpdateAbilityButtons();
    HighlightCurrentPlayer();
}


bool PlotWindow::AnyPlayerHasAvailableMoves() {
    const QVector<Player*>& players = game_->GetAllPlayers();

    for (Player* player : players) {
        // Check for abilities
        if (player->GetBomb() || player->GetMirror()) return true;
        // Check each of their remaining shapes
        for (Shape* shape : player->GetRemainingShapes()) {
            for (int r = 0; r < game_->GetBoard()->Rows(); ++r) {
                for (int c = 0; c < game_->GetBoard()->Cols(); ++c) {
                    QPoint topLeft(c, r);

                    bool is_first_move = (player->GetPlacedCount() == 0);

                    if (game_->GetBoard()->CanPlaceShape(shape, topLeft, player->GetPID(), is_first_move)) {
                        return true;  // found a legal move!
                    }
                }
            }
        }
    }

    return false;  // no moves left for anyone
}


void PlotWindow::GameOver() {
    // Disable gameplay
    ui->bombPushButton->setEnabled(false);
    ui->mirrorPushButton->setEnabled(false);
    ui->WildPushButton->setEnabled(false);
    ui->SkipPushButton->setEnabled(false);
    ui->EndGamePushButton->setEnabled(false);
    ability_mode_ = AbilityMode::None;
    if (preview_item_) {
        scene_->removeItem(preview_item_);
        delete preview_item_;
        preview_item_ = nullptr;
    }
    ui->boardGraphicsView->viewport()->unsetCursor();

    // Calculate final scores
    QVector<Player*> players = game_->GetAllPlayers();

    std::sort(players.begin(), players.end(), [](Player* a, Player* b) {
        return a->GetPlacedCount() > b->GetPlacedCount();
    });

    QString message;
    if (!players.isEmpty()) {
        message += "Winner! \t" + players[0]->GetName() + "\t Score:\t " + QString::number(players[0]->GetPlacedCount()) + "\n";
    }
    if (players.size() >= 2) {
        message += "Second: \t" + players[1]->GetName() + "\t Score:\t " + QString::number(players[1]->GetPlacedCount()) + "\n";
    }
    if (players.size() >= 3) {
        message += "Third: \t\t" + players[2]->GetName() + "\t Score:\t " + QString::number(players[2]->GetPlacedCount()) + "\n";
    }
    if (players.size() >= 4) {
        message += "Fourth: \t" + players[3]->GetName() + "\t Score:\t " + QString::number(players[3]->GetPlacedCount()) + "\n";
    }

    // Show final scores first
    QMessageBox::information(this, "Game Over", message);

    // Then offer Play Again or Quit
    QMessageBox::StandardButton choice;
    choice = QMessageBox::question(this, "Play Again?",
                                   "Would you like to start a new game?",
                                   QMessageBox::Yes | QMessageBox::No);

    if (choice == QMessageBox::Yes) {
        RestartGame();
    } else {
        QApplication::quit();
    }
}


void PlotWindow::OnSkipTurnPressed() {
    qDebug() << "Player skipped turn.";

    // Cancel any active ability or preview
    ability_mode_ = AbilityMode::None;
    if (preview_item_) {
        scene_->removeItem(preview_item_);
        delete preview_item_;
        preview_item_ = nullptr;
    }
    ui->boardGraphicsView->viewport()->unsetCursor();

    AdvanceTurn();
}

void PlotWindow::OnEndGamePressed() {
    qDebug() << "End Game button pressed.";

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm End Game",
                                  "Are you sure you want to end the game now?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        GameOver();
    } else {
        qDebug() << "End Game canceled.";
    }
}


void PlotWindow::RestartGame() {
    qDebug() << "Restarting game...";

    // Clear visuals
    QList<QGraphicsItem*> items = scene_->items();
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<QGraphicsPixmapItem*>(item)) continue;
        scene_->removeItem(item);
        delete item;
    }
    board_shape_items_.clear();
    if (preview_item_) {
        delete preview_item_;
        preview_item_ = nullptr;
    }

    // Reset the logical game state
    game_->Reset();

    // Rebuild GUI
    RedrawBoard();
    DisplayAvailableShapes(game_->GetCurrentPlayer()->GetRemainingShapes(), game_->GetCurrentPlayer()->GetColor());
    UpdatePlayerStats(game_->GetCurrentPlayer()->GetPID(), game_->GetCurrentPlayer());
    UpdateAbilityButtons();
    HighlightCurrentPlayer();

    qDebug() << "New game ready!";
}
