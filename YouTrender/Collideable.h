#pragma once

#include <SFML/Graphics.hpp>

class Collideable
{
protected:
	sf::FloatRect aabb_;
public:
	Collideable(const sf::FloatRect &aabb);
	Collideable(float x, float y, float width, float height);

	//	Wrapper functions
	bool isColliding(const Collideable &other) const;
	bool isColliding(const sf::FloatRect &other) const;
	//Point collisions (useful for mouse collisions)
	bool isColliding(const sf::Vector2f &point) const;
	bool isColliding(const sf::Vector2i &point) const;
	bool isColliding(float x, float y) const;

	void setPosition(float x, float y);
	void setSize(float width, float height);

	const sf::FloatRect &getAABB() const;
	sf::FloatRect &getAABB();
};