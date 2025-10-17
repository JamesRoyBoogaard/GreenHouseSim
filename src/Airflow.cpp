// Create points of intake and outtake for the air to travel from (standard ventilation)
// The airflow needs a direction, current  position, size, speed

#include <iostream>
#include <SFML/Graphics.hpp>

void Move_Directional_line();
void Create_Offshoot_line();
void Handle_line_Collision();
float Deminish_Velocity(Line line);

struct Origin
{
    int fan_rate;
    sf::Vector2f postion;
};

struct Oulet
{
    float reach;
    float strength; 
    sf::Vector2f position;
};

struct Line
{
    float velocity;
    sf::Vector2f position;
    float rate_of_slowing;

};

struct Directional_line: public Line
{
    
};

struct Offshoot_line: public Line{ 
    float tightness_of_curve;
};

