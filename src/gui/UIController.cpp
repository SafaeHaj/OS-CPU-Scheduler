#include "gui/UIController.h"
#include <iostream>

UIController::UIController()
  : inputUI(font, {800,600})
  , processManager(50, 100, font)
  , dropdown(
        { processManager.getHeaderX(3),
          processManager.getRowsY() - 50},
        processManager.getHeaderWidth(3),
        { "First Come First Served",
          "Shortest Job First",
          "Priority",
          "Round Robin",
          "Priority RR"
        },
        font
    )
{}

UIController::~UIController() {
    for (auto p : processes) delete p;
}

void UIController::initialize() {
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Failed to load font\n";
    }
}

void UIController::handleEvent(const sf::Event& event) {
    // global mouse pos
    sf::Vector2f mp(
      (float)sf::Mouse::getPosition().x,
      (float)sf::Mouse::getPosition().y
    );
    inputUI.handleEvent(event);
    dropdown.handleEvent(const_cast<sf::Event&>(event), mp);
}

void UIController::update() {
    if (!processesLaunched && inputUI.isInputComplete()) {
        launchProcesses();
        processesLaunched = true;
    }
}

void UIController::render(sf::RenderWindow& window) {
    dropdown.draw(window);
    inputUI.draw(window);
    processManager.draw(window);
}

void UIController::launchProcesses() {
    for (auto p : processes) delete p;
    processes.clear();

    auto vals = inputUI.getProcessValues();
    processes.reserve(vals.size());
    for (size_t i = 0; i < vals.size(); ++i) {
        const auto& v = vals[i];
        processes.push_back(new Process(
            int(i), v.arrival, v.burstTime, v.priority
        ));
    }
    processManager.setProcesses(processes);
}
