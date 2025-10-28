#include "display.h"
#include <iostream>

//Create a 5-pointed star
sf::ConvexShape makeStar(float radius, int points = 5) {
    sf::ConvexShape star(points * 2);
    float innerRadius = radius * 0.5f;
    float angleStep = static_cast<float>(M_PI) / points;

    for (int i = 0; i < points * 2; ++i) {
        float angle = i * angleStep - M_PI / 2.f;
        float r = (i % 2 == 0) ? radius : innerRadius;
        star.setPoint(i, {r * std::cos(angle), r * std::sin(angle)});
    }
    return star;
}

// ---------------- CONSTRUCTOR ----------------
Display::Display()
: window(sf::VideoMode({1200u, 600u}),
         "Constellation Connection",
         sf::State::Windowed),
  font(),
  title(font, "", 20),
  algo1Label(font, "", 12),
  algo2Label(font, "", 12),
  rand1Text(font, "", 18),
  rand2Text(font, "", 18),
  generateLabel(font, "", 18)
{
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    if (!font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    setupStars();
    setupSidebar();
}

// ---------------- STARS ----------------
void Display::setupStars() {
    for (int i = 0; i < 300; ++i) {
        Star s;

        s.position = {
            static_cast<float>(std::rand() % 950 + 225),
            static_cast<float>(std::rand() % 550 + 25)
        };

        float radius = static_cast<float>((std::rand() % 6) + 5);
        s.shape = makeStar(radius);
        s.shape.setFillColor(sf::Color::White);
        s.shape.setPosition(s.position);
        s.shape.setRotation(sf::degrees(static_cast<float>(std::rand() % 360)));

        s.shadow.setRadius(radius * 1.8f);
        s.shadow.setOrigin({radius * 1.8f, radius * 1.8f});
        s.shadow.setFillColor(sf::Color(255, 255, 220, 20));
        s.shadow.setPosition(s.position);

        s.twinklePhase = static_cast<float>(std::rand() % 360);
        s.twinkleSpeed = 0.5f + static_cast<float>(std::rand() % 100) / 200.f;

        stars.push_back(s);
    }

    int startIndex = std::rand() % stars.size();
    int endIndex   = std::rand() % stars.size();
    path = sf::VertexArray(sf::PrimitiveType::LineStrip);
    path.append(sf::Vertex(stars[startIndex].position, sf::Color::Red));
    path.append(sf::Vertex(stars[endIndex].position,   sf::Color::Red));
}

// ---------------- SIDEBAR ---------------- (IN PROGRESS)
void Display::setupSidebar() {
    sidebar.setSize({200.f, 600.f});
    sidebar.setFillColor(sf::Color(180, 180, 200));

    title.setString("Pick which\nalgorithm to use");
    title.setFillColor(sf::Color::Black);
    title.setPosition({20.f, 20.f});

    algo1Btn.setSize({80.f, 30.f});
    algo1Btn.setFillColor(sf::Color::White);
    algo1Btn.setPosition({25.f, 100.f});

    algo2Btn.setSize({80.f, 30.f});
    algo2Btn.setFillColor(sf::Color::White);
    algo2Btn.setPosition({115.f, 100.f});

    algo1Label.setString("Dijkstra");
    algo1Label.setFillColor(sf::Color::Black);
    algo1Label.setPosition({28.f, 106.f});

    algo2Label.setString("A* Search");
    algo2Label.setFillColor(sf::Color::Black);
    algo2Label.setPosition({118.f, 106.f});

    rand1Text.setString("Random\nstar 1");
    rand1Text.setFillColor(sf::Color::Black);
    rand1Text.setPosition({30.f, 170.f});

    rand2Text.setString("Random\nstar 2");
    rand2Text.setFillColor(sf::Color::Black);
    rand2Text.setPosition({30.f, 240.f});

    rand1Btn.setSize({70.f, 30.f});
    rand1Btn.setFillColor(sf::Color::White);
    rand1Btn.setOutlineColor(sf::Color::Black);
    rand1Btn.setOutlineThickness(1.f);
    rand1Btn.setPosition({100.f, 180.f});

    rand2Btn.setSize({70.f, 30.f});
    rand2Btn.setFillColor(sf::Color::White);
    rand2Btn.setOutlineColor(sf::Color::Black);
    rand2Btn.setOutlineThickness(1.f);
    rand2Btn.setPosition({100.f, 250.f});

    generateBtn.setSize({150.f, 40.f});
    generateBtn.setFillColor(sf::Color(240, 240, 240));
    generateBtn.setOutlineColor(sf::Color::Black);
    generateBtn.setOutlineThickness(1.f);
    generateBtn.setPosition({25.f, 330.f});

    generateLabel.setString("Generate");
    generateLabel.setFillColor(sf::Color::Black);
    generateLabel.setPosition({60.f, 338.f});
}

void Display::drawSidebar() {
    window.draw(sidebar);
    window.draw(title);
    window.draw(algo1Btn);
    window.draw(algo2Btn);
    window.draw(algo1Label);
    window.draw(algo2Label);
    window.draw(rand1Text);
    window.draw(rand2Text);
    window.draw(rand1Btn);
    window.draw(rand2Btn);
    window.draw(generateBtn);
    window.draw(generateLabel);
}

void Display::drawStars() {
    float time = clock.getElapsedTime().asSeconds();

    for (auto& s : stars) {
        float brightness = 170 + 85 * std::sin(time * s.twinkleSpeed * 4.0f + s.twinklePhase);
        uint8_t alpha = static_cast<uint8_t>(brightness);
        s.shape.setFillColor(sf::Color(255, 255, 255, alpha));
        s.shadow.setFillColor(sf::Color(255, 255, 220, alpha / 12));

        float scale = 1.0f + 0.05f * std::sin(time * s.twinkleSpeed + s.twinklePhase);
        s.shape.setScale({scale, scale});
        s.shadow.setScale({scale, scale});

        window.draw(s.shadow);
        window.draw(s.shape);
    }

    window.draw(path);
}

// ---------------- MAIN LOOP ----------------
void Display::start() {
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(sf::Color(5, 10, 30));
        drawSidebar();
        drawStars();
        window.display();
    }
}

// To draw the algorithm’s path
void Display::setPath(const std::vector<int>& indices) {
    path.clear();
    for (int idx : indices) {
        if (idx >= 0 && idx < static_cast<int>(stars.size())) {
            path.append(sf::Vertex(stars[idx].position, sf::Color::Red));
        }
    }
}


