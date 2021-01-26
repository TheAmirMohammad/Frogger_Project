#include "Frog.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

int Frog::getLane()
{
	return FrogSprite.getPosition().y / Game_Cell_Size;
}

bool Frog::isMoving()
{
	static bool n = true;
	static sf::Vector2f pos1;
	if(n) pos1 = FrogSprite.getPosition();
	n = false;

	sf::Vector2f pos2 = FrogSprite.getPosition();
	
	if (pos1 == pos2)
		return false;
	else
	{
		pos1 = pos2;
		return true;
	}
}

Frog::Frog(std::string path, sf::Vector2f position)
{
	if (!FrogTexture.loadFromFile(path))
	{
		std::cout << path << " don't exsist" << '\n';
	}
	else
	{
		FrogSprite.setTexture(FrogTexture);
		FrogSprite.setPosition(position);
		FrogPrimaryPosition = position;
	}
	FrogSprite.setOrigin(sf::Vector2f(FrogSprite.getGlobalBounds().width / 2, FrogSprite.getGlobalBounds().height / 2));
}

void Frog::HandleFrogMovement(sf::RenderWindow& GameWindow)
{
	sf::Event EventListener;
	while (GameWindow.pollEvent(EventListener))
	{
		switch (EventListener.type)
		{
			case sf::Event::KeyReleased:
			switch (EventListener.key.code)
			{
			case sf::Keyboard::Up:
				FrogSprite.move(0, -FrogSprite.getGlobalBounds().height);
				FrogSprite.setRotation(0);
				break;
			case sf::Keyboard::Down:
				FrogSprite.move(0, FrogSprite.getGlobalBounds().height);
				FrogSprite.setRotation(180);
				break;
			case sf::Keyboard::Left:
				FrogSprite.move(-FrogSprite.getLocalBounds().width, 0);
				FrogSprite.setRotation(270);
				break;
			case sf::Keyboard::Right:
				FrogSprite.move(FrogSprite.getGlobalBounds().height, 0);
				FrogSprite.setRotation(90);
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

void Frog::DrawFrog(sf::RenderWindow& window)
{
	window.draw(*this);
} 

void Frog::Reset()
{
	FrogSprite.setRotation(0);
	FrogSprite.setPosition(FrogPrimaryPosition);
}

void Frog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(FrogSprite,states);
}