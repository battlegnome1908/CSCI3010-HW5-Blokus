#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QVector>
#include "player.h"
#include "board.h"

class Game : public QObject {
    Q_OBJECT

public:
    Game(QObject* parent = nullptr);

    void AddPlayer(Player* player);
    void NextTurn();

    // Getters
    Board* GetBoard() const {return board_; }
    Player* GetCurrentPlayer() const;
    int GetTurnCount() const { return turn_count_; }
    int GetCurrentPlayerIndex() const { return current_player_index_; }
    QVector<Player*> GetAllPlayers() const { return players_; }
    int GetNumPlayers() const { return num_players_; }
    Player* FindPlayerByPID(int pid) const;
    QColor GetDefaultColor(int index) const;


    void Reset(); // new game /restart


signals:
    void PlayerChanged(Player* new_player);

private:
    int num_players_ = 0;
    QVector<Player*> players_;
    int current_player_index_ = 0;
    int turn_count_ = 0;

    Board* board_ = nullptr;
};

#endif // GAME_H
