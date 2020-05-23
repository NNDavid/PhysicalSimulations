#include <QApplication>
#include <QFrame>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "mainmenu.h"
int main(int argc, char **argv)
{
    // create the window
    /*sf::RenderWindow window(sf::VideoMode(800, 400), "My window");
    sf::CircleShape circle;
    circle.setRadius(50);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(sf::Color::Red);
    float amplitude = window.getSize().x / 2.0;
    circle.setPosition(sf::Vector2f(window.getSize().x/2.0,window.getSize().y/2.0));
    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)  window.close();
            if (event.type == sf::Event::Resized)
                {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                    circle.setPosition( window.getSize().x / 2 , window.getSize().y / 2 );
                }
        }
        sf::Time elapsed = clock.getElapsedTime();

        window.clear(sf::Color::White);
        window.draw(circle);
        window.display();
    }
*/
    QApplication App(argc, argv);

    MainMenu program;
    program.show();
    return App.exec();
}
