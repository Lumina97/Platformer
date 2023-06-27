#include "GUI.h"
#include "Globals.h"
#include <iostream>

using namespace tgui;

GUI::GUI(sf::RenderWindow* window)
{
	this->window = window;
	mainGUI.setWindow(*window);

	InitializeFinishedGameLabel();
	InitializePlayerScoreLabel();
}

void GUI::RenderGUI()
{
	mainGUI.draw();
}

void GUI::SetScore(int player, int enemy)
{
	tgui::String score;
	score.append(std::to_string(player));
	score.append("		");
	score.append(std::to_string(enemy));
		
	playerScoreText.get()->setText(score);
}

void GUI::SetGameFinished(gameState winstate)
{
	switch (winstate)
	{
	case player:
		gameFinishedLabel.get()->setText("PLAYER WINS!\nSpace to continue");
		gameFinishedLabel.get()->getRenderer()->setOpacity(100);
		break;

	case enemy:
		gameFinishedLabel.get()->setText("ENEMY WINS!\nSpace to continue");
		gameFinishedLabel.get()->getRenderer()->setOpacity(100);
		break;
	case running:
		gameFinishedLabel.get()->setText("");
		gameFinishedLabel.get()->getRenderer()->setOpacity(0);
		break;
	}
}

void GUI::InitializePlayerScoreLabel()
{
	playerScoreText = Label::create();
	playerScoreText.get()->setText("0		0");
	playerScoreText.get()->setTextSize(30);
	playerScoreText.get()->setHorizontalAlignment(Label::HorizontalAlignment::Center);

	try
	{
		tgui::Font font{"Resources/Guardians.ttf"};
		playerScoreText.get()->getRenderer()->setFont(font);

	}
	catch (tgui::Exception e)
	{
		std::cout << "Error loading font!\n" << e.what() << "\n";
	}

	playerScoreText.get()->getRenderer()->setTextColor(Color::White);
	playerScoreText.get()->getRenderer()->setBackgroundColor(Color::Transparent);


	float widgetWidth = playerScoreText.get()->getFullSize().x;
	playerScoreText.get()->setPosition((GLOBAL::ScreenSize.x / 2) - widgetWidth / 2, GLOBAL::ScreenSize.y * 0.05f);

	mainGUI.add(playerScoreText);
}

void GUI::InitializeFinishedGameLabel()
{
	gameFinishedLabel = Label::create();
	gameFinishedLabel.get()->setText("PLAYER WINS!\nSpace to continue");
	gameFinishedLabel.get()->setTextSize(30);
	gameFinishedLabel.get()->setHorizontalAlignment(Label::HorizontalAlignment::Center);

	try
	{
		Font font{"Resources/Guardians.ttf"};
		gameFinishedLabel.get()->getRenderer()->setFont(font);

	}
	catch (tgui::Exception e)
	{
		std::cout << "Error loading font!\n" << e.what() << "\n";
	}

	gameFinishedLabel.get()->getRenderer()->setTextColor(Color::White);
	gameFinishedLabel.get()->getRenderer()->setBackgroundColor(Color::Transparent);


	float widgetWidth = gameFinishedLabel.get()->getFullSize().x;
	float widgetHeight = gameFinishedLabel.get()->getFullSize().y;
	gameFinishedLabel.get()->setPosition((GLOBAL::ScreenSize.x / 2) - widgetWidth / 2, (GLOBAL::ScreenSize.y / 2) - widgetHeight / 2);

	gameFinishedLabel.get()->getRenderer()->setOpacity(0);


	mainGUI.add(gameFinishedLabel);
}
