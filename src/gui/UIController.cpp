#include <SFML/Graphics.hpp>
#include "gui/UIController.h"


void UIController::handleEvent(const sf::Event& event, sf::Vector2f mousePos) {
    switch (status) {
        case AppStatus::START_SCREEN:
            start.handleEvent(event, mousePos);
            if (start.isReady()) { // e.g., returns true when "Start" button clicked
                status = AppStatus::INPUT_PROCESS_COUNT;
            }
            break;

        case AppStatus::INPUT_PROCESS_COUNT:
            inputUI.doInputUIState(event);
            if (inputUI.readyToInputData()) {
                status = AppStatus::INPUT_PROCESS_DATA;
            }
            break;

        case AppStatus::INPUT_PROCESS_DATA:
            inputUI.handleEvent(event, mousePos);
            if (inputUI.isInputComplete()) {
                status = AppStatus::SELECT_ALGORITHM;
            }
            break;

        case AppStatus::SELECT_ALGORITHM:
            dropdownMenu.handleEvent(event, mousePos);
            if (dropdownMenu.isAlgorithmSelected()) {
                status = AppStatus::RUNNING;
            }
            break;

        case AppStatus::RUNNING:
            processUIManager.run(inputUI.getProcessValues(), dropdownMenu.getSelectedAlgorithm());
            status = AppStatus::DONE;
            break;

        case AppStatus::DONE:
            // maybe wait for restart or quit
            break;

        default: break;
    }
}

void UIController::render(sf::RenderWindow& window) {
    switch (status) {
        case AppStatus::START_SCREEN:
            start.draw(window);
            break;
        case AppStatus::INPUT_PROCESS_COUNT:
        case AppStatus::INPUT_PROCESS_DATA:
            inputUI.draw(window);
            break;
        case AppStatus::SELECT_ALGORITHM:
            dropdownMenu.draw(window);
            break;
        case AppStatus::RUNNING:
        case AppStatus::DONE:
            processUIManager.draw(window);
            break;
        default: break;
    }
}
