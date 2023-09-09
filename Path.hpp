#ifndef PATH_HPP
#define PATH_HPP "PATH_HPP"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "rsdl.hpp"
#include "Block.hpp"
#include "Field.hpp"
#include "InitialData.hpp"
#include "AddressData.hpp"

typedef std::string Address;
typedef std::vector<Block*> BlockPath;

class Path
{
public:
    Path(std::string pathData, Field* field, Window* window);
    BlockPath* getPath();
    Block* findStartBlock(); 
    Block* getNextBlockInPath(int pathBlocksPassed);
    bool checkEndOfPath(int pathBlocksPassed);
    void draw();

private:
    void fillMiddleBlockInPath();
    bool checkIfNeighbor(Block* block1, Block* block2);
    Block* findNextBlock(Block* block1, Block* block2);
    void saveTranslatedPathData(std::stringstream& pathDataStream);

    Window* gameWindow;
    BlockPath path;
    Field* gameField;
};

#endif