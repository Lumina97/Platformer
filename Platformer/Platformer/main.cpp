#include "Engine.h"
#include <iostream>
#include "Log.h"
int main()
{
    Engine* engine = new Engine();
    if (engine == nullptr)
    {
        ENGINE_LOG_ERROR("There was an error creating the engine!");
        return -1;
    }

    if (engine->Init() == false)
    {
        ENGINE_LOG_ERROR("There was an error creating the engine!");
        return -1;
    }

    engine->Run();
    return 0;
}