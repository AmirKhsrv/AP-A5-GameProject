#include "Field.hpp"

using namespace std;

Field::Field(Window* window)
{
    gameWindow = window;
    int blocksNumberVertical = (END_FIELD_Y - START_FIELD_Y) / BLOCK_SIZE;
    int blocksNumberHorizontal = (END_FIELD_X - START_FIELD_X) / BLOCK_SIZE;
    for (int i = 0; i < blocksNumberHorizontal; i++)
    {
        BlockColumn blockColumn;
        for (int j = 0; j < blocksNumberVertical; j++)
        {
            Block* block = new Block(START_FIELD_X + (i * BLOCK_SIZE), START_FIELD_Y + (j * BLOCK_SIZE));
            blockColumn.push_back(block);
        }
        blocks.push_back(blockColumn);
    }
}

Block* Field::getBlock(Point point)
{
    int horizontalIndex = (point.x - START_FIELD_X) / BLOCK_SIZE;
    int verticalIndex = (point.y - START_FIELD_Y) / BLOCK_SIZE;
    return blocks[horizontalIndex][verticalIndex];
}

void Field::setUnderConstructionBlock(Point point)
{
    if (underOrderMenu.size() == 0)
    {
        underOrderMenu.push_back(getBlock(point)); 
        ifOrderBuildMenu = true;
    }    
    else
        underOrderMenu.pop_back();
}

void Field::update()
{
 
}

void Field::draw()
{
    if (underOrderMenu.size() != 0)
    {
        if (ifOrderBuildMenu)
            gameWindow->draw_img(CONSTRUCTION_MENU, Rectangle(Point(underOrderMenu[0]->getStartX() - 90, 
                                underOrderMenu[0]->getStartY() - 150), Point(underOrderMenu[0]->getStartX() + 
                                150, underOrderMenu[0]->getStartY() + 90)), NULL_RECT, 0);
        else 
            gameWindow->draw_img(TOWER_INFO_MENU, Rectangle(Point(underOrderMenu[0]->getStartX() - 120, 
                                underOrderMenu[0]->getStartY() - 120), Point(underOrderMenu[0]->getStartX() + 
                                180, underOrderMenu[0]->getStartY() + 180)), NULL_RECT, 0);
    }
}

void Field::setTowerInfoBlock(Point point)
{
    if (underOrderMenu.size() == 0)
    {
        underOrderMenu.push_back(getBlock(point)); 
        ifOrderBuildMenu = false;
    }
    else
        underOrderMenu.pop_back();
}

void Field::clearMenus()
{
    if (underOrderMenu.size() != 0)
        underOrderMenu.pop_back();
}

Tower* Field::getTowerInBlock(Block* block)
{
    return block->getTowerIn();
}

void Field::deleteBlocksForRestart()
{
    int blocksNumberVertical = (END_FIELD_Y - START_FIELD_Y) / BLOCK_SIZE;
    int blocksNumberHorizontal = (END_FIELD_X - START_FIELD_X) / BLOCK_SIZE;
    for (int i = 0; i < blocksNumberHorizontal; i++)
        for (int j = 0; j < blocksNumberVertical; j++)
            delete blocks[i][j];
}
