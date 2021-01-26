#include "Window.hpp"

Window::Window(const int width,const int height,const std::string& windowName):MainWindow(sf::VideoMode(width, height), windowName, sf::Style::Titlebar | sf::Style::Close)
{
	MainWindow.setVerticalSyncEnabled(true);
}

void Window::Update()
{
	sf::Event EventListener;
	if (MainWindow.pollEvent(EventListener))
	{
		if (EventListener.type == sf::Event::Closed)
		{
			MainWindow.close();
		}
	}
}

void Window::BeginDraw()
{
	MainWindow.clear(sf::Color::Black);
}

void Window::Draw(const sf::Drawable& drawable)
{
	MainWindow.draw(drawable);
}

void Window::EndDraw()
{
	MainWindow.display();
}

bool Window::IsOpen() const
{
	return MainWindow.isOpen();
}

float Window::WindowSizeX() {
	return (MainWindow.getSize().x);
}

float Window::WindowSizeY() {
	return (MainWindow.getSize().y);
}