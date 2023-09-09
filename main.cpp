#include <iostream>
#include "rsdl.hpp"
#include "FieldRunner.hpp"
#include "Interface.hpp"

using namespace std;

int main()
{
    Window* gameWindow = new Window(1365, 1024, "FieldRunner");
    FieldRunner* fieldRunner = new FieldRunner(gameWindow);
    Interface interface(fieldRunner, gameWindow);
    interface.runGame();
}