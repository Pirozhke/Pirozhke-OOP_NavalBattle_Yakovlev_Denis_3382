#include "shipManager.h"

ShipManager::ShipManager(){
    setDamageScale(1);
}

ShipManager::ShipManager(size_t num, std::vector<size_t> sizes_array){
    setDamageScale(1);
    size_t min = num;
    if(num > sizes_array.size()){
        min = sizes_array.size();
    }
    for(size_t i = 0; i < min; i++){
        Ship temp = Ship(sizes_array[i]);
        ships_array.push_back(temp);
    }
}

std::vector <Ship> ShipManager::getShipsArray(){
    return ships_array;
}

void ShipManager::setDamageScale(size_t new_damage_scale){
    damage_scale = new_damage_scale;
}

size_t ShipManager::getDamageScale(){
    return damage_scale;
}

ShipManager::~ShipManager(){
    if(!ships_array.empty()){
        ships_array.clear();
    }
}