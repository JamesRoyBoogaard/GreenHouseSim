#include <iostream>
#include <SFML/Graphics.hpp>
#include "Airflow.hpp"

void Move_Directional_Line();
void Create_Directional_Line(sf::Vector2f direction, sf::Vector2f initial_position); //Spawn a directional line that then travels in the target
void Create_Offshoot_lines();
void Handle_line_Collision();
float Diminish_Velocity(const Airflow::Line& line);
void Create_Outlet_Lines(float reach, float strength, sf::Vector2f position);



Airflow::Airflow() {

}

