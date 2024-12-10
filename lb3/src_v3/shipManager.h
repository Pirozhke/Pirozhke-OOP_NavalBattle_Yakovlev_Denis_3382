#pragma once
#include <iostream>
#include <vector>
#include "ship.h"

class ShipManager{
    private:
        std::vector <Ship> ships_array;
        size_t damage_scale;
    public:
        ShipManager();
        ShipManager(size_t num, std::vector<size_t> sizes_array);
        std::vector <Ship> getShipsArray();
        void setDamageScale(size_t new_damage_scale);
        size_t getDamageScale();
        ~ShipManager();
};