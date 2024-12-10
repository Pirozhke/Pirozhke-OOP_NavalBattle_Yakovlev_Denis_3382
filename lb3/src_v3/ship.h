#pragma once
#include <iostream>
#include <vector>
#include "shipCell.h"

class Ship{
    private:
        std::vector<ShipCell*> cells_array;

    public:
        Ship(size_t ship_size);
        std::vector<ShipCell*> getArray();
        bool isShipDestroyed();
        size_t size();
        ~Ship();
};