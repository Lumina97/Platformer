#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include "SFML/Audio.hpp"

using namespace sf;

class SoundEngine
{
public:
	SoundEngine();
	void PlayMusic();
	void PlayPongSound();

private:

	const std::string musicFilePath = "Resources/music.wav";
	const std::string pongFilePath = "Resources/pong.wav";
	Music music;
	SoundBuffer buffer;
	Sound sound;

};

#endif // !SOUNDENGINE_H
