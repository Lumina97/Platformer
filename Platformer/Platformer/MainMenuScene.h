#ifndef MAINMENUSCENE_H
#define MAINMENUSCENE_H

#include "Scene.h"
#include "TGUI/TGUI.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>


class MainMenuScene :
    public Scene
{
public:
    // Inherited via Scene
    virtual void InitializeScene(ComponentManager* compManager) override;
    virtual void UnloadScene() override;
    virtual void UpdateScene() override;
    virtual void ReloadScene() override;

    static void ExitGame();

private:
    
    tgui::Gui* gui;

    tgui::Button::Ptr b_Play;
    tgui::Button::Ptr b_Exit;
};

#endif // !MAINMENUSCENE_H