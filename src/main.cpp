
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "Greenhouse.hpp"
#include "Airflow.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1400, 850), "The Simulation");
    Greenhouse greenhouse;
    Airflow airflow;
    sf::Vector2f intake = {1106, 185};
    std::vector<Airflow::Directional_line> lines;
    std::vector<Airflow::Offshoot_line> offshoot_lines;
    sf::Vector2f velocity = {-8,0};
    auto last_dl = std::chrono::steady_clock::now();
    auto last_ol = std::chrono::steady_clock::now().operator+=(std::chrono::steady_clock::duration(1000));
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        auto now = std::chrono::steady_clock::now();
        auto time_elapsed_dl = std::chrono::duration_cast<std::chrono::seconds>(now - last_dl);
        auto time_elapsed_ol = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_ol);    
        // sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // std::cout << "Mouse: " << mousePos.x << ", " << mousePos.y << "\n";

        window.clear();
        greenhouse.draw(window);
        window.display();
    }

    return 0;
}
