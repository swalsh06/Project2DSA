#ifndef DSA_PROJECT_2_DISPLAY_H
#define DSA_PROJECT_2_DISPLAY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "star.h"
#include "StarGroup.h"

class Display {
public:
    Display(const std::vector<std::string>& lines);
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


    int startIndex;
    int endIndex;
    int dijkstraNodes = -1;
    int aStarNodes = -1;


    StarGroup* sg;
    std::vector<Star> dataStars;
    std::vector<std::string> rawLines;


    sf::RenderWindow window;
    sf::Clock clock;
    std::vector<VisualStar> stars;
    sf::VertexArray path;
    sf::VertexArray backgroundLines;

    // sidebar
    sf::Font font;
    sf::RectangleShape sidebar;
    sf::Text title;

    sf::RectangleShape algo1Btn, algo2Btn, rand1Btn, rand2Btn, generateBtn;
    sf::Text algo1Label, algo2Label, rand1Text, rand2Text, generateLabel;

    sf::RectangleShape infoBox;
    sf::Text infoText;
    sf::Text rand1Value;
    sf::Text rand2Value;

    // input for number of stars
    sf::RectangleShape inputBox;
    sf::Text starCountLabel;
    sf::Text starCountInput;
    bool isTypingStarCount;
    int numStars;
    static constexpr int minStars = 20;
    static constexpr int maxStars = 500;

    std::string selectedAlgorithm;
    bool generateActive;

    // helpers
    sf::ConvexShape makeStar(float radius, int points = 5);
    void setupSidebar();
    void setupStars(int count = -1);
    void drawSidebar();
    void drawStars();
    void connectTwoRandomStars();
};

#endif
