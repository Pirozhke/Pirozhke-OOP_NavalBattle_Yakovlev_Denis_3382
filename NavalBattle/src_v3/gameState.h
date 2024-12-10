#pragma once

#include "game.h"
#include <iostream>

class GameState {
enum GameStates{Loaded, Saved};

private:
    GameStates state;
    Game game;

public:
    GameState(Game game);
    bool try_load();
    bool try_save();
    void new_game();
    bool play_round();
    void save(const std::string& filename);
    void load(const std::string& filename);
    friend std::ostream& operator << (std::ostream &os, const GameState &game_state);
    friend std::istream& operator >> (std::istream& in, GameState &game_state);
};