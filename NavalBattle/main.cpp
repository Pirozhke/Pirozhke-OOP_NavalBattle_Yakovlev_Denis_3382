#include "spellsManager.h"

bool isChanged(std::vector<bool> a, std::vector<bool> b){
        for(size_t i = 0; i < a.size(); i++){
            if(a[i] != b[i]){
                return true;
            }
        }
        return false;
    }

int main(){
    Field field(10, 10);
    ShipManager ship_manager(4, {1,2,3,4});
    std::vector<Ship*> ships_array = ship_manager.getShipsArray();
    try{
        field.setShip(*ships_array[0], 0, 0, false);
        field.setShip(*ships_array[1], 2, 2, true);
        field.setShip(*ships_array[2], 4, 4, false);
        field.setShip(*ships_array[3], 6, 6, true);
    }
    catch(WrongSettingShip& exception){
        std::cout << exception.what();
    }
    SpellsManager client;
    for(size_t i = 0; i < 10; i++){
        std::vector<bool> temp;
        for(size_t i = 0; i < ship_manager.getShipsArray().size(); i++){
            temp.push_back(ship_manager.getShipsArray()[i]->isShipDestroyed());
        }
        try{
            client.cast_spell(&field, &ship_manager);

            
            std::cout << "Enter the coordinates of the attack " << "(damage = " << ship_manager.getDamageScale() <<"):\n";
            size_t x, y;
            std::cin >> x >> y;
            std::cout << '\n';

            std::vector<bool> start_array, finish_array;
            for(size_t i = 0; i < ship_manager.getShipsArray().size(); i++){
                start_array.push_back(ship_manager.getShipsArray()[i]->isShipDestroyed());
            }

            field.attack(x, y, ship_manager.getDamageScale());
            ship_manager.setDamageScale(1);

            for(size_t i = 0; i < ship_manager.getShipsArray().size(); i++){
                finish_array.push_back(ship_manager.getShipsArray()[i]->isShipDestroyed());
            }
            if(isChanged(start_array, finish_array)){
                size_t n = rand();
                if(n%3 == 1){
                    client.add_spell(new Scan);
                } else if(n%3 == 2){
                    client.add_spell(new Bombing);
                } else{
                    client.add_spell(new DoubleDamage);
                }
            }

            field.printField();
        }
        catch(CastHaventSpell& exception){
            std::cout << exception.what();
        }
        catch(OutOfRangeAttack& exception){
            std::cout << exception.what();
        }
    }
    return 0;
}