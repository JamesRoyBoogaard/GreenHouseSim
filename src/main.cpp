
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

        // Okay so we have a chrono::now when each particle is made and then move the particle a certain amount of pixels each millisecond. 
        // The number of pixels each millisecond is then reduced by the slowing value appearing to slow the particle.
        window.clear();
        greenhouse.draw(window);
        if(time_elapsed_dl.count() >= 3){
            lines.emplace_back(intake,window,velocity); // each of these lines then need to have a spiral spawn out on each side every second.
            last_dl = now;
        }

        for(auto& line: lines){
            line.Move(window);
            if(time_elapsed_ol.count() >= 250){
                offshoot_lines.emplace_back(line,window,30);
                offshoot_lines.emplace_back(line, window,-30);
                last_ol = now;
            }
        }

        for(auto& offshoot_line: offshoot_lines){
            offshoot_line.Move_Spiral(window);
        }

        lines.erase(std::remove_if(lines.begin(),lines.end(), [](auto& line) 
            {return abs(line.velocity.x) < 0.1f && abs(line.velocity.y) < 0.1f;})
            ,lines.end());

        offshoot_lines.erase(std::remove_if(offshoot_lines.begin(),offshoot_lines.end(),[](auto& offshoot_line)
        {return abs(offshoot_line.velocity.x) < 0.1f && abs(offshoot_line.velocity.y) < 0.1f;}),
        offshoot_lines.end());

        window.display();
    }

    return 0;
}
