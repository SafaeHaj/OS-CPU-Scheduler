#pragma once
#include <SFML/Graphics.hpp>
#include "gui/InputUI.h"
#include "gui/DropDownMenu.h"
#include "gui/ProcessUIManager.h"
#include "Process.h"

class UIController {
public:
    UIController();
    ~UIController();

    void initialize();
    void handleEvent(const sf::Event& event);
    void update();
    void render(sf::RenderWindow& window);

private:
    sf::Font font;

    InputUI         inputUI;
    DropDownMenu    dropdown;
    ProcessUIManager processManager;

    bool processesLaunched = false;
    std::vector<Process*> processes;

    void launchProcesses();
};
