#include "Collideable.h"

Collideable::Collideable(const sf::FloatRect &aabb) :
	aabb_(aabb)
{}

Collideable::Collideable(float x, float y, float width, float height) :
	aabb_(x, y, width, height)
{}

bool Collideable::isColliding(const Collideable &other) const
{
	return aabb_.intersects(other.aabb_);
}

bool Collideable::isColliding(const sf::FloatRect &other) const
{
	return aabb_.intersects(other);
}

bool Collideable::isColliding(const sf::Vector2f &point) const
{
	return aabb_.contains(point);
}

bool Collideable::isColliding(const sf::Vector2i &point) const
{
	return aabb_.contains(static_cast<float>(point.x), static_cast<float>(point.y));
}

bool Collideable::isColliding(float x, float y) const
{
	return aabb_.contains(x, y);
}

void Collideable::setPosition(float x, float y)
{
	aabb_.left = x;
	aabb_.top = y;
}

void Collideable::setSize(float width, float height)
{
	aabb_.width = width;
	aabb_.height = height;
}

const sf::FloatRect &Collideable::getAABB() const
{
	return aabb_;
}

sf::FloatRect &Collideable::getAABB()
{
	return aabb_;
}