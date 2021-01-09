// frogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<SFML/Graphics.hpp>

using namespace std;
using namespace sf;


int main()
{
    RenderWindow window(VideoMode(1120, 800), "Frogger" , Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);

    //frog
    RectangleShape frog;
    frog.setSize(Vector2f(80.f, 80.f));
    frog.setPosition(Vector2f(window.getSize().x/2, window.getSize().y - frog.getSize().y));
    frog.setFillColor(Color::Cyan);

    while (window.isOpen())
    {
        Event ev;
        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case Event::Closed:
                window.close();

            case Event::KeyPressed:
                switch (ev.key.code)
                {
                case Keyboard::Up:
                    if(frog.getPosition().y != 0.f)
                        frog.move(Vector2f(0.f, -80.f));
                    break;
                case Keyboard::Down:
                    if (frog.getPosition().y != window.getSize().y - frog.getSize().y)
                        frog.move(Vector2f(0.f, 80.f));
                    break;
                case Keyboard::Left:
                    if (frog.getPosition().x != 0.f)
                        frog.move(Vector2f(-80.f, 0.f));
                    break;
                case Keyboard::Right:
                    if (frog.getPosition().x != window.getSize().x - frog.getSize().x)
                        frog.move(Vector2f(80.f, 0.f));
                    break;
                default:
                    break;
                }

                break;
            default:
                break;
            }    
        }

        //to clear the page
        window.clear();

        window.draw(frog);
        //to set the changes
        window.display();
    }

    return 0;
}
