#ifndef FIELD_HPP
#define FIELD_HPP "FIELD_HPP"

#include <iostream>
#include <string>
#include <vector>
#include "rsdl.hpp"
#include "Block.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

typedef std::vector<std::vector<Block*> > FieldBlocks;
typedef std::vector<Block*> BlockColumn;

class Field
{
public:
    Field(Window* window);
    Block* getBlock(Point point);
    void setUnderConstructionBlock(Point point);
    void setTowerInfoBlock(Point point);
    void update();
    void draw();
    void clearMenus();
    Tower* getTowerInBlock(Block* block);
    void deleteBlocksForRestart();

private:    
    Window* gameWindow;
    FieldBlocks blocks;
    BlockColumn underOrderMenu;
    bool ifOrderBuildMenu;
};

#endif