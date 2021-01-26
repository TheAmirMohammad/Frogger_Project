#pragma once
#ifndef Car_hpp
#define Car_hpp

#include <SFML/Graphics.hpp>
#include <string>

class Frog;

namespace sf
{
	class RenderWindow;
}

class Car : public sf::Drawable, public sf::Transformable {
public:
	
	Car(std::string path, sf::Vector2f position, int speed, int lane);
	bool Update(sf::RenderWindow& window, float DeltaTime, Frog* FrogObj);
	float GetCarPositionY();
	float GetCarPositionX(int width);
	std::string GetTexturePath();
	int GetCarSpeed();
	int GetCarWidth();
	int GetCarLane();
	void Reset();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Texture CarTexture;
	sf::Sprite CarSprite;
	sf::Vector2f CarPrimaryPosition;
	int CarSpeed;
	int CarLane;
	std::string CarTexturePath;

};


#endif /* Car_hpp */