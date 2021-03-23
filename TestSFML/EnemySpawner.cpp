#include "EnemySpawner.h"


EnemySpawner::EnemySpawner() :
	distribution(0.f, 1.f)
{
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	timeSenceLastSpawn = 0.f;
}

bool EnemySpawner::readyToSpawn(float dt)
{
	timeSenceLastSpawn += dt;
	return timeSenceLastSpawn > TIME_TO_SPAWN;
}

Enemy EnemySpawner::spawn(list<Enemy>& enemys, TextureStorage& textures)
{
	float radius = distribution(generator) * (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS, x;
	bool flag;
	
	//no overlap generation
	int cur_attempt = 0, MAX_ATTEMPTS = 100;
	do{
		cur_attempt++;
		//cout << cur_attempt << endl;
		flag = false;
		x = distribution(generator) * (MAX_RIGHT - 2 * radius - MAX_LEFT) + MAX_LEFT;
		for (auto enemy : enemys)
		{
			Vector2f oldEnemyCanter = enemy.getPosition() + Vector2f(enemy.getRadius(), enemy.getRadius());
			Vector2f newEnemyCenter = Vector2f(x, -2 * radius) + Vector2f(radius, radius);
			Vector2f refresh = oldEnemyCanter - newEnemyCenter;
			float scalarProduct = refresh.x * refresh.x + refresh.y * refresh.y;
			if (scalarProduct * 0.95f < (radius + enemy.getRadius()) * (radius + enemy.getRadius()))
			{
 				flag = true;
				break;
			}
		}
		flag = flag * (cur_attempt <= MAX_ATTEMPTS);
		}while (flag);
	//////////////

	Vector2f position(x, -2 * radius);
	Vector2f veloity(0.f, ENEMY_FALL_VELOSITY);
	timeSenceLastSpawn = 0;
	return Enemy(position,veloity,textures,radius);
}

void EnemySpawner::reset()
{
	if (flag)
	{
		timeSenceLastSpawn = TIME_TO_SPAWN-4.0f;
		flag = false;
	}
}
