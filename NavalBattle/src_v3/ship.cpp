#include "ship.h"

Ship::Ship(size_t ship_size){
    for(size_t i = 0; i < ship_size; i++){
        cells_array.push_back(new ShipCell());
        //std::cout << cells_array[-1] << "\n";
    }
}

std::vector<ShipCell*> Ship::getArray(){
    return cells_array;
}

bool Ship::isShipDestroyed(){
    for(ShipCell* i: cells_array){
        if(i->getHealth() != 0){
            return false;
        }
    }
    return true;
}

size_t Ship::size(){
    return getArray().size();
}

Ship::~Ship(){
    if(!cells_array.empty()){
        for(size_t i = 0; i < cells_array.size(); i++){
            delete cells_array[i];
        }
        cells_array.clear();
    }
}