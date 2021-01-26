#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "GameDefinitions.hpp"
#include "Window.hpp"
#include "Frog.hpp"
#include "Car.hpp"

class Game {
public:
	Game();
	void Update();
	void LateUpdate();
	void Draw();
	bool IsRunning() const;
	void CalculateDeltaTime();
	void MoveFrog();
private:

	sf::Sprite FootPathSprite;
	sf::Texture FootPathTexture;

	sf::Sprite MiddlePathSprite;
	sf::Texture MiddlePathTexture;

	sf::Sprite TopPathSprite;
	sf::Texture TopPathTexture;

	Window GameWindow;
	std::vector<Car*> CarsSet;
	Frog* FrogObject;
	int CarsSpeedSet[Car_Lanes_Number];
	std::string CarsLaneNameSet[Car_Lanes_Number];
	int LaneRandDistance[Car_Lanes_Number];


	int TempXDistance = Game_Cell_Size;
	float WindowWidth = 0;
	float WindowHeight = 0;

	bool isPlaying = true;
	sf::Clock GameClock;
	float DeltaTime = 0;
	float y = 25.0f;
	int CarsNumber = 0;
	int XDistance = 0;
	int XExCar = 0;

	sf::Music music;
};