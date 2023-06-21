#pragma once
#ifndef TIME
#define TIME

inline float DeltaTime = 0;
inline float currentTime = 0;

#endif // !TIME_H


#ifndef GLOBAL
#define GLOBAL

#include "SFML/Graphics.hpp"

inline sf::Vector2u ScreenSize;
inline float gravity = 0.97f;

#endif // !GLOBAL
