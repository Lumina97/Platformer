#ifndef TIME
#define TIME

inline float DeltaTime = 0;
inline float currentTime = 0;

#endif // !TIME_H


#ifndef GLOBAL
#define GLOBAL

#include "SFML/Graphics.hpp"
#include "TGUI/TGUI.hpp"
#include <TGUI/Backend/SFML-Graphics.hpp>

inline sf::Vector2u ScreenSize;
inline float gravity = 0.97f;
inline sf::RenderWindow* WINDOW;
inline sf::View* CAMERA;
inline tgui::Gui* MAINGUI;
inline tgui::Gui* oldGui;
inline void SetGUI(tgui::Gui* newGui)
{
	oldGui = GLOBAL::MAINGUI;
	GLOBAL::MAINGUI = newGui;
}

#endif // !GLOBAL
