// frogger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main()
{
    RenderWindow window(VideoMode(1120, 800), "Frogger" , Style::Titlebar | Style::Close);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window.close();
            default:
                break;
            }    
        }

        //to clear the page
        window.clear();
        
        //to set the changes
        window.display();
    }

    return 0;
}
