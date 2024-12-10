#include "shipManager.h"

ShipManager::ShipManager(size_t& numberOfShips, std::vector <size_t>& sizes){
    shipsArray.reserve(numberOfShips*sizeof(Ship));
    for (size_t i = 0; i < numberOfShips; i++){
        if (i >= sizes.size()){
            break;
        }
        addShip(sizes[i]);
    }
}

void ShipManager::addShip(size_t& length){
    Ship newShip(length);
    shipsArray.push_back(newShip);
}

void ShipManager::addShip(Ship& newShip){
    shipsArray.push_back(newShip);
}

Ship ShipManager::getShip(size_t& number) const{
    if (isInArray(number)){
        return shipsArray[number];
    }
    return 0;
}

bool ShipManager::isInArray(size_t& number) const{
    if (number < shipsArray.size()){
        return true;
    }
    return false;
}

void ShipManager::placeShip(size_t& number, size_t& newCordY, size_t& newCordX, char& orientation){
    shipsArray[number].move(newCordY, newCordX);
    shipsArray[number].changeOrientation(orientation);
    shipsArray[number].setIsPlaced();
}

ShipManager::~ShipManager(){
    shipsArray.clear();
}