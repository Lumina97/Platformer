#include "Engine.h"
#include <iostream>
#include "Globals.h"
#include <time.h>
#include "Math.h"
#include "Log.h"
#include "Debug.h"

bool Engine::Init()
{
	videoMode = VideoMode::getDesktopMode();
	videoMode.height *= 0.8f;
	videoMode.width *= 0.8f;

	window.create(videoMode, "PLATFORMER!");

	Camera.setCenter(sf::Vector2f(videoMode.width / 2, videoMode.height / 2));
	Camera.setSize(sf::Vector2f(videoMode.width * 1.5, videoMode.height * 1.5));
	window.setView(Camera);

	GLOBAL::ScreenSize = window.getSize();
	GLOBAL::WINDOW = &window;
	GLOBAL::CAMERA = &Camera;

	collisionDetection = new Physics::CollisionDetection();
	compManager = new ComponentManager(&window, collisionDetection);
	soundEngine = new SoundEngine();
	gameLoop = new GameLoop();
	gameLoop->InitializeGameLoop(&window, compManager, collisionDetection);
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
	tgui::SFML_GRAPHICS::Gui* gui = gameLoop->GetGUI();

	//soundEngine->PlayMusic();
	while (window.isOpen())
	{
		//	sf::Time elapsedTime = elapsedClock.restart();
		sf::Time elapsed = clock.getElapsedTime();
		float deltaTime = (frameEnd - frameStart).asSeconds();
		TIME::DeltaTime = deltaTime;
		TIME::currentTime = elapsed.asSeconds();
		frameStart = elapsed;

		//event polling
		sf::Event event;
		while (window.pollEvent(event))
		{
			gui->handleEvent(event);

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::KeyPressed:
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
				break;
			}
		}


		//window drawing
		window.clear();
		Debug::Update();
		gameLoop->RunUpdateLoop();
		window.display();
		frameEnd = clock.getElapsedTime();
	}
}