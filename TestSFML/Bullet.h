#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
using namespace std;
using namespace sf;
class Bullet
{
public:
	Bullet(Vector2f position, Vector2f velocity);
	virtual ~Bullet();

	void update(float dt);
	void draw(RenderWindow& window);
	void shiftHorizontalVelosity();

	Vector2f getPosition() const;
	Bullet& operator=(const Bullet& bullet);
	const float BULET_RADIUS = 5.f;

private:
	Vector2f velocity;

	CircleShape body;

};

