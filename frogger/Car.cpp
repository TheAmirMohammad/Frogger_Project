#include "Car.hpp"
#include <iostream>
#include "Frog.hpp"

Car::Car(std::string path, sf::Vector2f position, int speed, int lane) {
	if (!CarTexture.loadFromFile(path))
	{
		std::cout << path << " don't exsist" << '\n';
	}
	else
	CarSprite.setTexture(CarTexture);
	CarSprite.setPosition(position);
	CarPrimaryPosition = position;
	CarSpeed = speed;
	CarTexturePath = path;
	CarLane = lane;
}

bool Car::Update(sf::RenderWindow& window, float DeltaTime,Frog* FrogObj) {
	
	CarSprite.move(CarSpeed * DeltaTime,0);
	if (CarSprite.getGlobalBounds().intersects(FrogObj->FrogSprite.getGlobalBounds()))
	{
		FrogObj->Reset();
		FrogObj->CarCollisionSound();
	}

	if (CarSprite.getPosition().x > window.getSize().x + 3*Game_Cell_Size|| CarSprite.getPosition().x < -3*Game_Cell_Size)
	{ 
		return true;
	}
	return false;
}

void Car::Reset()
{
	CarSprite.setPosition(CarPrimaryPosition);
}

void Car::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(CarSprite, states);
} 

float Car::GetCarPositionY() {
	return(CarSprite.getPosition().y);
}

float Car::GetCarPositionX(int width) {
	if (GetCarSpeed() > 0)
	{
		std::cout << "Mosbat\n";
		return(-CarSprite.getGlobalBounds().width);
	}
	else
	{
		std::cout << "Manfi\n";
		return(width);
	}
}

std::string Car::GetTexturePath() {
	return (CarTexturePath);
}

int Car::GetCarSpeed() {
	return (CarSpeed);
}

int Car::GetCarWidth() {
	return(CarSprite.getGlobalBounds().width);
}

int Car::GetCarLane() {
	return(CarLane);
}