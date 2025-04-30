#include <SFML/Graphics.hpp>
#include <vector>
#include "gui/ProcessUIManager.h"
#include "gui/ProcessUI.h"

ProcessUIManager::ProcessUIManager(float x, float y, sf::Font &font)
    : x(x), y(y), font(font) {
    initHeaders();
    initAvgBox();
}

void ProcessUIManager::initText(sf::Text& text, const std::string& str, float x, float y) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
}

void ProcessUIManager::initHeader(sf::Text& text, const std::string& str, float x, float y, float customWidth) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x, y);

    float padding = 30.0f;
    sf::RectangleShape background;
    // Use customWidth if provided, otherwise calculate based on text
    float width = (customWidth > 0) ? customWidth : (text.getLocalBounds().width + padding);
    background.setSize(sf::Vector2f(width, 40));
    background.setFillColor(sf::Color::White);
    background.setPosition(x - padding / 2, y - padding / 2);
    headerBackgrounds.push_back(background);
}

void ProcessUIManager::initHeaders(){
    std::string titles[5] = {"Priority", "Burst Time", "Arrival", "Simulation", "Time"};
    float currentX = x;
    float gap = 5.0f; 
    float padding = 50.0f;
    float minSimulationWidth = 280.0f; 

    for (int i = 0; i < 5; ++i) {
        if (titles[i] == "Simulation") {
            sf::Text tempText;
            tempText.setFont(font);
            tempText.setString(titles[i]);
            tempText.setCharacterSize(18);
            float textWidth = tempText.getLocalBounds().width + padding;
            float totalWidth = std::max(textWidth, minSimulationWidth);
            initHeader(headers[i], titles[i], currentX, y, totalWidth);
        } else {
            initHeader(headers[i], titles[i], currentX, y);
        }

        // Update currentX for next header (current width + gap)
        float headerWidth = headerBackgrounds.back().getSize().x;
        currentX += headerWidth + gap;
    }
}

void ProcessUIManager::initAvgBox(){
    avgBox.setSize(sf::Vector2f(100, 30));
    avgBox.setFillColor(sf::Color::Black);
    avgBox.setOutlineColor(sf::Color::White);
    avgBox.setOutlineThickness(1.f);
    avgBox.setPosition(600, 500);

    avgTurnaroundText.setFont(font);
    avgTurnaroundText.setCharacterSize(16);
    avgTurnaroundText.setFillColor(sf::Color::White);
    avgTurnaroundText.setString("Avg. Turnaround Time:");
    avgTurnaroundText.setPosition(460, 505);

    avgValueText.setFont(font);
    avgValueText.setCharacterSize(16);
    avgValueText.setFillColor(sf::Color::White);
    avgValueText.setPosition(610, 505);
    avgValueText.setString("0.0 ms");
}

void ProcessUIManager::setProcesses(const std::vector<Process *> &processes) {
    processRows.clear();
    float yOffset = y + 40;
    for (auto &proc : processes) {
        ProcessUI row = ProcessUI(proc, x-15, yOffset, 720, 60, font);
        processRows.emplace_back(row);
        yOffset += 60;
    }
}

void ProcessUIManager::draw(sf::RenderWindow &window) {
    for (auto& bg : headerBackgrounds)
        window.draw(bg);

    for (auto &header : headers)
        window.draw(header);

    for (auto &row : processRows)
        row.draw(window);

    window.draw(avgTurnaroundText);
    window.draw(avgBox);
    window.draw(avgValueText);
}

void ProcessUIManager::updateAvgTurnaround(float avg) {
    avgValueText.setString(std::to_string(avg) + " ms");
}