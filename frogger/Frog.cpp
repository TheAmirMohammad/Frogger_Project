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

	if (!HopBuffer.loadFromFile(HopSound_File_Path))
	{
		std::cout << "ERROR sound-frogger-hop NOT FOUND!" << std::endl;
	}
	HopSound.setBuffer(HopBuffer);
	HopSound.setLoop(false);

	if (!PlunkBuffer.loadFromFile(PlunkSound_File_Path))
	{
		std::cout << "ERROR sound-frogger-plunk NOT FOUND!" << std::endl;
	}
	PlunkSound.setBuffer(PlunkBuffer);
	PlunkSound.setLoop(false);

	if (!SquashBuffer.loadFromFile(SquashkSound_File_Path))
	{
		std::cout << "ERROR sound-frogger-squash NOT FOUND!" << std::endl;
	}
	SquashSound.setBuffer(SquashBuffer);
	SquashSound.setLoop(false);
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
				HopSound.play();
				break;
			case sf::Keyboard::Down:
				FrogSprite.move(0, FrogSprite.getGlobalBounds().height);
				FrogSprite.setRotation(180);
				HopSound.play();
				break;
			case sf::Keyboard::Left:
				FrogSprite.move(-FrogSprite.getLocalBounds().width, 0);
				FrogSprite.setRotation(270);
				HopSound.play();
				break;
			case sf::Keyboard::Right:
				FrogSprite.move(FrogSprite.getGlobalBounds().height, 0);
				FrogSprite.setRotation(90);
				HopSound.play();
				break;
			default:
				break;
			}
		default:
			break;
		}
	}
}

bool Frog::logcollision(std::vector<Log*>& logsetvector) {
	bool collision = false;
	for (int i = 0; i < logsetvector.size(); i++)
	{
		if (logsetvector[i]->LogSprite.getGlobalBounds().intersects(FrogSprite.getGlobalBounds()))
		{
			collision = true;
			break;
		}
	}
	if (collision == false)
	{
		PlunkSound.play();
	}
	return (collision);
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

void Frog::CarCollisionSound() {
	SquashSound.play();
}

void Frog::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(FrogSprite,states);
}