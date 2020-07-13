#pragma once
#include "Menu.h"
class SettingsMenu : public Menu {
private:
    Button* back;
public:
    SettingsMenu();
    void render();
    void clean();
    void update();
};

