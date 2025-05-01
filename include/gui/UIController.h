#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include "gui/InputUI.h"
#include "gui/Start.h"
#include "gui/DropDownMenu.h"
#include "gui/ProcessUIManager.h"


class UIController {
    public:
        UIController();
        ~UIController();
    
        void initialize();
        void update();
        void render(sf::RenderWindow& window);
        void handleEvent(const sf::Event& event, sf::Vector2f mousePos);
    
    private:
        sf::Font font;
        Start start;
        InputUI inputUI;
        DropDownMenu dropdownMenu;
        ProcessUIManager processUIManager;
    
        void transitionToInput();
        void transitionToRun();
    };
    