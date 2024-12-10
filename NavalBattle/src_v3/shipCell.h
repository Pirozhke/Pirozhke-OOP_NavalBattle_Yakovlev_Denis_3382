#pragma once
#include <iostream>

class ShipCell{
enum ShipCellStatus: size_t {Detroyed = 0, Injured = 1, Healthy = 2};

private:
    ShipCellStatus status;

public:
    ShipCell();
    size_t getHealth() const;
    void setStatus(ShipCellStatus new_status);
    void attack(size_t damage);
};