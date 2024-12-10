#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "ship.h"
#include "cell.h"
#include "fieldExceptions.h"

class Field{
    private:
        std::vector<std::vector<Cell>> field_array;
        bool checkAreaForSetShip(Ship ship, size_t x, size_t y, bool orient_is_horizontal);

    public:
        Field();
        Field(size_t height, size_t width);
        std::vector<std::vector<Cell>> getFieldArray();
        std::pair<size_t, size_t> size();
        void setShip(Ship ship, size_t x, size_t y, bool orient_is_horizontal);
        void attack(size_t x, size_t y, size_t damage);
        void printField();
        void reveal(std::vector <std::pair <size_t, size_t>> cord);
        Field(const Field& field);
        Field& operator = (const Field& field);
        Field(Field&& field);
        Field& operator = (Field&& field);
        ~Field();
};