#include "Bullet.h"
#include <iostream>

Bullet::Bullet(Vector2f position, Vector2f velocity)
{
	body.setRadius(BULET_RADIUS);
	body.setPosition(position - Vector2f(BULET_RADIUS, BULET_RADIUS));
	body.setFillColor(Color::Green);
	body.setOutlineColor(Color::Black);
	body.setOutlineThickness(2);
	this->velocity = velocity;
}

Bullet::~Bullet()
{
}

void Bullet::update(float dt)
{

	body.setPosition(body.getPosition() + velocity * dt);

}

void Bullet::draw(RenderWindow& window)
{

	window.draw(body);

}

void Bullet::shiftHorizontalVelosity()
{
	velocity = Vector2f(-velocity.x, velocity.y);
}

Vector2f Bullet::getPosition() const
{
	return body.getPosition();
}

Bullet& Bullet::operator=(const Bullet& bullet)
{
	this->velocity=bullet.velocity;
	this->body=bullet.body;
	return *this;
}
