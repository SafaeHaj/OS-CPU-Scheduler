#include <SFML/Graphics.hpp>
#include "gui/ProcessUI.h"
#include "gui/Layout.h"

ProcessUI::ProcessUI(Process* process, float x, float y, float width, float height, sf::Font& font)
    : process(process), font(font) {
    
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color::Black);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(1.f);
    background.setPosition(x, y);

    initText(priorityText, std::to_string(process->priority), x + PADDING, y + PADDING);
    initText(burstText, std::to_string(process->burst_time) + " ms", x + FIELD_WIDTH + PADDING, y + PADDING);
    initText(arrivalText, std::to_string(process->arrival_time) + " ms", x + 2 * FIELD_WIDTH + PADDING, y + PADDING);
    initText(timeText, std::to_string(0) + " ms", x + SIM_WIDTH + TIME_WIDTH + PADDING, y + PADDING);

    float simStartX = x + 2 * FIELD_WIDTH + TIME_WIDTH + PADDING + COLUMN_GAP;
    for (int i = 0; i < 12; ++i) {
        sf::RectangleShape block(sf::Vector2f(FIELD_HEIGHT / 2, FIELD_HEIGHT * 0.6f));
        block.setPosition(simStartX + i * (FIELD_HEIGHT / 2 + COLUMN_GAP), y + PADDING);
        block.setFillColor(sf::Color::Black);
        block.setOutlineColor(sf::Color::Black);
        block.setOutlineThickness(1.f);
        simBlocks.push_back(block);
    }
}

void ProcessUI::nextBlock(int index) {
    if (index < simBlocks.size()) {
        simBlocks[index].setFillColor(sf::Color::White);
    }
}

void ProcessUI::setCompletionTime(int time) {
    process->completion_time = time;
    timeText.setString(std::to_string(time) + " ms");
}

void ProcessUI::clearBlocks() {
    for (auto& block : simBlocks) {
        block.setFillColor(sf::Color::Black);
    }
}

void ProcessUI::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(priorityText);
    window.draw(burstText);
    window.draw(arrivalText);
    for (auto& block : simBlocks)
        window.draw(block);
    window.draw(timeText);
}

void ProcessUI::initText(sf::Text& text, const std::string& str, float x, float y) {
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(CHAR_SIZE);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
}
