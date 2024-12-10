#include <iostream>
#include <fstream>

int main(){
    std::ifstream file("test.txt");
    size_t size, temp;
    file >> size;
    std::cout << size << "\n";
    for(size_t i = 0; i < size; i++){
        if(file.eof()){
            std::cout << "eof\n";
            break;
        }
        size_t temp = -1;
        file >> temp;
        std::cout << temp << "\n";
    }
    file.close();
    return 0;
}