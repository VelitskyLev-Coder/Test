#pragma once
#include <SFML/Audio.hpp>
using namespace sf;
class SoundManager
{
private:
	SoundBuffer shot_b;
	SoundBuffer bounceOffWall_b;
	SoundBuffer explosion_b;
	SoundBuffer lvlup_b;
	SoundBuffer win_b;
	SoundBuffer fail_b;
public:
	SoundManager();
	Sound shot;
	Sound bounceOffWall;
	Sound explosion;
	Sound lvlup;
	Sound win;
	Sound fail;


};

