#include "model.h"
using namespace std;
WastePickup WastePickupModel::createPickup(const std::string& wasteType, const std::string& location,const std::string& dateTime, const std::string& userName){
lock_guard<std::mutex> lock(wasteMutex);
WastePickup newPickup = {nextId++, wasteType, location, dateTime, "Pending", userName};
wastePickups.push_back(newPickup);
return newPickup;
}

vector<WastePickup> WastePickupModel::getAllPickups() {
    std::lock_guard<std::mutex> lock(wasteMutex);
    return wastePickups;
}

bool WastePickupModel::updatePickup(int id, const std::string& status, const std::string& dateTime) {
    std::lock_guard<std::mutex> lock(wasteMutex);

    for (auto& pickup : wastePickups) {
        if (pickup.id == id) {
            if (!status.empty()) pickup.status = status;
            if (!dateTime.empty()) pickup.pickupDateTime = dateTime;
            return true;
        }
    }
    return false;
}


bool WastePickupModel::deletePickup(int id) {
    std::lock_guard<std::mutex> lock(wasteMutex);

    for (auto it = wastePickups.begin(); it != wastePickups.end(); ++it) {
        if (it->id == id) {
            wastePickups.erase(it);
            return true;
        }
    }
    return false;
}
