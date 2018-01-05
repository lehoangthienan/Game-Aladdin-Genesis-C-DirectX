#include "GameSound.h"


GameSound* GameSound::instance_ = nullptr;


GameSound::GameSound()
{
}


GameSound::~GameSound()
{

	loadedSound_.clear();
}

void GameSound::initialize(HWND windowsHandler)
{
	Sound::initializeSoundClass(windowsHandler);
}


void GameSound::play(string soundLink, bool repeat /*= false*/, bool playFromStart /*= true*/)
{
	try
	{
		if (playFromStart)
			loadedSound_.at(soundLink)->stop();

		loadedSound_.at(soundLink)->play(repeat);
	}
	catch (exception)
	{
		loadedSound_.insert(SoundPair(soundLink, new Sound((char*)soundLink.c_str())));
		loadedSound_.at(soundLink)->play(repeat);
	}
}

GameSound* GameSound::getInstance()
{
	if (instance_ == 0)
	{
		instance_ = new GameSound();
	}

	return instance_;
}




void GameSound::stop(string soundLink)
{
	try
	{
		loadedSound_.at(soundLink)->stop();
	}
	catch (exception)
	{

	}
}

