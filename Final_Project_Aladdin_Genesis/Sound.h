#pragma once
#define AUDIO_FORMAT_TAG		WAVE_FORMAT_PCM
#define	AUDIO_NUM_OF_CHANNEL	2
#define AUDIO_SAMPLE_SPEED		22050
#define AUDIO_BITS_PER_SAMPLE	16
#define AUDIO_FLAGS				0
#define AUDIO_BUFFER_SIZE		640000
#define AUDIO_GUID				GUID_NULL
#define BACKGROUND_MUSIC "sound\\Ending.wav"
#define GAME1_MUSIC "sound\\man1.wav"
#define GAME2_MUSIC "sound\\bosstheme.wav"
#define CUT_MUSIC "sound\\Low Sword.wav"
#define THROW_MUSIC "sound\\Apple Splat.wav"
#define CAMEL_MUSIC "sound\\Camel Spit.wav"
#define HURT_MUSIC "sound\\Aladdin Hurt.wav"
#define APPLE_MUSIC "sound\\Apple Collect.wav"
#define APPLE_POP_MUSIC "sound\\Balloon Pop.wav"
#define SWORD_SWORD_MUSIC "sound\\Sword Ching.wav"
#define DIE_MUSIC "sound\\chet.wav"
#define JAFAR_HURT_MUSIC "sound\\Jafar Snake.wav"
#define SHOOT_MUSIC "sound\\shoot.wav"
#define NEXT_MUSIC "sound\\level_complete.wav"
#define JAFAR_HURT_MUSIC "sound\\Jafar Snake.wav"
#define GUARD_HIT_MUSIC "sound\\Guard Hit 1.wav"
#define THEEND_MUSIC "sound\\theend.wav"
#define POT_MUSIC "sound\\Clay Pot.wav"
#define COMEOUT_MUSIC "sound\\Coming Out.wav"
#define COMEIN_MUSIC "sound\\Continue Point.wav"
#define FIRE_MUSIC "sound\\Fire From Coal.wav"
#define LAMP_MUSIC "sound\\Splash.wav"
#define WOW_MUSIC "sound\\Wow!.wav"

#define AUDIO_BLOCK_ALIGN(bitPerSample, nChannels)		(WORD)(bitPerSample / 8 * nChannels)
#define AUDIO_AVERAGE_BPS(samplesPerSec, blockAlign)	(DWORD)(samplesPerSec * blockAlign)

#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dxguid.lib")

#include <sstream>
#include <iostream>
#include <dsound.h>
#include <vector>
#include "WaveFile.h"


class Sound
{
public:
	Sound(const char* audioPath);
	~Sound(void);

	static HRESULT initializeSoundClass(HWND windowsHandler);
	static HRESULT releaseSoundClass();

	HRESULT play(bool isLoop = false, DWORD priority = 0);
	HRESULT stop();


private:
	HRESULT loadAudio(const char* audioPath);

private:
	static WAVEFORMATEX bufferFormat_;
	static DSBUFFERDESC bufferDescription_;
	static LPDIRECTSOUND8 audioHandler_;
	static HWND windowsHandler_;

	LPDIRECTSOUNDBUFFER soundBuffer_;
};