#pragma once

#include "ship.h"
#include <vector>

class ShipManager{
private:
    std::vector <Ship> shipsArray;

public:
    ShipManager(size_t& numberOfShips, std::vector <size_t>& sizes);
    void addShip(size_t& length);
    void addShip(Ship& newShip);
    Ship getShip(size_t& number) const;
    bool isInArray(size_t& number) const;
    void placeShip(size_t& number, size_t& newCordY, size_t& newCordX, char& orientation);
    ~ShipManager();
};