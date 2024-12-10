#pragma once
#include <iostream>

class NoSaves: std::exception{
public:
    NoSaves();
    const char* what();
};
