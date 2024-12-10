#include "spells.h"

void DoubleDamage::cast_spell(Field* field, ShipManager* ship_manager){
    ship_manager->setDamageScale(2);
}

void Scan::cast_spell(Field* field, ShipManager* ship_manager){
    size_t x, y;
    std::cout << "Enter the scan coordinates:\n";
    std::cin >> x >> y;
    std::cout << '\n';
    std::vector<std::vector<Cell>> field_array = field->getFieldArray();
    if(x + 1 < field->size().second && y + 1 < field->size().first &&
    (field_array[x][y].isShipCell() || field_array[x+1][y].isShipCell() || field_array[x][y+1].isShipCell() || field_array[x+1][y+1].isShipCell())){
        std::cout << "There are ships in this area.\n";
    } else{
        std::cout << "There are no ships in this area.\n";
    }
}

void Bombing::cast_spell(Field* field, ShipManager* ship_manager){
    std::vector<ShipCell*> ship_cell_array;
    std::vector<std::vector<Cell>> field_array = field->getFieldArray();
    for(size_t i = 0; i < field->size().first; i++){
        for(size_t j = 0; j < field->size().second; j++){
            if(field_array[i][j].isShipCell() && field_array[i][j].getShipCell()->getHealth() != 0){
                ship_cell_array.push_back(field_array[i][j].getShipCell());
            }
        }
    }
    if(ship_cell_array.size() != 0){
        size_t index = rand() % ship_cell_array.size();
        ship_cell_array[index]->attack(1);
        std::cout << "A random segment of a random ship was attacked.\n";
    } else{
        std::cout << "There are no alive segments of ships for attack.\n";
    }
}