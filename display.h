#ifndef DSA_PROJECT_2_DISPLAY_H
#define DSA_PROJECT_2_DISPLAY_H

#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <optional>
#include <cstdint>
#include "star.h"

class Display {
public:
    Display(const std::vector<Star>& dataStars);
    void start();
    void setPath(const std::vector<int>& indices);

private:

    struct VisualStar {
        sf::ConvexShape shape;
        sf::CircleShape shadow;
        sf::Vector2f position;
        float twinklePhase;
        float twinkleSpeed;
    };

    sf::RenderWindow window;
    sf::Clock clock;
    std::vector<VisualStar> stars;
    sf::VertexArray path;

    // --- Sidebar UI ---
    sf::Font font;
    sf::RectangleShape sidebar;
    sf::Text title;
    sf::RectangleShape algo1Btn, algo2Btn, rand1Btn, rand2Btn, generateBtn;
    sf::Text algo1Label, algo2Label, rand1Text, rand2Text, generateLabel;
    sf::RectangleShape infoBox;
    sf::Text infoText;
    sf::Text rand1Value;
    sf::Text rand2Value;


    std::string selectedAlgorithm;
    bool generateActive = false;

    void setupStars(const std::vector<Star>& dataStars);
    void setupSidebar();
    void drawSidebar();
    void drawStars();

    sf::ConvexShape makeStar(float radius, int points = 5);

    void connectTwoRandomStars();
    std::vector<Star> dataStars;


};

#endif // DSA_PROJECT_2_DISPLAY_H
