#pragma once

#include <iostream>

class Ship{
    enum shipCellStatus : char {destroyed = '0', injured = '1', healthy = '2'};
    enum shipOrientation : char {gorizontal = 'g', vertical = 'v'}; 

    class ShipCell{
    private:
        char status;

    public:
        ShipCell(char newStatus = shipCellStatus::healthy);
        void setCell(char newStatus);
        char getStatus() const;
    };
    
private:
    size_t length, cordY, cordX;
    char orientation;
    bool isDestroyed, isPlaced;
    ShipCell* segmentsArray;

public:
    Ship(size_t newLength = 0, size_t newCordY = 0, size_t newCordX = 0, char newOrientation = shipOrientation::gorizontal, bool newIsDestroyed = false, bool newIsPlaced = false);
    bool checkDestruction() const;
    std::pair <size_t, size_t> getCords() const;
    char getOrientation() const;
    void changeOrientation(char& newOrientation);
    void move(size_t& newY, size_t& newX);
    size_t getLength() const;
    bool isCellDestroyed(size_t& number) const;
    char hitShipCell(size_t& number);
    bool getIsPlaced() const;
    void setIsPlaced();
    ~Ship();
};