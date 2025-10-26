#include <iostream>
#include <SFML/Graphics.hpp>
#include "Airflow.hpp"
#include <array>

void Move_Directional_Line(sf::Vector2f dir, sf::CircleShape& directional_dot);
void Create_Directional_Line(sf::Vector2f initial_position); //Create a dot with a trail that moves in a direction
void Create_Outlet_Lines(float reach, float strength, sf::Vector2f position);
// The intention for any kind of line is to create a particle that follows a tragectery and lifecycle and then slows and diminshes visually. 
// This applies to both the Directional and Offshoot lines, they are not lines but dots that have followed a tragectory and left a trail.


Airflow::Airflow() {
    
}

sf::CircleShape Airflow::Create_Directional_Line(sf::Vector2f initial_position, sf::RenderWindow& window){
    sf::CircleShape directional_dot;
    directional_dot.setRadius(3.f);
    directional_dot.setFillColor(sf::Color(173, 216, 230));
    directional_dot.setPosition(initial_position);
    window.draw(directional_dot);
    return directional_dot;
}

void Airflow::Move_Directional_Line(sf::Vector2f dir, sf::CircleShape& directional_dot, sf::RenderWindow& window){
    sf::Vector2f initial_position = directional_dot.getPosition();
    directional_dot.move(dir);
    sf::Vector2f new_postion = directional_dot.getPosition();
    std::array line = {
        sf::Vertex{initial_position},
        sf::Vertex{new_postion}
    };
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
}


