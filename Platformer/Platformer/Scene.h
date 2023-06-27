#ifndef SCENE_H
#define SCENE_H 

class ComponentManager;

class Scene
{
public:
	virtual void InitializeScene(ComponentManager* compManager) = 0;
	virtual void UnloadScene() = 0;
	virtual void UpdateScene() = 0;
	virtual void ReloadScene() = 0;
};

#endif // !SCENE_H
