#include "ship.h"

Ship::ShipCell::ShipCell(char newStatus)
    :status(newStatus){}

void Ship::ShipCell::setCell(char newStatus){
    if (newStatus == shipCellStatus::destroyed || newStatus == shipCellStatus::healthy || newStatus == shipCellStatus::injured){
        status = newStatus;
    }
}

char Ship::ShipCell::getStatus() const{
    return status;
}

Ship::Ship(size_t newLength, size_t newCordY, size_t newCordX, char newOrientation, bool newIsDestroyed, bool newIsPlaced)
    :length(newLength), cordY(newCordY), cordX(newCordX), orientation(newOrientation), isDestroyed(newIsDestroyed), isPlaced(newIsPlaced){
    if (length > 4 || length < 1){
        length = 1;
        std::cout << "Wrong ship length, it was setted to 1." << std::endl;
    }
    segmentsArray = new ShipCell[length];
    if (segmentsArray == nullptr){
        std::cout << "Memory can't be allocate." << std::endl;
        exit(40);
    }
}

bool Ship::checkDestruction() const{
    for (size_t i = 0; i < length; i++){
        if (segmentsArray[i].getStatus() == shipCellStatus::destroyed){
            return false;
        }
    }
    return true;
}

std::pair <size_t, size_t> Ship::getCords() const{
    return std::make_pair(cordY, cordX);
}

char Ship::getOrientation() const{
    return orientation;
}

void Ship::changeOrientation(char& newOrientation){
    orientation = newOrientation;
}

void Ship::move(size_t& newY, size_t& newX){
    cordY = newY;
    cordX = newX;
}

size_t Ship::getLength() const{
    return length;
}

bool Ship::isCellDestroyed(size_t& number) const{
    if (segmentsArray[number].getStatus() == shipCellStatus::destroyed){
        return true;
    }
    return false;
}

char Ship::hitShipCell(size_t& number){
    if (segmentsArray[number].getStatus() == '2'){
        segmentsArray[number].setCell(shipCellStatus::injured);
        return shipCellStatus::injured;
    } else{
        segmentsArray[number].setCell(shipCellStatus::destroyed);
        return shipCellStatus::destroyed;
    }
}

bool Ship::getIsPlaced() const{
    return isPlaced;
}

void Ship::setIsPlaced(){
    isPlaced = true;
}

Ship::~Ship(){
    delete [] segmentsArray;
}