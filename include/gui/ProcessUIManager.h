#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Process.h"
#include "ProcessUI.h"

class ProcessUIManager
{
private:
    float x, y;
    sf::Font &font;
    std::vector<ProcessUI> processRows;
    sf::Text headers[5];
    sf::RectangleShape avgBox;
    sf::Text avgTurnaroundText;
    sf::Text avgValueText;
    std::vector<sf::RectangleShape> headerBackgrounds;

    void initText(sf::Text &text, const std::string &str, float x, float y);
    void initHeader(sf::Text &text, const std::string &str, float x, float y, float customWidth = 0);
    void initHeaders();
    void initAvgBox();

public:
    ProcessUIManager(float x, float y, sf::Font &font);
    void setProcesses(const std::vector<Process *> &processes);
    void draw(sf::RenderWindow &window);
    void updateAvgTurnaround(float avg);
};
