#include "Game.hpp"

Game::Game():GameWindow(Width_Game_Window, Height_Game_Window, Title_Game_Window) {

	//srand(time(NULL));

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

	CarsSpeedSet[0] = Car_Lane_1_Speed;
	CarsSpeedSet[1] = Car_Lane_2_Speed;
	CarsSpeedSet[2] = Car_Lane_3_Speed;
	CarsSpeedSet[3] = Car_Lane_4_Speed;
	CarsSpeedSet[4] = Car_Lane_5_Speed;

	CarsLaneNameSet[0] = Car_Lane_1_CarFilePath;
	CarsLaneNameSet[1] = Car_Lane_2_CarFilePath;
	CarsLaneNameSet[2] = Car_Lane_3_CarFilePath;
	CarsLaneNameSet[3] = Car_Lane_4_CarFilePath;
	CarsLaneNameSet[4] = Car_Lane_5_CarFilePath;

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
	GameWindow.Draw(FootPathSprite);
	GameWindow.Draw(MiddlePathSprite);
	GameWindow.Draw(TopPathSprite);
	GameWindow.Draw(*FrogObject);
	for (int i = 0; i < CarsSet.size() ; i++)
	{
		GameWindow.Draw(*CarsSet[i]);
	}
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

/*Game::Game(int width, int height, std::string title)
{
	srand(time(NULL));
	game_window = new sf::RenderWindow(sf::VideoMode(width, height), title);

	if (!music.openFromFile("assets/music.ogg"))
	{
		std::cout << "assets / music.ogg is not exsist \n";
	}

	m_frog = new Frog("assets/life.png", sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y - 50));


	m_cars.emplace_back(new Car("assets/car1.png"    ,  sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 - 100), 100, 1));
	m_cars.emplace_back(new Car("assets/car2.png"    ,  sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 - 50), 100, 2));
	m_cars.emplace_back(new Car("assets/tractor.png" ,  sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2), 50, 1));
	m_cars.emplace_back(new Car("assets/truck.png"   ,  sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 + 50), 75, 2));
	m_cars.emplace_back(new Car("assets/car1.png"    ,  sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 + 100), 100, 1));
	m_cars.emplace_back(new Car("assets/car3.png"    ,  sf::Vector2f(m_window->getSize().x / 2, m_window->getSize().y / 2 + 150), 100, 2));

	
}

void Game::run()
{
	music.setLoop(true);
	music.setVolume(20);
	music.play();

	sf::Clock deltaClock;
	while (isPlaying)
	{
		m_frog->Update(*m_window, deltaTime);
		for (int i = 0; i < m_cars.size(); i++)
			m_cars[i]->Update(*m_window, deltaTime);


		m_frog->HandleEvent(*m_window);

		m_window->clear();

		m_frog->Draw(*m_window);
		for (int i = 0; i < m_cars.size(); i++)
			m_cars[i]->Draw(*m_window);

		m_window->display();

		deltaTime = deltaClock.restart().asSeconds();
	}
}

void Game::reset()
{
	m_frog->Reset();
	for (int i = 0; i < m_cars.size(); i++)
		m_cars[i]->Reset();
}

Game* Game::instance = nullptr;

void Game::constructor(int width, int height, std::string title)
{
	instance = new Game(width, height, title);
	Game::instance->run();
}

Game* Game::getInstance()
{
	if (instance == nullptr)
		std::cout << "You need to call constructor\n";

	return instance;
} */