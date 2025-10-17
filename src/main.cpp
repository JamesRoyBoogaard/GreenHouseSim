
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Greenhouse.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 850), "The Simulation");
    Greenhouse greenhouse;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        std::cout << "Mouse: " << mousePos.x << ", " << mousePos.y << "\n";

        window.clear();
        greenhouse.draw(window);
        window.display();
    }

    return 0;
}
