#include "gui/InputUI.h"
#include "gui/Layout.h"
#include <iostream>

InputUI::InputUI(sf::Font& font, sf::Vector2f ws)
  : font(font), winSize(ws)
{
    promptText.setFont(font);
    promptText.setString("Processes:");
    promptText.setCharacterSize(24);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(50, 50);

    countBox.setSize({FIELD_WIDTH, FIELD_HEIGHT});
    countBox.setPosition(200, 40);
    countBox.setFillColor(sf::Color::Black);
    countBox.setOutlineColor(sf::Color::White);
    countBox.setOutlineThickness(1);

    countText.setFont(font);
    countText.setString("");
    countText.setCharacterSize(CHAR_SIZE);
    countText.setFillColor(sf::Color::White);
    countText.setPosition(countBox.getPosition().x + PADDING, countBox.getPosition().y + (FIELD_HEIGHT - CHAR_SIZE) / 2);

    goButton.setSize({80, FIELD_HEIGHT});
    goButton.setPosition(countBox.getPosition() + sf::Vector2f(FIELD_WIDTH + 20, 0));
    goButton.setFillColor(sf::Color::White);
    goButton.setOutlineColor(sf::Color::Black);
    goButton.setOutlineThickness(1);

    goText.setFont(font);
    goText.setString("Go");
    goText.setCharacterSize(CHAR_SIZE);
    goText.setFillColor(sf::Color::Black);
    goText.setPosition(goButton.getPosition().x + 15, goButton.getPosition().y + (FIELD_HEIGHT - CHAR_SIZE) / 2);
}


void InputUI::handleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mp(event.mouseButton.x, event.mouseButton.y);
        // Focus fields
        bool anyField = false;
        for (auto& f : fields) {
            if (f.box.getGlobalBounds().contains(mp)) {
                f.active = true; f.box.setOutlineThickness(3);
                anyField = true;
            } else {
                f.active = false; f.box.setOutlineThickness(1);
            }
        }
        // Focus count
        if (!anyField && countBox.getGlobalBounds().contains(mp)) {
            countActive = true;
        } else if (!anyField && !countBox.getGlobalBounds().contains(mp)) {
            countActive = false;
        }
        // Go button
        if (goButton.getGlobalBounds().contains(mp)) {
            commitCount();
        }
    }

    if (event.type == sf::Event::TextEntered) {
        char c = static_cast<char>(event.text.unicode);
        // Only digits, backspace, enter
        if (countActive) {
            if (std::isdigit(c) && countBuffer.size()<2) {
                countBuffer+=c;
            } else if (c=='\b' && !countBuffer.empty()) {
                countBuffer.pop_back();
            } else if ((c=='\r'||c=='\n')) {
                commitCount();
            }
            countText.setString(countBuffer);
            return;
        }
        // Else check fields
        for (auto& f : fields) if (f.active) {
            if (std::isdigit(c) && f.buffer.size()<3) {
                f.buffer+=c;
            } else if (c=='\b' && !f.buffer.empty()) {
                f.buffer.pop_back();
            } else if (c=='\r'||c=='\n') {
                // commit field
                int v=std::stoi(f.buffer.empty()?"0":f.buffer);
                auto& pi = values[f.row];
                if (f.col==0) pi.priority=v;
                else if(f.col==1) pi.burstTime=v;
                else pi.arrival=v;
                f.active=false;
                f.box.setOutlineThickness(1);
            }
            updateField(f);
            return;
        }
    }
}

void InputUI::commitCount() {
    if (countBuffer.empty()) return;
    int n = std::stoi(countBuffer);
    if (n>0 && n!=numProcesses) {
        numProcesses=n;
        values.assign(n, {});
        createFields();
    }
    countActive=false;
}

void InputUI::createFields() {
    fields.clear();
    const float x=50, y0=120;
    for(int r=0;r<numProcesses;++r){
        for(int c=0;c<3;++c){
            Field f;
            f.row=r; f.col=c;
            float xpos = (c==0?x+40: c==1?x+140: x+280);
            f.box.setSize({FIELD_WIDTH, FIELD_HEIGHT});
            f.box.setPosition(xpos, y0+r*ROW_HEIGHT);
            f.box.setFillColor(sf::Color::Black);
            f.box.setOutlineColor(sf::Color::White);
            f.box.setOutlineThickness(1);
            f.text.setFont(font);
            f.text.setCharacterSize(CHAR_SIZE);
            f.text.setFillColor(sf::Color::White);
            f.text.setPosition(f.box.getPosition().x + PADDING, f.box.getPosition().y + (FIELD_HEIGHT - CHAR_SIZE) / 2);
            updateField(f);
            fields.push_back(f);
        }
    }
}

void InputUI::updateField(Field& f) {
    f.text.setString(f.buffer);
}

void InputUI::draw(sf::RenderWindow& win) {
    // always draw count UI
    win.draw(promptText);
    win.draw(countBox);
    win.draw(countText);
    win.draw(goButton);
    win.draw(goText);
    // draw fields
    for(auto& f:fields){
        win.draw(f.box);
        win.draw(f.text);
    }
}

bool InputUI::isInputComplete() const {
    if (numProcesses==0) return false;
    for(auto& p:values)
        if(p.priority<=0||p.burstTime<=0) return false;
    return true;
}

std::vector<ProcessInput> InputUI::getProcessValues() const {
    return values;
}
