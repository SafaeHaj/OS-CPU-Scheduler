#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ProcessUIManager.h"
#include "ProcessUI.h"

class ProcessUIManager
{
    std::vector<ProcessUI> processRows;
    sf::Font &font;
    sf::Text headers[5];
    sf::Text avgTurnaroundText;
    sf::RectangleShape avgBox;

public:
    ProcessUIManager(sf::Font &font);
    void setProcesses(const std::vector<Process *> &processes);
    void draw(sf::RenderWindow &window);
    void updateAvgTurnaround(float avg);
};
