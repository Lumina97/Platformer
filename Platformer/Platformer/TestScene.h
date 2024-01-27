#ifndef TESTSCENE
#define TESTSCENE


#include "Scene.h"
#include <vector>
#include "tmxlite/Map.hpp"
#include "MapLayer.h"

namespace sf {
    class RenderWindow;
}
class ComponentManager;
class Actor;

class TestScene :
    public Scene
{
public:
    // Inherited via Scene
    virtual void InitializeScene(ComponentManager* compManager) override;
    virtual void UnloadScene() override;
    virtual void UpdateScene() override;
    virtual void ReloadScene() override;


private:
    tmx::Map map;
    sf::RenderWindow* window;
    std::vector<MapLayer*> mapLayers;
    ComponentManager* componentManager;
    Actor* mapActor;
};


#endif // !TestScene