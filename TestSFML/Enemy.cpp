#include "Enemy.h"


Enemy::Enemy(Vector2f position, Vector2f velosity, TextureStorage& textures,float radius) 
{
	body.setTexture(&textures.enemy);
	body.setPosition(position);
	body.setRadius(radius);
	this->velosity = velosity;
}
Enemy::~Enemy()
{
}

void Enemy::update(float dt)
{
	body.move(velosity * dt);
}

void Enemy::draw(RenderWindow& window)
{
	window.draw(body);
}

Vector2f Enemy::getPosition() const
{
	return body.getPosition();
}

Vector2f Enemy::getVelosity() const
{
	return velosity;
}

FloatRect Enemy::getGlobalBounds()const
{
	return body.getGlobalBounds();
}

float Enemy::getRadius() const
{
	return body.getRadius();
}
