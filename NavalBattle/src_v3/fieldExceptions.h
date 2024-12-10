#pragma once
#include <iostream>

class OutOfRangeAttack: std::exception{
private:
    size_t x, y;
    std::pair<size_t, size_t> size;
public:
    OutOfRangeAttack(size_t x, size_t y, std::pair<size_t, size_t> size);
    const char* what();
};

class WrongSettingShip: std::exception{
private:
    size_t x, y, setX, setY;
public:
    WrongSettingShip(size_t x, size_t y, size_t setX, size_t setY);
    const char* what();
};