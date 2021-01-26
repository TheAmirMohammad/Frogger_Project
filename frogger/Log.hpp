#pragma once
#ifndef Log_hpp
#define Log_hpp

#include <SFML/Graphics.hpp>
#include <string>

class Frog;

namespace sf
{
	class RenderWindow;
}

class Log : public sf::Drawable, public sf::Transformable {
public:

	Log(std::string path, sf::Vector2f position, int speed, int lane);
	bool Update(sf::RenderWindow& window, float DeltaTime, Frog* FrogObj);
	float GetLogPositionY();
	float GetLogPositionX(int width);
	std::string GetTexturePath();
	int GetLogSpeed();
	int GetLogWidth();
	int GetLogLane();
	void Reset();

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	sf::Texture LogTexture;
	sf::Sprite LogSprite;
	sf::Vector2f LogPrimaryPosition;
	int LogSpeed;
	int LogLane;
	std::string LogTexturePath;
};

#endif /* Log_hpp */