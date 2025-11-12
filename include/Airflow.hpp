#pragma once
#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <chrono>


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
        };

        struct Offshoot_line: public Line
        { 
            std::chrono::steady_clock::time_point initial_time;  

            float tightness_of_curve;
            std::vector<sf::Vector2f> trail;

            Offshoot_line(sf::Vector2f p_position, sf::Vector2f p_velocity, float y_offset){
                float tightness_of_curve = 4.f;
                dot.setRadius(2.f);
                auto position = p_position;
                dot.setPosition(position);
                dot.setFillColor(sf::Color::Green);
                velocity = {p_velocity.x , p_velocity.y + y_offset};
                trail.push_back(position);
                initial_time = std::chrono::steady_clock::now();
            }

            void Move_Spiral(sf::RenderWindow& window){
                auto current_time = std::chrono::steady_clock::now();
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - initial_time);
                if(elapsed.count()>=10){
                    dot.move(velocity);
                    velocity*=rate_of_slowing;
                    sf::Vector2f position = dot.getPosition();
                    trail.push_back(position);
                    initial_time = current_time;
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
                window.draw(trail.data(),trail.size(), sf::PrimitiveType::LineStrip);
                window.draw(dot);
            }
        };



    private:

    


};