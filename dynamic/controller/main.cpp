#include "crow.h"
#include "controller.h"
#include <iostream>

int main() {
    crow::SimpleApp app;
    WastePickupController controller;

    std::cout << "Calling setupRoutes()..." << std::endl;
    controller.setupRoutes(app);

    

    app.port(8080).run();
}

