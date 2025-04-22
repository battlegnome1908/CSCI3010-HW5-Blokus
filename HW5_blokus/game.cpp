/**
 * @file game.cpp
 * @brief Implementation of the Game class for managing Blokus game state
 */
#include "game.h"
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
