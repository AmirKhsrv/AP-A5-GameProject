#include "Path.hpp"

using namespace std;

Path::Path(string pathData, Field* field, Window* window)
{
    gameWindow = window;
    gameField = field;
    stringstream pathDataStream;
    pathDataStream << pathData;
    saveTranslatedPathData(pathDataStream);
    fillMiddleBlockInPath();
    for (int i = 0; i < path.size(); i++)
        path[i]->setBuildPermissionFalse();
}

Block* Path::findStartBlock()
{
    return path[0];
}

Block* Path::getNextBlockInPath(int pathBlocksPassed)
{
    return path[pathBlocksPassed];
}

bool Path::checkEndOfPath(int pathBlocksPassed)
{
    return pathBlocksPassed == path.size();
}

void Path::fillMiddleBlockInPath()
{
    BlockPath completePath;
    completePath.push_back(path[0]);
    for (int i = 1; i < path.size(); i++)
    {
        while (!checkIfNeighbor(path[i], completePath[completePath.size() - 1]))
            completePath.push_back(findNextBlock(completePath[completePath.size() - 1], path[i]));
        completePath.push_back(path[i]); 
        path[i]->getBuildPermission();
    }
    path = completePath;
    completePath[1]->getBuildPermission();
}

bool Path::checkIfNeighbor(Block* block1, Block* block2)
{
    return (block1->getStartX() - block2->getStartX() == BLOCK_SIZE || block2->getStartX() - block1->getStartX() == BLOCK_SIZE)
        || (block1->getStartY() - block2->getStartY() == BLOCK_SIZE || block2->getStartY() - block1->getStartY() == BLOCK_SIZE);
}

Block* Path::findNextBlock(Block* block1, Block* block2)
{
    if (block1->getStartX() == block2->getStartX() && block1->getStartY() < block2->getStartY())
        return gameField->getBlock(Point(block1->getStartX(), block1->getStartY() + BLOCK_SIZE));
    if (block1->getStartX() == block2->getStartX() && block1->getStartY() > block2->getStartY())
        return gameField->getBlock(Point(block1->getStartX(), block1->getStartY() - BLOCK_SIZE));
    if (block1->getStartY() == block2->getStartY() && block1->getStartX() < block2->getStartX())
        return gameField->getBlock(Point(block1->getStartX() + BLOCK_SIZE, block1->getStartY()));
    if (block1->getStartY() == block2->getStartY() && block1->getStartX() > block2->getStartX())
        return gameField->getBlock(Point(block1->getStartX() - BLOCK_SIZE, block1->getStartY()));
}

void Path::draw()
{
    for (int i = 0; i < path.size(); i++)
        gameWindow->draw_img(PATH_IDENTIFIER_PIC_ADDRESS, Rectangle(Point(path[i]->getStartX(), 
                            path[i]->getStartY()), Point(path[i]->getStartX() + BLOCK_SIZE, 
                            path[i]->getStartY() + BLOCK_SIZE)), NULL_RECT, 0);
    gameWindow->draw_img(START_END_PORTAL_PIC_ADDRESS, Rectangle(Point(path[0]->getStartX(), 
                        path[0]->getStartY()), Point(path[0]->getStartX() + BLOCK_SIZE, 
                        path[0]->getStartY() + BLOCK_SIZE)), NULL_RECT, 0);
    gameWindow->draw_img(START_END_PORTAL_PIC_ADDRESS, Rectangle(Point(path[path.size() - 1]->getStartX(), 
                        path[path.size() - 1]->getStartY()), Point(path[path.size() - 1]->getStartX() + 
                        BLOCK_SIZE, path[path.size() - 1]->getStartY() + BLOCK_SIZE)), NULL_RECT, 0);
}

void Path::saveTranslatedPathData(stringstream& pathDataStream)
{
    int readVerticalIndex;
    int readHorizontalIndex;
    while(pathDataStream >> readHorizontalIndex)
    {
        pathDataStream >> readVerticalIndex;
        path.push_back(gameField->getBlock(Point(readHorizontalIndex * BLOCK_SIZE + START_FIELD_X, readVerticalIndex * BLOCK_SIZE + START_FIELD_Y)));
        gameField->getBlock(Point(readHorizontalIndex * BLOCK_SIZE + START_FIELD_X, readVerticalIndex * BLOCK_SIZE + START_FIELD_Y))->getBuildPermission();
    }
}
