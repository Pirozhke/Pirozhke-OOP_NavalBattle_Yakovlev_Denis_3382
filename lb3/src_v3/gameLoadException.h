#pragma once
#include <iostream>

class BrokenLoadingFile: std::exception{
private:
    std::string message;
public:
    BrokenLoadingFile(std::string message);
    const char* what();
};