#pragma once
#include "Enemy.h"
#include <list>
#include <random>
#include <chrono>
#include <iostream>

using namespace std;
using namespace sf;
class EnemySpawner
{
public:
	EnemySpawner();

	bool readyToSpawn(float dt);
	Enemy spawn(list<Enemy>& enemys,TextureStorage& textures);
	void reset();
	float MAX_RADIUS=35.f;
	float MIN_RADIUS=15.f;
	float TIME_TO_SPAWN = 0.15f;
	float ENEMY_FALL_VELOSITY = 150.f;
private:
	
	const float MAX_LEFT = 0.f;
	const float MAX_RIGHT = 600.f;

	bool flag = true;

	float timeSenceLastSpawn;

	default_random_engine generator;
	uniform_real_distribution<float> distribution;
};

