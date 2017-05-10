#include "controllers.hpp"

int main() {
    ControllerInit controllerInit;
    controllerInit.initialize();
    controllerInit.showUI();
    return 0;
}
