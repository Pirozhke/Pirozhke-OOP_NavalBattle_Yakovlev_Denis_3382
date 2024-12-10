#include "gameLoadException.h"

BrokenLoadingFile::BrokenLoadingFile(std::string message) :message(message){}

const char* BrokenLoadingFile::what(){
    return this->message.c_str();
}