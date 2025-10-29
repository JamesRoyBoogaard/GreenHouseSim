#pragma once
#include <iostream>
#include "Airflow.hpp"
#include <SFML/Graphics.hpp>

class Aircon{

    Aircon(sf::Vector2f& position,sf::Vector2f& direction, sf::RenderWindow& window, sf::Vector2f& intake_speed);
    public:
    sf::RectangleShape aircon_box;
    sf::Vector2f intake;
    sf::Vector2f outake;
    sf::Vector2f offset_intake;

    private:
    

};

