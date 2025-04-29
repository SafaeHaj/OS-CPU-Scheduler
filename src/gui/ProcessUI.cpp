#include <SFML/Graphics.hpp>
#include "ProcessUI.h"

ProcessUI::ProcessUI(Process* process,float x, float y, float width, float height, sf::Font& font)
        : process(process), font(font) {

        background.setSize(sf::Vector2f(width, height));
        background.setFillColor(sf::Color(30, 30, 30));
        background.setOutlineColor(sf::Color::White);
        background.setOutlineThickness(1.f);
        background.setPosition(x, y);

        initText(priorityText, std::to_string(process->priority), x + 30, y + 15);
        initText(burstText, std::to_string(process->burst_time) + " ms", x + 90, y + 15);
        initText(arrivalText, std::to_string(process->arrival_time) + " ms",x +  180, y + 15);
        initText(timeText, std::to_string(process->completion_time) + " ms", x + 600, y + 15);


        float simStartX = 280+x;
        for (int i = 0; i < 12; ++i) {
            sf::RectangleShape block(sf::Vector2f(20, 30));
            block.setPosition(simStartX + i * 22, y + 10);
            block.setFillColor(sf::Color::White);
            block.setOutlineColor(sf::Color::Black);
            block.setOutlineThickness(1.f);
            simBlocks.push_back(block);
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
        text.setCharacterSize(16);
        text.setFillColor(sf::Color::White);
        text.setPosition(x, y);
    }
