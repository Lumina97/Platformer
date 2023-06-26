#include "SoundEngine.h"
#include <iostream>

SoundEngine::SoundEngine()
{
	if(!music.openFromFile(musicFilePath)) {}
	if(!buffer.loadFromFile(pongFilePath)) {}
}

void SoundEngine::PlayMusic()
{		 
	music.play();
}

void SoundEngine::PlayPongSound()
{
	sound.setVolume(100.0f);
	sound.setBuffer(buffer);
	sound.play();
}
