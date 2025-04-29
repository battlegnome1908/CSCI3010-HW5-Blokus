/**
 * @file game.cpp
 * @brief Implementation of the Game class for managing Blokus game state
 */
#include "game.h"
#include "shapefactory.h"
#include <QDebug>

/**
 * @brief Constructs a new Game instance
 * @param parent Parent QObject for memory management
 */
Game::Game(QObject* parent)
    : QObject(parent), current_player_index_(0), turn_count_(0)
{
    board_ = new Board(20,20);
}

/**
 * @brief Adds a player to the game
 * @param player Pointer to the Player to be added
 */
void Game::AddPlayer(Player* p) {
    players_.append(p);
    num_players_++;
    qDebug() << "Player: " << p->GetPID() << " name: " << p->GetName() << " color: " << p->GetColor();
}

/**
 * @brief Gets the current active player
 * @return Pointer to the current Player, nullptr if no players exist
 */
Player* Game::GetCurrentPlayer() const {
    if (players_.isEmpty()) return nullptr;
    return players_[current_player_index_];
}

/**
 * @brief Advances the game to the next player's turn
 * Increments turn count and updates current player index
 */
void Game::NextTurn() {
    if (players_.isEmpty()) return;

    current_player_index_ = (current_player_index_ + 1) % players_.size();
    ++turn_count_;

    emit PlayerChanged(GetCurrentPlayer());
}

/**
 * @brief Returns the player associated with pid
 * @param pid player id to return
 * @return a player object associated with the pid
 */
Player* Game::FindPlayerByPID(int pid) const {
    for (Player* player : players_) {
        if (player->GetPID() == pid) return player;
    }
    return nullptr;
}

/**
 * @brief resets the entire game.
 */
void Game::Reset() {
    // Clear existing players
    for (Player* player : players_) {
        delete player;
    }
    players_.clear();

    // Reset the board
    board_->Reset();

    // Recreate players
    int num_players = num_players_;
    QVector<Shape*> shape_pool = ShapeFactory::PremadeShapes();
    for (int i = 0; i < num_players; ++i) {
        QString name = "Player " + QString::number(i + 1);
        Player* player = new Player(i + 1, name, GetDefaultColor(i), shape_pool);
        players_.append(player);
    }

    current_player_index_ = 0;
}

/**
 * @brief Default colors to set players to upon a restart
 * @param index the index of the player
 * @return
 */
QColor Game::GetDefaultColor(int index) const {
    static QVector<QColor> colors = {
        Qt::red,
        Qt::blue,
        Qt::green,
        Qt::yellow
    };

    if (index >= 0 && index < colors.size()) {
        return colors[index];
    } else {
        return Qt::black; // fallback color for errors
    }
}
