#include "spellsManagerExceptions.h"

CastHaventSpell::CastHaventSpell(){}

const char* CastHaventSpell::what(){
    std::string message = "You don't have any spell now.\n";
    return message.c_str();
}