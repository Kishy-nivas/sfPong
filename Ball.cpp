#include <SFML\Graphics.hpp>

#include <random>

#include "Ball.h"
#include "Entity.h"
#include "Game.h"

const float Ball::Speed = 200.f;

Ball::Ball(float radius)
: Entity(Entities::Ball, sf::Vector2f(Game::Width / 2 - radius, Game::Height / 2 - radius)),
radius_(radius), velocity_(getRandomVelocity())
{
	shape_.setRadius(radius_);
	shape_.setPosition(position_);
	shape_.setFillColor(sf::Color::Red);
}

sf::Vector2f Ball::getRandomVelocity()
{
	sf::Vector2f vel;

	static std::default_random_engine engine;
	static std::uniform_int_distribution<int> distribution(-1, 1);

	vel.x = distribution(engine);
	vel.y = distribution(engine);

	return vel;
}

void Ball::handleInput()
{

}

void Ball::checkCollisions()
{
	if (position_.x >= Game::Width - radius_ * 2)
		velocity_.x = -velocity_.x;
	if (position_.x <= 0)
		velocity_.x = -velocity_.x;
	if (position_.y <= 0)
		velocity_.y = -velocity_.y;
	if (position_.y >= Game::Height - radius_ * 2)
		velocity_.y = -velocity_.y;
}

void Ball::update(sf::Time delta)
{
	checkCollisions();

	position_ += velocity_ * Ball::Speed * delta.asSeconds();

	shape_.setPosition(position_);
}

void Ball::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}
