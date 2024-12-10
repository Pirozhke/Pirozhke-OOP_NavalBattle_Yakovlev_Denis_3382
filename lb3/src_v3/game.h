#pragma once

#include "spellsManager.h"
#include "gameLoadException.h"
#include <fstream>

class Game{
    private:
        Field player_field, bot_field;
        ShipManager player_ship_manager, bot_ship_manager;
        SpellsManager player_spells_manager, bot_spells_manager;
        size_t count_of_ships, field_height, field_width;

    public:
        Game();
        void new_game();
        bool play_round();
        void play_next_level();
        void save(const std::string& filename);
        void load(const std::string& filename);
};