/**
 * @file player.cpp
 * @brief Implementation of the Player class for managing player state in Blokus
 */
#include "player.h"

/**
 * @brief Constructs a new Player instance
 * @param pid Player's unique identifier
 * @param name Player's display name
 * @param color Player's piece color
 * @param all_shapes Vector of all shapes available to the player
 */
Player::Player(int pid, const QString& name, const QColor& color, const QVector<Shape*> all_shapes)
    : pid_(pid), name_(name), color_(color), remaining_(all_shapes) {}


// Setters and Incrementers
/**
 * @brief Adds a shape to the player's remaining shapes
 * @param new_shape Pointer to the Shape to be added
 */
void Player::addRemaining(Shape* new_shape){
    remaining_.push_back(new_shape);
}

/**
 * @brief Adds a shape to the player's placed shapes
 * @param new_shape Pointer to the Shape to be added
 */
void Player::addPlaced(Shape* new_shape){
    placed_.push_back(new_shape);
}

/**
 * @brief Removes a specific shape from the player's remaining shapes
 * @param x Pointer to the Shape to be removed
 */
void Player::removeRemaining(Shape* x){
    if (!x) return; // null check
    remaining_.removeAll(x);
}


/**
 * @brief Removes a shape from remaining shapes by its ID
 * @param id ID of the shape to be removed
 */
void Player::removeRemainingByID(int id) {
    for (int i = 0; i < remaining_.size(); ++i) {
        if (remaining_[i]->GetShapeID() == id) {
            remaining_.remove(i);
            return;
        }
    }
}


/**
 * @brief Removes a specific shape from the player's placed shapes
 * @param x Pointer to the Shape to be removed
 */
void Player::removePlaced(Shape* x){
    if (!x) return; // null check
    placed_.removeAll(x);
}

/**
 * @brief Removes a shape from placed shapes by its ID
 * @param id ID of the shape to be removed
 */
void Player::removePlacedByID(int id) {
    for (int i = 0; i < placed_.size(); ++i) {
        if (placed_[i]->GetShapeID() == id) {
            placed_.remove(i);
            return;
        }
    }
}
/**
 * @brief Sets the player's ability bool to the new passed state
 * @param state State we want the ability to be set to
 */
void Player::setBomb(bool state){
    has_bomb_ = state;
}
/**
 * @brief Sets the player's ability bool to the new passed state
 * @param state State we want the ability to be set to
 */
void Player::setMirror(bool state){
    has_mirror_ = state;
}
/**
 * @brief Sets the player's ability bool to the new passed state
 * @param state State we want the ability to be set to
 */
void Player::setWild(bool state){
    has_wild_ = state;
}
