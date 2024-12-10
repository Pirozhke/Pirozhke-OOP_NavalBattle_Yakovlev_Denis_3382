#pragma once

#include "game.h"
#include "gameStateExceptions.h"
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
};