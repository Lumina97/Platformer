#include "Engine.h"
#include <iostream>
#include "Globals.h"
#include <time.h>
#include "Math.h"
#include "Log.h"
#include "Debug.h"
#include "SoundEngine.h"
#include "GameLoop.h"
#include "ComponentManager.h"

bool Engine::Init()
{
	videoMode = VideoMode::getDesktopMode();
	videoMode.height *= 0.8f;
	videoMode.width *= 0.8f;

	window.create(videoMode, "PLATFORMER!");

	Camera.setCenter(sf::Vector2f(videoMode.width / 2, videoMode.height / 2));
	Camera.setSize(sf::Vector2f(videoMode.width * 1.5f, videoMode.height * 1.5f));
	window.setView(Camera);

	GLOBAL::ScreenSize = window.getSize();
	GLOBAL::WINDOW = &window;
	GLOBAL::CAMERA = &Camera;

	collisionDetection = new Physics::CollisionDetection();
	compManager = new ComponentManager(&window, collisionDetection);
	soundEngine = new SoundEngine();
	gameLoop = new GameLoop();
	gameLoop->InitializeGameLoop(compManager);
	Log::Init();


	if (window.isOpen())
		return true;

	return false;
}

void Engine::Run()
{
	//initialize varialbes to calculate deltatime
	sf::Clock clock;
	sf::Time frameStart = clock.getElapsedTime();;
	sf::Time frameEnd;

	//soundEngine->PlayMusic();
	while (window.isOpen())
	{
		//	sf::Time elapsedTime = elapsedClock.restart();
		sf::Time elapsed = clock.getElapsedTime();
		float deltaTime = (frameEnd - frameStart).asSeconds();
		sf::Time SFDeltaTime = frameEnd - frameStart;

		TIME::SFDeltaTime = SFDeltaTime;
		TIME::DeltaTime = deltaTime;
		TIME::currentTime = elapsed.asSeconds();

		frameStart = elapsed;

		//event polling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (GLOBAL::MAINGUI != nullptr)
				GLOBAL::MAINGUI->handleEvent(event);

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
					window.close();
				break;
			}
		}

		//window drawing
		window.clear();
		gameLoop->RunUpdateLoop();
		Debug::Update();
		if (GLOBAL::MAINGUI != nullptr)
			GLOBAL::MAINGUI->draw();
		window.display();
		frameEnd = clock.getElapsedTime();

		//need to wait for event polling to end before we can delete the old gui
		tgui::Gui* oldgui = GLOBAL::oldGui;
		if (oldgui != nullptr)
		{
			delete(GLOBAL::oldGui);
			GLOBAL::oldGui = nullptr;
		}
	}
}