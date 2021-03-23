#include "SoundManager.h"

SoundManager::SoundManager()
{
	fail_b.loadFromFile("Sounds/fail.wav");
	lvlup_b.loadFromFile("Sounds/lvlup.wav");
	explosion_b.loadFromFile("Sounds/explosion.wav");
	win_b.loadFromFile("Sounds/win.wav");
	bounceOffWall_b.loadFromFile("Sounds/wall.wav");
	shot_b.loadFromFile("Sounds/shot.wav");

	fail.setBuffer(fail_b);
	lvlup.setBuffer(lvlup_b);
	explosion.setBuffer(explosion_b);
	win.setBuffer(win_b);
	bounceOffWall.setBuffer(bounceOffWall_b);
	shot.setBuffer(shot_b);

	shot.setVolume(50);
}
