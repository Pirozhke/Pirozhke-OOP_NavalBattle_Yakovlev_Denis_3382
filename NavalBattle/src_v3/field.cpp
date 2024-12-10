#include "field.h"

Field::Field(){
    size_t height = 10, width = 10;
    field_array.resize(height);
    for(size_t i = 0; i < height; i++){
        field_array[i].resize(width, Cell());
    }
}

Field::Field(size_t height, size_t width){
    field_array.resize(height);
    for(size_t i = 0; i < height; i++){
        field_array[i].resize(width, Cell());
    }
}

std::vector<std::vector<Cell>> Field::getFieldArray(){
    return field_array;
}

std::pair<size_t, size_t> Field::size(){
    std::pair<size_t, size_t> size;
    size.first = field_array.size();
    if(field_array.size() != 0){
        size.second = field_array[0].size();
    } else{
        size.second = 0;
    }
    return size;
}

bool Field::checkAreaForSetShip(Ship ship, size_t x, size_t y, bool orient_is_horizontal){
    std::pair<size_t, size_t> size = this->size();
    size_t sqx1 = 0, sqx2 = size.second, sqy1 = 0, sqy2 = size.first;
    if ((orient_is_horizontal && x + ship.size() - 1 < size.second && y < size.first) || (!orient_is_horizontal && y + ship.size() - 1 < size.first && x < size.second)){
        if(x != 0){
            sqx1 = x - 1;
        }
        if(y != 0){
            sqy1 = y - 1;
        }
        if(orient_is_horizontal){
            if(size.second > x + ship.size()){
                sqx2 = x + ship.size();
            } else{
                sqx2 = x + ship.size() - 1;
            }
            if(size.first > y + 1){
                sqy2 = y + 1;
            } else{
                sqy2 = y;
            }
        }
        if(!orient_is_horizontal){
            if(size.first > y + ship.size()){
                sqy2 = y + ship.size();
            } else{
                sqy2 = y + ship.size() - 1;
            }
            if(size.second > x + 1){
                sqx2 = x + 1;
            } else{
                sqx2 = x;
            }
        }
    } else{
        return false;
    }
    for(size_t i = sqy1; i <= sqy2; i++){
        for(size_t j = sqx1; j <= sqx2; j++){
            if(field_array[i][j].isShipCell()){
                throw WrongSettingShip(x, y, j, i);
                return false;
            }
        }
    }
    return true;
}

void Field::setShip(Ship ship, size_t x, size_t y, bool orient_is_horizontal){
    if(checkAreaForSetShip(ship, x, y, orient_is_horizontal)){
        std::vector<ShipCell*> ship_array = ship.getArray();
        if(orient_is_horizontal){
            for(size_t i = 0; i < ship.size(); i++){
                field_array[y][x+i].setShipCell(ship_array[i]);
            }
        } else{
            for(size_t i = 0; i < ship.size(); i++){
                field_array[y+i][x].setShipCell(ship_array[i]);
            }
        }
    }
    return;
}

void Field::attack(size_t x, size_t y, size_t damage){
    if(x < size().second && y < size().first){
        if(field_array[y][x].isShipCell()){
            field_array[y][x].getShipCell()->attack(damage);
        }
        field_array[y][x].changeStatus();
    } else{
        throw OutOfRangeAttack(x, y, size());
    }
}


void Field::printField(){
    for(size_t i = 0; i < field_array.size(); i++){
        if (field_array.size() != 0){
            for(size_t j = 0; j < field_array[0].size(); j++){
                std::cout << '(';
                std::cout << field_array[i][j].getCell();
                std::cout << ") ";
            }
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}


void Field::reveal(std::vector<std::pair<size_t, size_t>> cord){
    for(size_t i = 0; i < cord.size(); i++){
        field_array[cord[i].first][cord[i].second].changeStatus();
    }
}


Field::Field(const Field& field){
    field_array.resize(field.field_array.size());
    if(field.field_array.size() != 0){
        field_array.resize(field.field_array[0].size());
    }
    for(size_t i = 0; i < field_array.size(); i++){
        if(field_array.size() != 0){
            for(size_t j = 0; j < field_array[0].size(); j++){
                field_array[i][j] = field.field_array[i][j];
            }
        }
    }
}

Field& Field::operator = (const Field& field){
    if(this != &field){
        field_array.clear();
        field_array.resize(field.field_array.size());
        if(field.field_array.size() != 0){
            field_array.resize(field.field_array[0].size());
        }
        for(size_t i = 0; i < field_array.size(); i++){
            if(field_array.size() != 0){
                for(size_t j = 0; j < field_array[0].size(); j++){
                    field_array[i][j] = field.field_array[i][j];
                }
            }
        }
    }
    return *this;
}

Field::Field(Field&& field){
    field_array.clear();
    std::swap(field_array, field.field_array);
}

Field& Field::operator = (Field&& field){
    if(this != &field){
        std::swap(field_array, field.field_array);
    }
    return *this;
}

Field::~Field(){
    for(std::vector<Cell> i: field_array){
        if(!i.empty()){
            i.clear();
        }
    }
    field_array.clear();
}