#include "field.h"
#include <iostream>
#include <vector>

int main (){
    //make field
    size_t height, length;
    std::cout << "Hello, it's  the Naval Battle!" << std::endl << "Please, set the Field:"<< std::endl << "\tHeight of the Field: ";
    std::cin >> height;
    std::cout << "\tLength of the Field: ";
    std::cin >> length;
    std::cout << std::endl;
    Field field(length, height);
    field.printField();
    
    //make start ships
    std::vector <size_t> sizesOfShips;
    sizesOfShips.push_back(2);
    sizesOfShips.push_back(3);
    size_t numberOfShips = sizesOfShips.size();
    ShipManager shipManager(numberOfShips, sizesOfShips);
    
    //place start ships
    std::cout << "Placing ships to the field:" << std::endl;
    for (size_t i = 0; i < numberOfShips; i++){
        size_t x = 0, y = 0, temp;
        bool isGorizontal = true;
        char answer;
        do{
            do{
                std::cout << "Please, set y-coordinate: ";
                std::cin >> temp;
            } while (typeid(temp) != typeid(y));
            y = temp;
            do{
                std::cout << "Please, set x-coordinate: ";
                std::cin >> temp;
            } while (typeid(temp) != typeid(x));
            x = temp;
            do{
                std::cout << "Please, set orientation of the ship (type <v> for vertical and <g> for gorizontal): ";
                std::cin >> answer;
            } while (answer != 'g' && answer != 'v');
            if (answer == 'v'){
                isGorizontal = false;
            }
        } while (!(field.placeShip(shipManager, i, y, x, isGorizontal)));
        //field.printField();
    }

    //attack
    while(true){
        size_t attackY = height, attackX = length;
        std::cout << "Attack:" << std::endl;
        do{
            std::cout << "\tY-coordinate for attack: ";
            std::cin >> attackY;
        } while (attackY >= height);
        do{
            std::cout << "\tX-coordinate for attack: ";
            std::cin >> attackX;
        } while (attackX >= length);
        std::cout << std::endl;
        field.attack(attackY, attackX, shipManager);
        field.printField();
    }

    return 0;
}