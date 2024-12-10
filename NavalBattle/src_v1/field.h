#pragma once

#include "shipManager.h"
#include "ship.h"
#include <iostream>
#include <string>
#include <vector>

class Field{
    enum cellStatus : char {hidden = '*', empty = '.', destroyedShip = '0', injuredShip = '1', healthyShip = '2'};

private:
    std::vector <std::vector <char>> fieldArray;
    size_t length, height;
    
public:
    Field(size_t length = 10, size_t height = 10);
    void printField();
    void setFieldSize(size_t& newHeight, size_t& newLength);
    bool setFieldCell(size_t& cellHeight, size_t& cellLength, char cellValue);
    bool checkCellLimit(size_t cellHeight, size_t cellLength) const;
    bool placeShip(ShipManager& shipManager, size_t& numberOfShip, size_t& newCordY, size_t& newCordX, bool newIsGorizontal);
    //bool placeShip(Ship& newShip, ShipManager& shipManager);
    bool attack(size_t& cellHeight, size_t& cellLength, ShipManager& shipManager);
    bool possibleAttack(size_t& cellHeight, size_t& cellLength, ShipManager& shipManager);
    Field(const Field& field);
    Field& operator = (const Field& field);
    Field(Field&& field);
    Field& operator = (Field&& field);
    ~Field();
};