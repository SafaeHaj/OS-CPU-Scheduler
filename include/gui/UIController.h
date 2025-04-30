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
    void render();

private:
    InputUI inputUI;
    Start start;
    DropDownMenu dropdownMenu;
    ProcessUIManager processUIManager;
};

#endif // UICONTROLLER_H