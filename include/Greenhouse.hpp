#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Airflow.hpp"
#include "Aircon.hpp"
#include <chrono>

class Greenhouse {
public:
    Greenhouse();
    void update(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);


private:
    sf::RectangleShape background;
    sf::RectangleShape greenhouse;
    sf::RectangleShape upper_air_intake;
    sf::RectangleShape upper_air_outlet;
    sf::RectangleShape lower_air_intake;
    sf::RectangleShape lower_air_outlet;
    std::chrono::steady_clock::time_point last_dl;
    std::chrono::steady_clock::time_point last_ol;

    Aircon aircon1;
    Aircon aircon2;

    std::vector<sf::Sprite> plants;
    sf::Texture grassTexture;
    sf::Texture plantTexture;
};



