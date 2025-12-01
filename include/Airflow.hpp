#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <chrono>
#include <cmath>
#include <numbers>

class Airflow {
    public:
        Airflow();
        void draw(sf::RenderWindow& window);
        sf::CircleShape Create_Directional_Line(sf::Vector2f initial_position, sf::RenderWindow& window);
        void Move_Directional_Line(sf::Vector2f dir, sf::CircleShape& directional_dot, sf::RenderWindow& window);
        float Decay_Method(float initial_velocity, sf::CircleShape& directional_dot, sf::RenderWindow& window);

        struct Line;
        struct Directional_line;
        struct Offshoot_line;

        struct Line
        {
            sf::Vector2f velocity ;
            sf::CircleShape dot;
            sf::Vector2f position;
            float rate_of_slowing = 0.99f;
            double PI = 3.14159265358979323846;
        };
        

        struct Offshoot_line: public Line
        { 
            std::chrono::steady_clock::time_point initial_time;  

            float tightness_of_curve;
            sf::Vector2f dl_velocity;
            sf::Vector2f centre;
            sf::Vector2f offset;
            std::vector<sf::Vector2f> trail;
            int direction;
            float radius;
            float iterant;

            Offshoot_line(sf::Vector2f p_position, sf::Vector2f p_velocity, int p_is_right_or_left){
                tightness_of_curve = 4.f;
                dot.setRadius(2.f);
                position = p_position;

                dot.setPosition(position);
                //std::cout << "OG p_position OL constructor: " << position.x << ", " << position.y << "\n";

                dl_velocity = p_velocity;
                dot.setFillColor(sf::Color::Green);
                velocity = {dl_velocity.x , dl_velocity.y};
                direction = p_is_right_or_left;
                centre = normalise(dl_velocity, position);
                // std::cout << "centre: " << centre.x << ", " << centre.y << "\n";
                trail.push_back(position);
                initial_time = std::chrono::steady_clock::now();
                iterant = 0.f;
            }

            sf::Vector2f normalise(sf::Vector2f p_velocity, sf::Vector2f pe_position){
                sf::Vector2f r_centre;
                std::cout << "p_velocity: "<< p_velocity.x << ": "<< p_velocity.y<<"\n";
                int sign_x = (p_velocity.x>0) ? 1 : -1;
                int sign_y = (p_velocity.y>0) ? 1 : -1;

                if(p_velocity.x!=0){
                    r_centre.x = pe_position.x + sign_x*100;
                    //std::cout<<"r_centre: "<< r_centre.x<<": "<<r_centre.y<<"\n";
                }else{
                    r_centre.x = pe_position.x + 100;
                    //std::cout<<"r_centre: "<< r_centre.x<<": "<<r_centre.y<<"\n";

                }
                if(p_velocity.y!=0){
                    r_centre.y = pe_position.y + sign_y*100;
                    //std::cout<<"r_centre: "<< r_centre.x<<": "<<r_centre.y<<"\n";

                }else{
                    r_centre.y = pe_position.y + 100;
                    //std::cout<<"r_centre: "<< r_centre.x<<": "<<r_centre.y<<"\n";

                }
                return r_centre;
            }

    
            // we can derive the direction from the velocity and the initial position p_postion - p_velocity we will get a +-x and +-y.
            // then we do a check on this and will make the offsets appropriate 

        void Move_Spiral(sf::RenderWindow& window)
        {
            auto current_time = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);

            if (elapsed.count() >= 10 && iterant <= 1.f) {
                initial_time = current_time;

                float x = position.x + (centre.x - position.x) * iterant;
                float y = position.y + (centre.y - position.y) * iterant;

                dot.setPosition(x, y);
                trail.push_back({x, y});
                iterant += 0.01f;   
            }

            if (trail.size() > 50)
                trail.erase(trail.begin());

            std::vector<sf::Vertex> vert;
            for (auto& p : trail)
                vert.emplace_back(p, sf::Color::Green);
            window.draw(vert.data(), vert.size(), sf::LineStrip);
            window.draw(dot);
        }
    };

        struct Directional_line: public Line
        {
            std::vector<sf::Vertex> trail;   
            std::chrono::steady_clock::time_point initial_time;  
            std::chrono::steady_clock::time_point last_offshoot;
            std::vector<Airflow::Offshoot_line> offshoot_lines;
            

            Directional_line(sf::Vector2f initial_position,sf::RenderWindow& window, sf::Vector2f p_velocity)
            {
                dot.setRadius(2.f);
                dot.setFillColor(sf::Color::Black);
                dot.setPosition(initial_position);
                position = initial_position;
                velocity = p_velocity;
                trail.emplace_back(initial_position, sf::Color::Black);
                initial_time = std::chrono::steady_clock::now();
                last_offshoot = initial_time;
            }

            void Move(sf::RenderWindow& window)
            {
                auto current_time = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);
                auto ol_elapsted = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_offshoot);

                if(elapsed.count()>=10){
                    dot.move(velocity);
                    velocity.x *= rate_of_slowing;  
                    velocity.y *= rate_of_slowing;
                    sf::Vector2f position = dot.getPosition();
                    trail.emplace_back(position, sf::Color::Black);
                    initial_time = current_time;
                }
                if(trail.size()>=20){
                    trail.erase(trail.begin());
                }
                if(ol_elapsted.count()>=500){
                    offshoot_lines.emplace_back(dot.getPosition(),velocity, 1);
                    // std::cout << "Position of the pos OL: "<< dot.getPosition().x << ": "<< dot.getPosition().y<<"\n";
                    offshoot_lines.emplace_back(dot.getPosition(), velocity,-1);
                    // std::cout << "Position of the neg OL: "<< dot.getPosition().x << ": "<< dot.getPosition().y<<"\n";
                    last_offshoot = std::chrono::steady_clock::now();
                }
                offshoot_lines.erase(std::remove_if(offshoot_lines.begin(),offshoot_lines.end(),[](auto& offshoot_line)
                {return abs(offshoot_line.velocity.x) < 0.1f && abs(offshoot_line.velocity.y) < 0.1f;}),
                offshoot_lines.end());

                window.draw(trail.data(),trail.size(), sf::PrimitiveType::LineStrip);
                window.draw(dot);
            }
        };



    private:

    


};