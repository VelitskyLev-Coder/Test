#include "Player.h"

using namespace sf;
using namespace std;
Player::Player(TextureStorage& textures)
{
	body.setTexture(&textures.player);
	//body.setScale(0.2f, 0.2f);
	body.setPosition(Vector2f((MAX_RIGHT - MAX_LEFT) / 2 - body.getGlobalBounds().width / 2,
		DOWN_POSITION - body.getGlobalBounds().height));
	body.setSize(Vector2f(84.f, 170.4f));
	timeSinceLastShot = 0.f;
	velocity = 0.f;
	acceleration = 0.f;
	isShot=false;

}
Player::~Player()
{
}

void Player::sendAction(Actions action)
{
	switch (action)
	{
	case Player::Actions::LEFT:
		acceleration = -MAX_ACCELERATION;
		break;
	case Player::Actions::RIGHT:
		acceleration = MAX_ACCELERATION;
		break;
	case Player::Actions::SHOOT:
		if (timeSinceLastShot >= TIME_FOR_REPEAT_SHOT)
		{
			isShot = true;
		}
		break;
	default:
		break;
	}
}

void Player::update(float dt, list<Bullet>& bullets, Sound& sound)
{
	
	//velocity
	if (acceleration == 0)
	{
		if (velocity < 0)
			velocity = min(0.f, velocity + FRICTION_ACCELERATION*dt);
		if (velocity > 0)
			velocity = max(0.f, velocity - FRICTION_ACCELERATION*dt);
	}
	else if (abs(velocity + acceleration * dt) < MAX_VELOCITY)
		velocity = velocity + acceleration * dt;
	acceleration = 0;

	//position
	float newY = DOWN_POSITION - body.getGlobalBounds().height;
	float dx = velocity * dt;
	float newX = body.getPosition().x + dx;
	if (newX < MAX_LEFT)
	{
		newX = MAX_LEFT;
		velocity = -velocity * 0.5;
	}
	else if (newX > MAX_RIGHT - body.getGlobalBounds().width)
	{
		newX = MAX_RIGHT - body.getGlobalBounds().width;
		velocity = -velocity * 0.5;
	}
	body.setPosition(newX, newY);
	
	//shooting
	timeSinceLastShot += dt;
	if (isShot)
	{
		bullets.push_back(shot());
		isShot = false;
		sound.play();
	}

	
}

void Player::draw(RenderWindow& window)
{
	window.draw(body);
}

Bullet Player::shot()
{
	timeSinceLastShot = 0;
	return Bullet(body.getPosition()+Vector2f(body.getGlobalBounds().width*0.5f,0.f),
		Vector2f(velocity,-SHOT_VELOCITY));
}

FloatRect Player::getGlobalBounds() const
{
	return FloatRect(body.getPosition().x + 5.f, body.getPosition().y + 40.f, 74.f, 130.f);
}


