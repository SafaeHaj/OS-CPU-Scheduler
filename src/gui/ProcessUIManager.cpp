#include <SFML/Graphics.hpp>
#include <vector>
#include "gui/ProcessUIManager.h"
#include "gui/ProcessUI.h"
#include "gui/Layout.h"

ProcessUIManager::ProcessUIManager(float x, float y, sf::Font &font)
    : x(x), y(y), font(font) {
    initHeaders();
    initAvgBox();
}

void ProcessUIManager::initText(sf::Text& text, const std::string& str, float x, float y) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(CHAR_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
}

void ProcessUIManager::initHeader(sf::Text& text, const std::string& str, float x, float y, float customWidth) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(CHAR_SIZE);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x, y);

    sf::RectangleShape background;
    // Use customWidth if provided, otherwise calculate based on text
    float width = (customWidth > 0) ? customWidth : (text.getLocalBounds().width + PADDING);
    background.setSize(sf::Vector2f(width, HEADER_HEIGHT));
    background.setFillColor(sf::Color::White);
    background.setPosition(x - PADDING / 2, y - PADDING / 2);
    headerBackgrounds.push_back(background);
}

void ProcessUIManager::initHeaders() {
    std::string titles[5] = {"Priority", "Burst Time", "Arrival", "Simulation", "Time"};
    float currentX = x;

    for (int i = 0; i < 5; ++i) {
        if (titles[i] == "Simulation") {
            sf::Text tempText;
            tempText.setFont(font);
            tempText.setString(titles[i]);
            tempText.setCharacterSize(CHAR_SIZE);
            float textWidth = tempText.getLocalBounds().width + PADDING;
            float totalWidth = std::max(textWidth, SIM_WIDTH);
            initHeader(headers[i], titles[i], currentX, y, totalWidth);
        } else if (titles[i] == "Time") {
            initHeader(headers[i], titles[i], currentX, y, TIME_WIDTH);
        } else {
            initHeader(headers[i], titles[i], currentX, y, FIELD_WIDTH);
        }

        // Update currentX for next header (current width + gap)
        float headerWidth = headerBackgrounds.back().getSize().x;
        currentX += headerWidth + COLUMN_GAP;
    }
}

void ProcessUIManager::initAvgBox() {
    avgBox.setSize(sf::Vector2f(FIELD_WIDTH, FIELD_HEIGHT));
    avgBox.setFillColor(sf::Color::Black);
    avgBox.setOutlineColor(sf::Color::White);
    avgBox.setOutlineThickness(1.f);
    avgBox.setPosition(600, 500);

    avgTurnaroundText.setFont(font);
    avgTurnaroundText.setCharacterSize(CHAR_SIZE);
    avgTurnaroundText.setFillColor(sf::Color::White);
    avgTurnaroundText.setString("Avg. Turnaround Time:");
    avgTurnaroundText.setPosition(460, 505);

    avgValueText.setFont(font);
    avgValueText.setCharacterSize(CHAR_SIZE);
    avgValueText.setFillColor(sf::Color::White);
    avgValueText.setPosition(610, 505);
    avgValueText.setString("0.0 ms");
}

void ProcessUIManager::setProcesses(const std::vector<Process *> &processes) {
    processRows.clear();
    float yOffset = y + HEADER_HEIGHT;
    for (auto &proc : processes) {
        ProcessUI row = ProcessUI(proc, x - PADDING, yOffset, FIELD_WIDTH * 3.6f, ROW_HEIGHT, font);
        processRows.emplace_back(row);
        yOffset += ROW_HEIGHT;
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
