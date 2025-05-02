#include "core/Scheduler.h"
#include "core/FCFS.h"
#include "core/SJF.h"
#include "core/Priority.h"
#include "core/RR.h"
#include "core/PriorityRR.h"
#include "gui/Start.h"
#include "gui/Layout.h"
#include "gui/DropDownMenu.h"
#include "gui/InputUI.h"
#include "gui/ProcessUIManager.h"
#include "Process.h"

Start::Start(sf::Font& font, DropDownMenu& d, InputUI& ui, ProcessUIManager& mgr, std::vector<Process*>& procList)
    : dropdown(d), inputUI(ui), manager(mgr), processes(procList) {
    startButton.setSize({200, FIELD_HEIGHT});
    startButton.setPosition(50, 500);
    startButton.setFillColor(sf::Color::White);
    startButton.setOutlineColor(sf::Color::Black);
    startButton.setOutlineThickness(1);

    startText.setFont(font);
    startText.setString("Start Simulation");
    startText.setCharacterSize(CHAR_SIZE);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(
        startButton.getPosition().x + PADDING,
        startButton.getPosition().y + (FIELD_HEIGHT - CHAR_SIZE) / 2
    );
}

void Start::draw(sf::RenderWindow& win) {
    win.draw(startButton);
    win.draw(startText);
}

void Start::handleEvent(const sf::Event& ev, sf::Vector2f mousePos) {
    if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
        if (startButton.getGlobalBounds().contains(mousePos)) {
            clicked = true;
            launchSimulation();
        }
    }
}

void Start::launchSimulation() {
    std::string selected = dropdown.getSelectedItem();
    std::vector<ProcessInput> vals = inputUI.getProcessValues();
    processes.clear();

    for (size_t i = 0; i < vals.size(); ++i) {
        processes.push_back(new Process(i, vals[i].arrival, vals[i].burstTime, vals[i].priority));
    }

    if (selected == "First Come First Served") {
        scheduler = std::make_unique<FCFS>();
    } else if (selected == "Shortest Job First") {
        scheduler = std::make_unique<SJF>();
    } else if (selected == "Priority") {
        scheduler = std::make_unique<Priority>();
    } else if (selected == "Round Robin") {
        scheduler = std::make_unique<RR>(4); // to modify so its not hardcoded
    } else if (selected == "Priority RR") {
        scheduler = std::make_unique<PriorityRR>(4);
    } else {
        return;
    }

    for (auto* p : processes) {
        scheduler->processes.push_back(*p);
    }

    scheduler->schedule(); // Builds timeline
    scheduler->current_time = 0;
    sim_step_index = 0;
    simulation_done = false;
    clock.restart();
}

void Start::update() {
    if (!scheduler || simulation_done || clock.getElapsedTime().asMilliseconds() < 100) {
        return;
    }

    clock.restart();

    if (sim_step_index >= scheduler->timeline.size()) {
        simulation_done = true;
        return;
    }

    const auto& [pid, start, end] = scheduler->timeline[sim_step_index];
    int blockIdx = scheduler->current_time - start;

    if (blockIdx >= 0 && blockIdx < 12) {
        manager.processRows[pid].nextBlock(blockIdx);
    }

    scheduler->current_time += 1;
    if (scheduler->current_time >= end) {
        manager.processRows[pid].setCompletionTime(end);
        sim_step_index++;
    }
}