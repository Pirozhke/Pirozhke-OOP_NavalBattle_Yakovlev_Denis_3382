#include "shipCell.h"

ShipCell::ShipCell(){
    status = Healthy;
}

size_t ShipCell::getHealth() const{
    return static_cast<size_t> (status);
}

void ShipCell::setStatus(ShipCellStatus new_status){
    status = new_status;
}

void ShipCell::attack(size_t damage){
    size_t health = getHealth();
    if(health != 0 && damage <= health){
        health -= damage;
    } else{
        health = 0;
    }
    setStatus(ShipCellStatus(health));
}