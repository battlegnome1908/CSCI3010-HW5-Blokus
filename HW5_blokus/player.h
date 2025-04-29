// Header for player class

#ifndef PLAYER_H
#define PLAYER_H

#include <QVector>
#include <QColor>
#include <QString>

#include "shape.h"

class Player
{
public:
    Player(int pid, const QString& name, const QColor& color, const QVector<Shape*> all_shapes);

    // Getters
        // player stats
    int GetPID() const {return pid_; }
    QString GetName() const {return name_; }
    QColor GetColor() const {return color_; }
        // Shapes
    QVector<Shape*> GetRemainingShapes() const { return remaining_; }
    QVector<Shape*> GetPlacedShapes() const { return placed_; }
    int GetRemainingCount() const { return remaining_.size(); }
    int GetPlacedCount() const {return placed_.size(); }
        // Abilities
    bool GetBomb() const {return has_bomb_; }
    bool GetMirror() const { return has_mirror_; }
    bool GetWild() const {return has_wild_; }

    // Setters and Incrementers
        // Shapes
    void addRemaining(Shape* x);
    void addPlaced(Shape* x);
    void removeRemaining(Shape* x); // remove by shape
    void removeRemainingByID(int id);   // remove by id (used for clones)
    void removePlaced(Shape* x);
    void removePlacedByID(int id);
        // Abilities
    void setBomb(bool state);
    void setMirror(bool state);
    void setWild(bool state);

    // For first placement
    bool HasPlaced() const { return has_placed_; }
    void MarkPlaced() { has_placed_ = true; }

private:
    int pid_;
    QString name_;
    QColor color_;
    QVector<Shape*> remaining_;
    QVector<Shape*> placed_;

    bool has_placed_ = false;

    // Abilities
    bool has_bomb_ = true;
    bool has_mirror_ = true;
    bool has_wild_ = true;

};

#endif // PLAYER_H
