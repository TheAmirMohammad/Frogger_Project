#include "Log.hpp"
#include <iostream>
#include "Frog.hpp"

Log::Log(std::string path, sf::Vector2f position, int speed, int lane) {
	if (!LogTexture.loadFromFile(path))
	{
		std::cout << path << " don't exsist" << '\n';
	}
	else
	LogSprite.setTexture(LogTexture);
	LogSprite.setPosition(position);
	LogPrimaryPosition = position;
	LogSpeed = speed;
	LogTexturePath = path;
	LogLane = lane;
}

int Log::GetLogLane() {
	return(LogLane);
}

bool Log::Update(sf::RenderWindow& window, float DeltaTime, Frog* FrogObj) {

	LogSprite.move(LogSpeed * DeltaTime, 0);

	if (LogSprite.getGlobalBounds().intersects(FrogObj->FrogSprite.getGlobalBounds()))
	{
		FrogObj->FrogSprite.move(LogSpeed * DeltaTime, 0);
	}
	/* if (FrogObj->getLane() >= 1 && FrogObj->getLane() <= 4)
	{
		if (FrogObj->isMoving())
		{
			static int i = 1;
			std::cout << i << " : dead" << std::endl;
			i++;
		}
	} */

	int x = 4;
	if (LogSprite.getPosition().x > window.getSize().x + x * Game_Cell_Size || LogSprite.getPosition().x < -x * Game_Cell_Size)
	{
		return true;
	}
	return false;
	
}

void Log::Reset()
{
	LogSprite.setPosition(LogPrimaryPosition);
}

void Log::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(LogSprite, states);
}

float Log::GetLogPositionY() {
	return(LogSprite.getPosition().y);
}

float Log::GetLogPositionX(int width) {
	if (GetLogSpeed() > 0)
	{
		std::cout << "Mosbat\n";
		return(-LogSprite.getGlobalBounds().width);
	}
	else
	{
		std::cout << "Manfi\n";
		return(width);
	}
}

std::string Log::GetTexturePath() {
	return (LogTexturePath);
}

int Log::GetLogSpeed() {
	return (LogSpeed);
}

int Log::GetLogWidth() {
	return(LogSprite.getGlobalBounds().width);
}