#include "Editor.h"
#include <iostream>
#include "Globals.h"
#include <time.h>
#include "Math.h"
#include "Log.h"

bool Editor::Init()
{
	videoMode = VideoMode::getDesktopMode();
	videoMode.height *= 0.8f;
	videoMode.width *= 0.8f;

	window.create(videoMode, "Map Editor");

	Camera.setCenter(sf::Vector2f(videoMode.width / 2, videoMode.height / 2));
	Camera.setSize(sf::Vector2f(videoMode.width * 1.5f, videoMode.height * 1.5f));
	window.setView(Camera);

	GLOBAL::ScreenSize = window.getSize();
	GLOBAL::WINDOW = &window;
	GLOBAL::CAMERA = &Camera;

	Log::Init();


	if (window.isOpen())
		return true;

	return false;
}

void Editor::Run()
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
		TIME::DeltaTime = deltaTime;
		TIME::currentTime = elapsed.asSeconds();
		frameStart = elapsed;

		//event polling
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (GLOBAL::MAINGUI != NULL)
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
