
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
    sf::Vector2f direction = {5,0}; // for now hard coded but will be determined via culculation through an aircon struct later
    std::vector<Airflow::Directional_line> lines;
    auto last_line = std::chrono::steady_clock::now();


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        auto now = std::chrono::steady_clock::now();
        auto time_elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - last_line);
    
        // sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        // std::cout << "Mouse: " << mousePos.x << ", " << mousePos.y << "\n";

        window.clear();
        greenhouse.draw(window);
        if(time_elapsed.count() >= 3){
            lines.emplace_back(intake,window);
            last_line = now;
        }   
             
        for(auto& line: lines){
            line.Move(window);
        }

        lines.erase(std::remove_if(lines.begin(),lines.end(), [](auto& line) 
            {return abs(line.velocity.x) < 0.01f && abs(line.velocity.y) < 0.01f;})
            ,lines.end());

        window.display();
    }

    return 0;
}
