#include "Aircon.hpp"



Aircon::Aircon(sf::Vector2f position,
               sf::Vector2f p_direction,
               float p_speed)
    : aircon_box({50.f, 50.f})           
{
    aircon_box.setPosition(position);
    aircon_box.setFillColor({128, 128, 128});
    intake = position;
    direction = p_direction;
    speed = p_speed;
    outake = position;
    offset_intake = intake;//come up with better way to use the speed to determine how far the offset is
    last_directional_line = std::chrono::steady_clock::now();
}

void Aircon::draw(sf::RenderWindow& p_window){
    p_window.draw(aircon_box);
};

void Aircon::airflow(sf::RenderWindow& p_window){
    // work out direction and then add speed to the 2dvector direction to form the velocity 
    
    bool line_produced = false;
    sf::Vector2f velocity = {direction.x*speed, direction.y*speed};
    

    auto now = std::chrono::steady_clock::now();
    auto time_elapsed_dl = std::chrono::duration_cast<std::chrono::seconds>(now - last_directional_line);

    if(time_elapsed_dl.count() >= speed)
    {
        directional_lines.emplace_back(intake,p_window,velocity); 
        last_directional_line = now;
    }

    for (Airflow::Directional_line dl: directional_lines){
        dl.Move(p_window);
        for(Airflow::Offshoot_line ol: dl.offshoot_lines){
            ol.Move_Spiral(p_window);
        }
    }

    directional_lines.erase(std::remove_if(directional_lines.begin(),directional_lines.end(), [](auto& line) 
    {return abs(line.velocity.x) < 0.1f && abs(line.velocity.y) < 0.1f;})
    ,directional_lines.end());

    offshoot_lines.erase(std::remove_if(offshoot_lines.begin(),offshoot_lines.end(),[](auto& offshoot_line)
    {return abs(offshoot_line.velocity.x) < 0.1f && abs(offshoot_line.velocity.y) < 0.1f;}),
    offshoot_lines.end());
}