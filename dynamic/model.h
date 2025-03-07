#include "crow.h"
#include <stdio.h>
#include <string.h>
#ifndef WASTE_PICKUP_H
#define WASTE_PICKUP_H

#include <string>
#include <vector>
#include <mutex>
using namespace std;

struct WastePickup{
int id;
string wasteType;
string pickupLocation;
string pickupDateTime;
string status;
string username;
};

class WastePickupModel{
private:
vector<WastePickup> wastePickups;
mutex wasteMutex;
int nextId = 1;

public:
    WastePickup createPickup(const std::string& wasteType, const std::string& location,
                             const std::string& dateTime, const std::string& username);

    std::vector<WastePickup> getAllPickups();

    bool updatePickup(int id, const std::string& status, const std::string& dateTime);

    bool deletePickup(int id);
};

#endif
