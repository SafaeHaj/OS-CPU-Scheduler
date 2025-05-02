#ifndef START_H
#define START_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

// Forward declarations
class DropDownMenu;
class InputUI;
class ProcessUIManager;
class Process;
class Scheduler;

class Start {
public:
    Start(sf::Font& font, DropDownMenu& d, InputUI& ui, ProcessUIManager& mgr, std::vector<Process*>& procList);
    
    void draw(sf::RenderWindow& win);
    void handleEvent(const sf::Event& ev, sf::Vector2f mousePos);
    void update();

private:
    void launchSimulation();

    // References to external components
    DropDownMenu& dropdown;
    InputUI& inputUI;
    ProcessUIManager& manager;
    std::vector<Process*>& processes;

    // UI Elements
    sf::RectangleShape startButton;
    sf::Text startText;

    // Simulation state
    bool clicked = false;
    std::unique_ptr<Scheduler> scheduler;
    sf::Clock clock;
    size_t sim_step_index = 0;
    bool simulation_done = false;
};

#endif // START_H