#include "Game.hpp"
#include "SFML/Graphics.hpp"

sf::RectangleShape water;

Game::Game():GameWindow(Width_Game_Window, Height_Game_Window, Title_Game_Window) {

	srand(time(NULL));
	sf::Color waterColor =sf::Color::Color(0 , 134 , 163);
	water.setSize(sf::Vector2f(Width_Game_Window, 5.5 * Game_Cell_Size));
	water.setPosition(0, 0);
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
	TopPathSprite.setPosition(WindowWidth / 2, 0);

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

	for (int i = 0; i < Log_Lanes_Number; i++)
	{
		TempXDistance = Game_Cell_Size*1.5;
		for (int j = 0; j < Log_Lane_LogsNumber; j++)
		{
			LogsSet.emplace_back(new Log(LogsLaneNameSet[i], sf::Vector2f(TempXDistance + (WindowWidth / Log_Lane_LogsNumber), WindowHeight - (i + 8) * Game_Cell_Size), LogsSpeedSet[i], i));
			TempXDistance += 1.2*(WindowWidth / Log_Lane_LogsNumber);
		}
	}

	for (int i = 0; i < Car_Lanes_Number; i++)
	{
		TempXDistance = Game_Cell_Size;
		for (int j = 0; j < Car_Lane_CarsNumber; j++)
		{
			CarsSet.emplace_back(new Car(CarsLaneNameSet[i], sf::Vector2f(TempXDistance + (WindowWidth / Car_Lane_CarsNumber), WindowHeight - (i+2) * Game_Cell_Size), CarsSpeedSet[i],i));
			TempXDistance += (WindowWidth / Car_Lane_CarsNumber);
		}
	}
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
}

void Game::LateUpdate() {

}

void Game::Draw() {
	GameWindow.BeginDraw();
	GameWindow.Draw(water);
	GameWindow.Draw(StreetPathSprite);
	GameWindow.Draw(FootPathSprite);
	GameWindow.Draw(MiddlePathSprite);
	GameWindow.Draw(TopPathSprite);
	for (int i = 0; i < LogsSet.size(); i++)
	{
		GameWindow.Draw(*LogsSet[i]);
	}
	for (int i = 0; i < CarsSet.size() ; i++)
	{
		GameWindow.Draw(*CarsSet[i]);
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