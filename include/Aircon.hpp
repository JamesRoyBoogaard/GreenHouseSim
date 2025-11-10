#pragma once
#include <iostream>
#include "Airflow.hpp"
#include <SFML/Graphics.hpp>
#include "Greenhouse.hpp"

class Aircon{

    public:
    Aircon(sf::Vector2f position, sf::Vector2f p_direction, float p_speed);
    void draw();
    void airflow(sf::RenderWindow& p_window);

    private:
    sf::Vector2f direction;
    float speed;
    sf::RectangleShape aircon_box;
    sf::Vector2f intake;
    sf::Vector2f outake;
    sf::Vector2f offset_intake;
    std::vector<Airflow::Directional_line> lines;
    std::vector<Airflow::Offshoot_line> offshoot_lines;
    

};

