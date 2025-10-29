#include "Aircon.hpp"


Aircon::Aircon(sf::Vector2f& position,
               sf::Vector2f p_direction,
               sf::RenderWindow& p_window,
               float p_speed)
    : window(p_window),
    aircon_box({50.f, 50.f})           
{
    aircon_box.setPosition(position);
    aircon_box.setFillColor(sf::Color::Blue);
    intake = position;
    direction = p_direction;
    speed = p_speed;
    outake = position;
    offset_intake = intake;//come up with better way to use the speed to determine how far the offset is
}

void Aircon::draw(){

    
};

void Aircon::airflow(){
    // work out direction and then add speed to the 2dvector direction to form the velocity 
    sf::Vector2f velocity = {direction.x*speed, direction.y*speed};
    //just copy accross how the dots are spawining with the airflow class in main and it should work if you then let this class handle the logic

}