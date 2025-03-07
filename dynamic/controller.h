#ifndef WASTE_PICKUP_CONTROLLER_H
#define WASTE_PICKUP_CONTROLLER_H

#include "crow.h"
#include "model.h"

class WastePickupController {
private:
    WastePickupModel model;

public:
    void setupRoutes(crow::SimpleApp& app);
};

#endif  // WASTE_PICKUP_CONTROLLER_H
