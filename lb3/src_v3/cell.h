#pragma once
#include "shipCell.h"

class Cell{
enum CellStatus{Hidden, Empty, Ship};

private:
    CellStatus status;
    ShipCell* ship_cell;

public:
    Cell();
    Cell(ShipCell* new_ship_cell);
    ShipCell* getShipCell() const;
    char getCell() const;
    bool isShipCell() const;
    void changeStatus();
    void setShipCell(ShipCell* new_ship_cell);
    bool isHidden();
};