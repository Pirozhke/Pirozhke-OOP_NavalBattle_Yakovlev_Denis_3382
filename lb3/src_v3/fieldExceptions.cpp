#include "fieldExceptions.h"

OutOfRangeAttack::OutOfRangeAttack(size_t x, size_t y, std::pair<size_t, size_t> size)
:x(x), y(y), size(size){}

const char* OutOfRangeAttack::what(){
    std::string message = "Size of field is " + std::to_string(size.second) + ":" + std::to_string(size.first) + ".\n";
    message += "The x coordinate must be less than " + std::to_string(size.second) + ", now: " + std::to_string(x) + ".\n";
    message += "The y coordinate must be less than " + std::to_string(size.first) + ", now: " + std::to_string(y) + ".\n";
    return message.c_str();
}

WrongSettingShip::WrongSettingShip(size_t x, size_t y, size_t setX, size_t setY)
:x(x), y(y), setX(setX), setY(setY){}

const char* WrongSettingShip::what(){
    std::string message = "It is impossible to place the ship according to the coordinates (" + std::to_string(x) + ", " + std::to_string(y) + ").\n";
    message += "Another ship is already located at the coordinates (" + std::to_string(setX) + ", " + std::to_string(setY) + ").\n";
    return message.c_str();
}