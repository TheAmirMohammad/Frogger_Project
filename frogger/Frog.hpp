#pragma once
#ifndef Frog_hpp
#define Frog_hpp

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.hpp"
#include "Log.hpp"
#include <iostream>
#include <string>

namespace sf
{
	class RenderWindow;
}

class Frog : public sf::Drawable, public sf::Transformable {
public:

	Frog(std::string path, sf::Vector2f position);
	int getLane();
	bool isMoving();
	void DrawFrog(sf::RenderWindow& window);
	void HandleFrogMovement(sf::RenderWindow& window);
	bool logcollision(std::vector<Log*>& logsetvector);
	void CarCollisionSound();
	void Reset();

private:
	sf::Sprite FrogSprite;
	sf::Texture FrogTexture;
	sf::Vector2f FrogPrimaryPosition;
	sf::SoundBuffer HopBuffer;
	sf::Sound HopSound;
	sf::SoundBuffer PlunkBuffer;
	sf::Sound PlunkSound;
	sf::SoundBuffer SquashBuffer;
	sf::Sound SquashSound;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	friend class Car;
	friend class Log;
	friend class Game;
};

#endif /* Frog_hpp */