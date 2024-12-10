#pragma once
#include <iostream>

class CastHaventSpell: std::exception{
public:
    CastHaventSpell();
    const char* what();
};