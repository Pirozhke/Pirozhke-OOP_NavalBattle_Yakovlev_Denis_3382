#include "field.h"

Field::Field(size_t newLength, size_t newHeight)
    :length(newLength), height(newHeight){
    fieldArray.resize(height);
    for (size_t i = 0; i < height; i++){
        fieldArray[i].resize(length, cellStatus::hidden);
    }
}

void Field::printField(){
    for (size_t i = 0; i < height; i++){
        for (size_t j = 0; j < length; j++){
            std::cout << '(' << fieldArray[i][j] << ')' << " ";
        }
        std::cout << std::endl; 
    }
}

void Field::setFieldSize(size_t& newHeight, size_t& newLength){
    height = newHeight;
    length = newLength;
    fieldArray.resize(height);
    for (size_t i = 0; i < height; i++){
        fieldArray[i].resize(length, cellStatus::hidden);
    }
}

bool Field::setFieldCell(size_t& cellHeight, size_t& cellLength, char cellValue){
    if (checkCellLimit(cellHeight, cellLength)){
        fieldArray[cellHeight][cellLength] = cellValue;
        return true;
    } else{
        return false;
    }
}

bool Field::checkCellLimit(size_t cellHeight, size_t cellLength) const{
    if (cellHeight >= height || cellLength >= length){
        return false;
    }
    return true;
}

/*bool Field::placeShip(Ship& newShip, ShipManager& shipManager){
    std::pair <size_t, size_t> newCords = newShip.getCords();
    size_t newLength = newShip.getLength();
    bool newIsGorizontal = true;
    if (newShip.getOrientation() == 'v'){
        newIsGorizontal = false;
    }
    for (size_t i = 0; i < newLength; i++){
        if (!((newIsGorizontal && checkCellLimit(newCords.first, newCords.second + i)) || (!newIsGorizontal && checkCellLimit(newCords.first + i, newCords.second)))){
            return false;
        }
    }
    for (size_t k = 0; k < length; k++){
        size_t cellHeight = newCords.first;
        size_t cellLength = newCords.second;
        if(newIsGorizontal == true){
            cellLength += k;
        } else{
            cellHeight += k;
        }
        size_t i = 0;
        Ship currentShip = shipManager.getShip(i);
        while (shipManager.isInArray(i)){
            currentShip = shipManager.getShip(i);
            std::pair <size_t, size_t> cords = currentShip.getCords();
            bool isGorizontal = true;
            if (currentShip.getOrientation() == 'v'){
                isGorizontal = false;
            }
            if (cords.first > 0){
                cords.first--;
            }
            if (cords.second > 0){
                cords.second--;
            }
            for (size_t l = 0; l < currentShip.getLength() + 2; l++){
                for (size_t w = 0; w < 3; w++){
                    if (!((isGorizontal && (cords.second + l == cellLength) && (cords.first + w == cellHeight)) || 
                    (!isGorizontal && (cords.second + w == cellLength) && (cords.first + l == cellHeight)))){
                        return false;
                    }
                }
            }
            i++;
            }
        }
    return true;
}*/

bool Field::placeShip(ShipManager& shipManager, size_t& numberOfShip, size_t& newCordY, size_t& newCordX, bool setterOrientation){
    if (shipManager.getShip(numberOfShip).getIsPlaced()){
        return true;
    }
    std::pair <size_t, size_t> newCords;
    newCords.first = newCordY;
    newCords.second = newCordX;
    size_t newLength = shipManager.getShip(numberOfShip).getLength();
    bool newIsGorizontal = setterOrientation;
    for (size_t i = 0; i < newLength; i++){
        if (!((newIsGorizontal && checkCellLimit(newCords.first, newCords.second + i)) || (!newIsGorizontal && checkCellLimit(newCords.first + i, newCords.second)))){
            return false;
        }
    }
    for (size_t k = 0; k < newLength; k++){
        size_t cellHeight = newCords.first;
        size_t cellLength = newCords.second;
        if(newIsGorizontal == true){
            cellLength += k;
        } else{
            cellHeight += k;
        }
        size_t i = 0;
        Ship currentShip = shipManager.getShip(i);
        while (shipManager.isInArray(i)){
            currentShip = shipManager.getShip(i);
            if (currentShip.getIsPlaced()){
                std::pair <size_t, size_t> cords = currentShip.getCords();
                size_t maxL = currentShip.getLength() + 2, maxW = 3;
                bool isGorizontal = true;
                if (currentShip.getOrientation() == 'v'){
                    isGorizontal = false;
                }
                if (cords.first > 0){
                    cords.first--;
                } else{
                    if (isGorizontal){
                        maxW--;
                    } else{
                        maxL--;
                    }
                }
                if (cords.second > 0){
                    cords.second--;
                } else{
                    if (isGorizontal){
                        maxL--;
                    } else{
                        maxW--;
                    }
                }
                for (size_t l = 0; l < maxL; l++){
                    for (size_t w = 0; w < maxW; w++){
                        if ((isGorizontal && (cords.second + l == cellLength) && (cords.first + w == cellHeight)) || 
                        (!isGorizontal && (cords.second + w == cellLength) && (cords.first + l == cellHeight))){
                            return false;
                        }
                    }
                }
            }
            i++;
        }
    }
    char orientation;
    if (newIsGorizontal){
        orientation = 'g';
    } else{
        orientation = 'v';
    }
    shipManager.placeShip(numberOfShip, newCordY, newCordX, orientation);
    return true;
}

bool Field::attack(size_t& cellHeight, size_t& cellLength, ShipManager& shipManager){
    if (checkCellLimit(cellHeight, cellLength) && fieldArray[cellHeight][cellLength] != cellStatus::destroyedShip && fieldArray[cellHeight][cellLength] != cellStatus::empty){
        if (!(possibleAttack(cellHeight, cellLength, shipManager) == true)){
            setFieldCell(cellHeight, cellLength, cellStatus::empty);
        }
        return true;
    } else{
        return false;
    }
}

bool Field::possibleAttack(size_t& cellHeight, size_t& cellLength, ShipManager& shipManager){
    size_t i = 0;
    Ship currentShip = shipManager.getShip(i);
    while (shipManager.isInArray(i)){
        currentShip = shipManager.getShip(i);
        std::pair <size_t, size_t> cords = currentShip.getCords();
        bool isGorizontal = true;
        if (currentShip.getOrientation() == 'v'){
            isGorizontal = false;
        }
        for (size_t j = 0; j < currentShip.getLength(); j++){
            if ((isGorizontal && cords.first == cellHeight && cords.second + j == cellLength) || (!isGorizontal && cords.first + j == cellHeight && cords.second == cellLength)){
                if (!currentShip.isCellDestroyed(j)){
                    setFieldCell(cellHeight, cellLength, currentShip.hitShipCell(j));
                    return true;
                }
            }
        }
        i++;
    }
    return false;
}

Field::Field(const Field& field)
    :length(field.length), height(field.height){
    fieldArray.clear();
    for (size_t i = 0; i < height; i++){
        fieldArray.push_back(field.fieldArray[i]);
    }
}

Field& Field::operator = (const Field& field){
    if (this != &field){
        fieldArray.clear();
        for (size_t i = 0; i < height; i++){
            fieldArray.push_back(field.fieldArray[i]);
        }
    }
    return *this;
}

Field::Field(Field&& field)
    :length(0), height(0){
    fieldArray.clear();
    std::swap(length, field.length);
    std::swap(height, field.height);
    std::swap(fieldArray, field.fieldArray);
}
    
Field& Field::operator = (Field&& field){
     if (this != &field){
        fieldArray.clear();
        length = 0;
        height = 0;
        std::swap(length, field.length);
        std::swap(height, field.height);
        std::swap(fieldArray, field.fieldArray);
    }
    return *this;
}

Field::~Field(){
    fieldArray.clear();
}