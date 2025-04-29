#pragma once
#include <SFML/Graphics.hpp>
#include "../../include/Process.h"

class ProcessUI {
public:
    Process* process;
    sf::RectangleShape background;
    sf::Text priorityText, arrivalText, burstText, timeText;
    std::vector<sf::RectangleShape> simBlocks;
    sf::Font& font;
    float top;

    ProcessUI(Process* process, float x, float y, float width, float height, sf::Font& font);

    void draw(sf::RenderWindow& window);

private:
    void initText(sf::Text& text, const std::string& str, float x, float y);
};
