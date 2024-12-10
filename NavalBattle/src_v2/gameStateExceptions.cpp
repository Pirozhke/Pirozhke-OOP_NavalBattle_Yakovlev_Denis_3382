#include "gameStateExceptions.h"

NoSaves::NoSaves(){}

const char* NoSaves::what(){
    std::string message = "There is no saves, starting new game...\n";
    return message.c_str();
}