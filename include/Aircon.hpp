#pragma once
#include <iostream>
#include "Airflow.hpp"
#include <SFML/Graphics.hpp>
#include <string>
// #include "Greenhouse.hpp"

class Aircon{

    public:
    Aircon(int id, sf::Vector2f position, sf::Vector2f p_direction, float p_speed);
    void draw(sf::RenderWindow& p_window);
    void airflow(sf::RenderWindow& p_window);

    private:
    sf::Vector2f direction;
    float speed;
    sf::RectangleShape aircon_box;
    sf::Vector2f intake;
    sf::Vector2f outake;
    sf::Vector2f offset_intake;
    std::vector<Airflow::Directional_line> directional_lines;
    std::vector<Airflow::Offshoot_line> offshoot_lines;
    std::chrono::steady_clock::time_point last_directional_line;

    int id;
    

};

