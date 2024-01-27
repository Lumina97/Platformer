#include "Editor.h"
#include <iostream>
#include "Log.h"

int main()
{
    Editor* editor = new Editor();
    if (editor == nullptr)
    {
        ENGINE_LOG_ERROR("There was an error creating the engine!");
        return -1;
    }

    if (editor->Init() == false)
    {
        ENGINE_LOG_ERROR("There was an error creating the engine!");
        return -1;
    }

    editor->Run();
    return 0;
}