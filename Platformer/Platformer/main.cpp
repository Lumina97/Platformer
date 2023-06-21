#include "Engine.h"
#include <iostream>
int main()
{
    Engine* engine = new Engine();
    if (engine == nullptr)
    {
        std::cout << "There was an error creating the engine!" << "\n";
        return -1;
    }

    if (engine->Init() == false)
    {
        std::cout << "There was an error creating the engine!" << "\n";
        return -1;
    }

    engine->Run();
    return 0;
}