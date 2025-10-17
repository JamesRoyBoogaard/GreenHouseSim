// Create points of intake and outtake for the air to travel from (standard ventilation)
// The airflow needs a direction, current  position, size, speed

#include <iostream>
#include <SFML/Graphics.hpp>


struct Origin{
    int fan_rate;
    sf::Vector2f postion;
};

struct Oulet{
    float reach;
    float strength; 
    sf::Vector2f position;
};

struct Directinal_line{

};

struct Offshoot{

};