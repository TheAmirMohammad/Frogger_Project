#include "Game.hpp"
#include <string>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

sf::RectangleShape water;
int score = 0;
bool over = false;

Game::Game():GameWindow(Width_Game_Window, Height_Game_Window, Title_Game_Window) {
	srand(time(NULL));
	
	if (!font.loadFromFile(FontPath))
	{
		std::cout << "ERROR Reglisse.otf NOT FOUND!" << std::endl;
	}
	Score.setFont(font);
	Score.setCharacterSize(40);
	Score.setFillColor(sf::Color::White);
	Score.setString("Score " + std::to_string(score));
	Score.setOrigin(Score.getGlobalBounds().width , Score.getGlobalBounds().height);
	Score.setPosition(Width_Game_Window - Game_Cell_Size, 30);

	gameOver.setFont(font);
	gameOver.setCharacterSize(150);
	gameOver.setFillColor(sf::Color::White);
	gameOver.setOrigin(gameOver.getGlobalBounds().width/2, gameOver.getGlobalBounds().height/2);
	gameOver.setPosition(50, 200);
	
	sf::Color waterColor =sf::Color::Color(0 , 134 , 163);
	water.setSize(sf::Vector2f(Width_Game_Window, 5.5 * Game_Cell_Size));
	water.setPosition(0, Game_Cell_Size);
	water.setFillColor(waterColor);

	StreetPathTexture.loadFromFile(StreetBackground_File_Path);
	StreetPathSprite.setTexture(StreetPathTexture);
	StreetPathSprite.setPosition(WindowWidth / 2 , Height_Game_Window - 6*Game_Cell_Size );

	FootPathTexture.loadFromFile(FootPathBackground_File_Path);
	FootPathSprite.setTexture(FootPathTexture);
	FootPathSprite.setPosition(WindowWidth / 2, Height_Game_Window - Game_Cell_Size);

	MiddlePathTexture.loadFromFile(MiddlePathBackground_File_Path);
	MiddlePathSprite.setTexture(FootPathTexture);
	MiddlePathSprite.setPosition(WindowWidth / 2, Height_Game_Window - 7*Game_Cell_Size);

	TopPathTexture.loadFromFile(TopPathBackground_File_Path);
	TopPathSprite.setTexture(TopPathTexture);
	TopPathSprite.setPosition(WindowWidth / 2, Game_Cell_Size);

	WindowWidth = GameWindow.WindowSizeX();
	WindowHeight = GameWindow.WindowSizeY();

	FrogObject = new Frog(Frog_File_Path, sf::Vector2f(WindowWidth/2, WindowHeight - Game_Cell_Size/2));
	
	//log speed
	LogsSpeedSet[0] = Log_Lane_1_Speed;
	LogsSpeedSet[1] = Log_Lane_2_Speed;
	LogsSpeedSet[2] = Log_Lane_3_Speed;
	LogsSpeedSet[3] = Log_Lane_4_Speed;
	//log lane
	LogsLaneNameSet[0] = Log_Lane_1_LogFilePath;
	LogsLaneNameSet[1] = Log_Lane_2_LogFilePath;
	LogsLaneNameSet[2] = Log_Lane_3_LogFilePath;
	LogsLaneNameSet[3] = Log_Lane_4_LogFilePath;

	//car speed
	CarsSpeedSet[0] = Car_Lane_1_Speed;
	CarsSpeedSet[1] = Car_Lane_2_Speed;
	CarsSpeedSet[2] = Car_Lane_3_Speed;
	CarsSpeedSet[3] = Car_Lane_4_Speed;
	CarsSpeedSet[4] = Car_Lane_5_Speed;
	//car lane
	CarsLaneNameSet[0] = Car_Lane_1_CarFilePath;
	CarsLaneNameSet[1] = Car_Lane_2_CarFilePath;
	CarsLaneNameSet[2] = Car_Lane_3_CarFilePath;
	CarsLaneNameSet[3] = Car_Lane_4_CarFilePath;
	CarsLaneNameSet[4] = Car_Lane_5_CarFilePath;

	HeartPathTexture.loadFromFile(Heart_FilePath);
	for (int i = 0; i < FrogObject->heart_count; i++)
	{
		HeartPathSprite[i].setTexture(HeartPathTexture);
		HeartPathSprite[i].setPosition(i*(Game_Cell_Size-10), 0);
	}

	for (int i = 0; i < Log_Lanes_Number; i++)
	{
		TempXDistance = Game_Cell_Size*1.5;
		for (int j = 0; j < Log_Lane_LogsNumber; j++)
		{
			LogsSet.emplace_back(new Log(LogsLaneNameSet[i], sf::Vector2f(TempXDistance, WindowHeight - (i + 8) * Game_Cell_Size), LogsSpeedSet[i], i));
			TempXDistance += 1.2*(WindowWidth / Log_Lane_LogsNumber);
		}
	}

	for (int i = 0; i < Car_Lanes_Number; i++)
	{
		TempXDistance = Game_Cell_Size * 1.5;
		for (int j = 0; j < Car_Lane_CarsNumber; j++)
		{
			CarsSet.emplace_back(new Car(CarsLaneNameSet[i], sf::Vector2f(TempXDistance, WindowHeight - (i+2) * Game_Cell_Size), CarsSpeedSet[i],i));
			TempXDistance += (WindowWidth / Car_Lane_CarsNumber);
		}
	}

	if (!MusicBuffer.loadFromFile(Music_File_Path))
	{
		std::cout << "ERROR sound-frogger-music NOT FOUND!" << std::endl;
	}
	MusicSound.setBuffer(MusicBuffer);
	MusicSound.setLoop(true);
	MusicSound.play();
}

void Game::Update() {
	GameWindow.Update();
	for (int i = 0; i < LogsSet.size(); i++)
	{
		if (LogsSet[i]->Update(GameWindow.MainWindow, DeltaTime, FrogObject )) {
			if (LogsSet[i]->GetLogSpeed() > 0)
			{
				LogsSet.emplace_back(new Log(LogsSet[i]->GetTexturePath(), sf::Vector2f(-LogsSet[i]->GetLogWidth(), LogsSet[i]->GetLogPositionY()), LogsSet[i]->GetLogSpeed(), LogsSet[i]->GetLogLane()));
			}
			else
			{
				LogsSet.emplace_back(new Log(LogsSet[i]->GetTexturePath(), sf::Vector2f(Width_Game_Window, LogsSet[i]->GetLogPositionY()), LogsSet[i]->GetLogSpeed(), LogsSet[i]->GetLogLane()));
			}
			LogsSet.erase(LogsSet.begin() + i);
		}
	}
	for (int i = 0; i < CarsSet.size(); i++)
	{
		if (CarsSet[i]->Update(GameWindow.MainWindow, DeltaTime, FrogObject)) {
			if (CarsSet[i]->GetCarSpeed() > 0)
			{
				CarsSet.emplace_back(new Car(CarsSet[i]->GetTexturePath(), sf::Vector2f(-CarsSet[i]->GetCarWidth(), CarsSet[i]->GetCarPositionY()), CarsSet[i]->GetCarSpeed(), CarsSet[i]->GetCarLane()));
			}
			else
			{
				CarsSet.emplace_back(new Car(CarsSet[i]->GetTexturePath(), sf::Vector2f(Width_Game_Window, CarsSet[i]->GetCarPositionY()), CarsSet[i]->GetCarSpeed(), CarsSet[i]->GetCarLane()));
			}
			CarsSet.erase(CarsSet.begin() + i);
		}
	}
	if (FrogObject->getLane() == 1)
	{
		if (FrogObject->FrogSprite.getPosition().x >= 35 && FrogObject->FrogSprite.getPosition().x <= 152)
		{
			score++;
			Score.setString("Score " + std::to_string(score));
			FrogObject->Reset_Frog();
		} else if (FrogObject->FrogSprite.getPosition().x >= 323 && FrogObject->FrogSprite.getPosition().x <= 444)
		{
			score++;
			Score.setString("Score " + std::to_string(score));
			FrogObject->Reset_Frog();
		} else if (FrogObject->FrogSprite.getPosition().x >= 615 && FrogObject->FrogSprite.getPosition().x <= 735)
		{
			score++;
			Score.setString("Score " + std::to_string(score));
			FrogObject->Reset_Frog();
		}
		else
		{
			FrogObject->Reset();
		}
	}
	if (FrogObject->getLane() >= 2 && FrogObject->getLane() <= 5)
	{
		if (FrogObject->logcollision(LogsSet) == false)
		{
			FrogObject->Reset();
		}
	}
	if (FrogObject->FrogSprite.getPosition().x > WindowWidth || FrogObject->FrogSprite.getPosition().x < 0 || FrogObject->FrogSprite.getPosition().y > WindowHeight || FrogObject->FrogSprite.getPosition().y < Game_Cell_Size)
	{
		FrogObject->Reset();
	}
	if (FrogObject->heart_count == 0)
	{
		over = true;
	}
}

void Game::Draw() {
	GameWindow.BeginDraw();
	GameWindow.Draw(Score);
	GameWindow.Draw(water);
	GameWindow.Draw(StreetPathSprite);
	GameWindow.Draw(FootPathSprite);
	GameWindow.Draw(MiddlePathSprite);
	GameWindow.Draw(TopPathSprite);

	for (int i = 0; i < FrogObject->heart_count; i++)
	{
		GameWindow.Draw(HeartPathSprite[i]);
	}

	for (int i = 0; i < LogsSet.size(); i++)
	{
		GameWindow.Draw(*LogsSet[i]);
	}
	for (int i = 0; i < CarsSet.size() ; i++)
	{
		GameWindow.Draw(*CarsSet[i]);
	}
	if (over)
	{
		gameOver.setString("Game Over!\nScore : " + std::to_string(score));
		GameWindow.Draw(gameOver);
	}
	GameWindow.Draw(*FrogObject);
	GameWindow.EndDraw();
}

bool Game::IsRunning() const
{
	return GameWindow.IsOpen();
}

void Game::CalculateDeltaTime()
{
	DeltaTime = GameClock.restart().asSeconds();
}

void Game::MoveFrog() {
	FrogObject->HandleFrogMovement(GameWindow.MainWindow);
}
