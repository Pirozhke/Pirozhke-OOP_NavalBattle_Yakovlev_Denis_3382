#include "cell.h"

Cell::Cell(){
    status = Hidden;
    ship_cell = nullptr;
}

Cell::Cell(ShipCell* new_ship_cell): ship_cell(new_ship_cell){
    status = Hidden;
}

ShipCell* Cell::getShipCell() const{
    return ship_cell;
}

char Cell::getCell() const{
    if(isShipCell() && status != Hidden){
        return (char)getShipCell()->getHealth() + 48;
    } else{
        if(status == Hidden){
            return '*';
        } else if(status == Empty){
            return '.';
        } else{
            return ' ';
        }
    }
}

bool Cell::isShipCell() const{
    if(ship_cell != nullptr){
        return true;
    }
    return false;
}

void Cell::changeStatus(){
    if(ship_cell != nullptr){
        status = Ship;
    } else{
        status = Empty;
    }
}

void Cell::setShipCell(ShipCell* new_ship_cell){
    ship_cell = new_ship_cell;
}

bool Cell::isHidden(){
    if(status == Hidden){
        return true;
    }
    return false;
}