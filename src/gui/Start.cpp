#include<SFML/Graphics.hpp>
#include "gui/Start.h"
#include "gui/InputUI.h"

void Start::run() {
    // Main loop to handle different statuses
    switch (status) {
        case Status::START:
            // wait for Start button press
            break;
        case Status::INPUT:
            // show InputUI, validate inputs
            if (inputUI.isInputComplete()) {
                // validate -> if OK:
                status = Status::RUNNING;
                // else:
                // inputUI.reset() or display error
            }
            break;
        case Status::RUNNING:
            // run scheduling simulation, animate bars
            break;
        case Status::DONE:
            // display final results, wait for exit or restart
            break;
    }
}
