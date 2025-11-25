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
            sf::Vector2f position;
            float radius;

            Offshoot_line(sf::Vector2f p_position, sf::Vector2f p_velocity, float y_offset){
                float tightness_of_curve = 4.f;
                dot.setRadius(2.f);
                position = p_position;
                dot.setPosition(position);
                dl_velocity = p_velocity;
                dot.setFillColor(sf::Color::Green);
                velocity = {p_velocity.x , p_velocity.y + y_offset};
                centre = {velocity.x+100,velocity.y+100};
                offset = centre;
                trail.push_back(position);
                initial_time = std::chrono::steady_clock::now();
                radius = Find_Radius(p_position, centre);

            }

            float min(float f1, float f2){
                if(f1>f2){
                    return f2;
                }else{
                    return f1;
                }
            }

            float Find_Radius(const sf::Vector2f& A, const sf::Vector2f& B)
            {
                float dx = B.x - A.x;
                float dy = B.y - A.y;
                return std::sqrt(dx*dx + dy*dy);
            }

            void Move_Spiral(sf::RenderWindow& window){
                auto current_time = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);
                float t = elapsed.count(); 
                if(elapsed.count()>=10){
              
                    float x = centre.x + radius * cos(t*0.01f);
                    float y = centre.y + radius * sin(t*0.01f);

                    dot.setPosition(x,y);
                    velocity*=rate_of_slowing;
                    sf::Vector2f position = dot.getPosition();
                    trail.push_back(position);
                }
                
                std::vector<sf::Vertex> vert;
                for (auto& p: trail){
                    if(trail.size()<=10){
                        vert.push_back(sf::Vertex(p,sf::Color::Green));
                    }else{
                        trail.erase(trail.begin());
                }
            }
            window.draw(vert.data(), vert.size(), sf::PrimitiveType::LineStrip);
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
                    velocity.x *= rate_of_slowing;  // decay after move
                    velocity.y *= rate_of_slowing;
                    sf::Vector2f position = dot.getPosition();
                    trail.emplace_back(position, sf::Color::Black);
                    initial_time = current_time;
                }
                if(trail.size()>=20){
                    trail.erase(trail.begin());
                }
                if(ol_elapsted.count()>=500){
                    offshoot_lines.emplace_back(dot.getPosition(),velocity,30);
                    offshoot_lines.emplace_back(dot.getPosition(), velocity,-30);
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