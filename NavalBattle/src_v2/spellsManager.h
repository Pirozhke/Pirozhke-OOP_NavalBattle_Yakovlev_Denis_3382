#pragma once
#include <iostream>
#include <queue>
#include "spells.h"
#include "spellsManagerExceptions.h"

class SpellsManager{
    private:
        std::queue<Spell*> spells_queue;
    public:
        SpellsManager();
        void add_spell(Spell* spell);
        void cast_spell(Field* field, ShipManager* ship_manager);
        size_t size();
        std::vector<size_t> array();
        ~SpellsManager();
};