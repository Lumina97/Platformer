#include "Engine.h"
#include <iostream>
#include "Globals.h"
#include <time.h>
#include "Math.h"

bool Engine::Init()
{
	videoMode = VideoMode::getDesktopMode();
	videoMode.height *= 0.8f;
	videoMode.width *= 0.8f;

	window.create(videoMode, "Pong!");
	//window.setFramerateLimit(60);

	GLOBAL::ScreenSize = window.getSize();
	compManager = new ComponentManager(&window);
	soundEngine = new SoundEngine();
	gameLoop = new GameLoop();
	gameLoop->InitializeGameLoop(&window, compManager);

	if (window.isOpen())
		return true;

	return false;
}

void Engine::Run()
{
	//initialize varialbes to calculate deltatime
	sf::Clock clock;
	//sf::Clock elapsedClock;
	sf::Time frameStart = clock.getElapsedTime();;
	sf::Time frameEnd;
	tgui::SFML_GRAPHICS::Gui* gui = gameLoop->GetGUI();


	//sf::Time targetFrameTime = sf::seconds(1.0f / 10000.0f);


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
		gameLoop->RunUpdateLoop();
		window.display();
		frameEnd = clock.getElapsedTime();


		//sf::Time remainingTime = targetFrameTime - elapsedTime;
		//if (remainingTime > sf::Time::Zero)
		//{
		//	sf::sleep(remainingTime);
		//}
	}
}