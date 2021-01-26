#pragma once
#ifndef Window_hpp
#define Window_hpp

#include <SFML/Graphics.hpp>

class Window
{
public:

	Window(const int width,const int height,const std::string& WindowName);
	void Update();
	void BeginDraw();
	void Draw(const sf::Drawable& drawable);
	void EndDraw();
	bool IsOpen() const;
	float WindowSizeX(); 
	float WindowSizeY();
	sf::RenderWindow MainWindow;

private:
	
};

#endif /* Window_hpp */
