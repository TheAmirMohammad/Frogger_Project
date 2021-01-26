#pragma once
#ifndef Frog_hpp
#define Frog_hpp

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <iostream>
#include <string>

namespace sf
{
	class RenderWindow;
}

class Frog : public sf::Drawable, public sf::Transformable {
public:

	Frog(std::string path, sf::Vector2f position);
	void DrawFrog(sf::RenderWindow& window);
	void HandleFrogMovement(sf::RenderWindow& window);
	void Reset();

private:

	sf::Sprite FrogSprite;
	sf::Texture FrogTexture;
	sf::Vector2f FrogPrimaryPosition;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	friend class Car;

};

#endif /* Frog_hpp */