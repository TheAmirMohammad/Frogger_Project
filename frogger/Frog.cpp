#include "Frog.hpp"
#include "Game.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

using namespace std::chrono_literals;

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
	heart_count = Heart_Number;
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
	heart_count--;
	FrogSprite.setRotation(0);
	FrogSprite.setPosition(FrogPrimaryPosition);
}

void Frog::Reset_Frog()
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

void Frog::HandleFrogMovement(sf::RenderWindow& GameWindow)
{
	if (heart_count == 0)
	{
		std::this_thread::sleep_for(4000ms);
		GameWindow.close();
	}
	sf::Event EventListener;
	while (GameWindow.pollEvent(EventListener))
	{
		switch (EventListener.type)
		{
		case sf::Event::KeyReleased:
			switch (EventListener.key.code)
			{
			case sf::Keyboard::Space:
				std::cout << FrogSprite.getPosition().x << std::endl;
				break;
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

