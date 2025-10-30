#include "Aircon.hpp"


Aircon::Aircon(sf::Vector2f position,
               sf::Vector2f p_direction,
               float p_speed)
    : aircon_box({50.f, 50.f})           
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

void Aircon::airflow(sf::RenderWindow& p_window, auto p_last_dl, auto last_ol){
    // work out direction and then add speed to the 2dvector direction to form the velocity 
    
    sf::Vector2f velocity = {direction.x*speed, direction.y*speed};

    auto now = std::chrono::steady_clock::now();
    auto time_elapsed_dl = std::chrono::duration_cast<std::chrono::seconds>(now - last_dl);
    auto time_elapsed_ol = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_ol);    

    if(time_elapsed_dl.count() >= speed)
    {
        lines.emplace_back(intake,p_window,velocity); 
        last_dl = now;
    }

    for(auto& line: lines)
    {
        line.Move(p_window);
        if(time_elapsed_ol.count() >= 250){
            offshoot_lines.emplace_back(line,p_window,30);
            offshoot_lines.emplace_back(line, p_window,-30);
            last_ol = now;
        }
    }
    for(auto& offshoot_line: offshoot_lines)
    {
        offshoot_line.Move_Spiral(p_window);
    }

    lines.erase(std::remove_if(lines.begin(),lines.end(), [](auto& line) 
    {return abs(line.velocity.x) < 0.1f && abs(line.velocity.y) < 0.1f;})
    ,lines.end());

    offshoot_lines.erase(std::remove_if(offshoot_lines.begin(),offshoot_lines.end(),[](auto& offshoot_line)
    {return abs(offshoot_line.velocity.x) < 0.1f && abs(offshoot_line.velocity.y) < 0.1f;}),
    offshoot_lines.end());
    //just copy accross how the dots are spawining with the airflow class in main and it should work if you then let this class handle the logic

}