#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Process.h"
#include "ProcessUI.h"

class ProcessUIManager {
public:
    ProcessUIManager(float x, float y, sf::Font& font);
    void setProcesses(const std::vector<Process*>& processes);
    void draw(sf::RenderWindow& window);
    void updateAvgTurnaround(float avg);

    // —— Layout getters ——  
    /// Left-edge of header column idx (0=Priority,1=Burst,2=Arrival,3=Simulation,4=Time)
    float getHeaderX(int idx) const { return headerBackgrounds.at(idx).getPosition().x; }
    /// Width of header column idx
    float getHeaderWidth(int idx) const { return headerBackgrounds.at(idx).getSize().x; }
    /// Y-position at which rows begin (so you can align input fields under them)
    float getRowsY()      const { return y + 40.f; }

private:
    float x, y;
    sf::Font& font;

    sf::RectangleShape avgBox;
    sf::Text avgTurnaroundText, avgValueText;

    sf::Text headers[5];
    std::vector<sf::RectangleShape> headerBackgrounds;

    std::vector<ProcessUI> processRows;
    void initText(sf::Text& text, const std::string& str, float x, float y);
    void initHeaders();
    void initHeader(sf::Text& text, const std::string& str, float x, float y, float customW = 0);
    void initAvgBox();
};
