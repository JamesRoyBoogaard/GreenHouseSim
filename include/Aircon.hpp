#pragma once
#include <iostream>
#include "Airflow.hpp"
#include <SFML/Graphics.hpp>

class Aircon{

    public:
    Aircon(sf::Vector2f& position, sf::Vector2f p_direction, sf::RenderWindow& p_window, float p_speed);

    sf::RenderWindow& window;
    sf::Vector2f direction;
    float speed;
    sf::RectangleShape aircon_box;
    sf::Vector2f intake;
    sf::Vector2f outake;
    sf::Vector2f offset_intake;

    void draw();
    void airflow();

    private:
    

};

