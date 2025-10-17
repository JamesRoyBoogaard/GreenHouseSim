#include <iostream>
#include <SFML/Graphics.hpp>

void Move_Directional_Line();
void Create_Directional_Line(sf::Vector2f direction, sf::Vector2f initial_position); //Spawn a directional line that then travels in the target
void Create_Offshoot_lines();
void Handle_line_Collision();
struct Line
{
    float velocity;
    sf::Vector2f position;
    float rate_of_slowing;

};
float Diminish_Velocity(Line line);

void Create_Outlet_Lines(float reach, float strength, sf::Vector2f position);

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

struct Directional_line: public Line
{
    
};

struct Offshoot_line: public Line
{ 
    float tightness_of_curve;
};

