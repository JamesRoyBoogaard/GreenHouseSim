#include "Greenhouse.hpp"
#include <iostream>


Greenhouse::Greenhouse() 
: aircon1(1,{900.f, 164}, {-1.f, 0.f}, 1.f),
  aircon2(2,{900.f, 100.f}, {-1.f, 0.f}, 2.f),
  last_dl(std::chrono::steady_clock::now()),
  last_ol(std::chrono::steady_clock::now().operator+=(std::chrono::steady_clock::duration(1000)))
{
    background.setSize(sf::Vector2f(1400, 500));
    greenhouse.setSize(sf::Vector2f(800, 300));


    if (!grassTexture.loadFromFile("../Textures/grass.png", sf::IntRect(0, 0, 1400, 850))) {
        std::cerr << "Failed to load grass texture\n";
    }
    if (!plantTexture.loadFromFile("../Textures/plant_no_bg.png")) {
        std::cerr << "Failed to load plant texture\n";
    }

    background.setTexture(&grassTexture);
    background.setPosition(0.f, 0.f);

    greenhouse.setFillColor(sf::Color(192, 192, 192));
    greenhouse.setOutlineThickness(10.f);
    greenhouse.setOutlineColor(sf::Color(200, 200, 200));
    greenhouse.setPosition(300.f, 110.f);

    float top_row[2] = {385.f, 188.f};
    float bottom_row[2] = {435.f, 288.f};

    for (int i = 0; i < 12; i++) {
        sf::Sprite plant;
        plant.setTexture(plantTexture);
        plant.setScale(0.2f, 0.2f);

        if (i % 2)
            plant.setPosition(top_row[0] + i * 50, top_row[1]);
        else
            plant.setPosition(bottom_row[0] + i * 50, bottom_row[1]);

        plants.push_back(plant);
    }
}

void Greenhouse::update(sf::RenderWindow& window) {
    aircon1.airflow(window);
    aircon2.airflow(window);
}

void Greenhouse::draw(sf::RenderWindow& window) {
    
    window.draw(background);
    window.draw(greenhouse);
    aircon1.draw(window);
    aircon2.draw(window);
    for (auto& plant : plants)
        window.draw(plant);
}
