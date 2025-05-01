#include "gui/InputUI.h"
#include <iostream>

InputUI::InputUI(sf::Font& font, sf::Vector2f winSize)
    : font(font), windowSize(winSize) {

    countBox.setSize({100, 40});
    countBox.setPosition(winSize.x / 2 - 50, 100);
    countBox.setFillColor(sf::Color::White);
    countBox.setOutlineColor(sf::Color::Black);
    countBox.setOutlineThickness(1);

    countText.setFont(font);
    countText.setCharacterSize(20);
    countText.setFillColor(sf::Color::Black);
    countText.setPosition(countBox.getPosition() + sf::Vector2f(5, 5));

    inputBox.setSize({80, 40});
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setOutlineThickness(1);

    label.setFont(font);
    label.setCharacterSize(20);
    label.setFillColor(sf::Color::Black);
}

void InputUI::handleEvent(const sf::Event& event, sf::Vector2f) {
    if (status == Status::IDLE || status == Status::INPUTUI) {
        if (event.type == sf::Event::TextEntered) {
            if (std::isdigit(event.text.unicode) && countBuffer.size() < 3) {
                countBuffer += static_cast<char>(event.text.unicode);
                countText.setString(countBuffer);
            } else if (event.text.unicode == '\b' && !countBuffer.empty()) {
                countBuffer.pop_back();
                countText.setString(countBuffer);
            } else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
                int n = std::stoi(countBuffer.empty() ? "0" : countBuffer);
                if (n > 0) {
                    numProcesses = n;
                    results.assign(n, {0, 0, 0});
                    currentRow = 0;
                    currentField = PRIORITY;
                    status = Status::INPUT;
                } else {
                    displayError("Enter a positive number");
                }
            }
        }
    } else if (status == Status::INPUT) {
        if (event.type == sf::Event::TextEntered) {
            char c = static_cast<char>(event.text.unicode);
            if (std::isdigit(c) && buffer.size() < 4) {
                buffer.push_back(c);
            } else if (c == '\b' && !buffer.empty()) {
                buffer.pop_back();
            } else if (c == '\r' || c == '\n') {
                if (validateAndStore()) {
                    nextFieldOrRow();
                    if (currentRow >= numProcesses)
                        status = Status::DONE;
                }
            }
            updateDisplay();
        }
    }
}

bool InputUI::validateAndStore() {
    int v = std::stoi(buffer.empty() ? "0" : buffer);
    auto& entry = results[currentRow];
    switch (currentField) {
        case PRIORITY:   entry.priority = v; break;
        case BURST:      entry.burstTime = v; break;
        case ARRIVAL:    entry.arrival = v; break;
    }
    return true;
}

void InputUI::nextFieldOrRow() {
    buffer.clear();
    if (currentField == ARRIVAL) {
        currentField = PRIORITY;
        currentRow++;
    } else {
        currentField = static_cast<Field>(int(currentField) + 1);
    }
}

void InputUI::updateDisplay() {
    float y = baseY + rowHeight * currentRow;
    float x = xStart;

    switch (currentField) {
        case PRIORITY: x += 40; break;
        case BURST:    x += 140; break;
        case ARRIVAL:  x += 280; break;
    }

    inputBox.setPosition(x, y);
    label.setString(buffer);
    label.setPosition(x + 5, y + 5);
}

void InputUI::draw(sf::RenderWindow& win) {
    if (status == Status::IDLE || status == Status::INPUTUI) {
        win.draw(countBox);
        win.draw(countText);
    } else if (status == Status::INPUT || status == Status::DONE) {
        for (int i = 0; i < currentRow; ++i) {
            float y = baseY + rowHeight * i;

            sf::Text pText, bText, aText;
            pText.setFont(font);
            bText.setFont(font);
            aText.setFont(font);
            pText.setCharacterSize(18);
            bText.setCharacterSize(18);
            aText.setCharacterSize(18);
            pText.setFillColor(sf::Color::Black);
            bText.setFillColor(sf::Color::Black);
            aText.setFillColor(sf::Color::Black);

            pText.setString(std::to_string(results[i].priority));
            pText.setPosition(xStart + 40, y + 15);

            bText.setString(std::to_string(results[i].burstTime) + " ms");
            bText.setPosition(xStart + 140, y + 15);

            aText.setString(std::to_string(results[i].arrival) + " ms");
            aText.setPosition(xStart + 280, y + 15);

            win.draw(pText);
            win.draw(bText);
            win.draw(aText);
        }

        if (status == Status::INPUT) {
            win.draw(inputBox);
            win.draw(label);
        }
    }
}

bool InputUI::isInputComplete() const {
    return status == Status::DONE;
}

std::vector<ProcessInput> InputUI::getProcessValues() const {
    return results;
}

void InputUI::displayError(const std::string& msg) {
    std::cerr << "Error: " << msg << std::endl;
}
