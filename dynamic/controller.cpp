#include "controller.h"
using namespace std;
void WastePickupController::setupRoutes(crow::SimpleApp& app) {
    std::cout << "Registering routes..." << std::endl;
// **CREATE (POST)**
//std::cout << "Registering POST /api/wastepickups" << std::endl;
        CROW_ROUTE(app, "/post")([]() {
        std::ifstream file("static/post.html");
        if (!file) return crow::response(404, "File not found");
        std::stringstream buffer;
        buffer << file.rdbuf();
        return crow::response(buffer.str());
    });
CROW_ROUTE(app, "/get")([]() {
    std::ifstream file("static/get.html");
    if (!file) return crow::response(404, "File not found");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return crow::response(buffer.str());
});
CROW_ROUTE(app, "/update")([]() {
    std::ifstream file("static/update.html");
    if (!file) return crow::response(404, "File not found");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return crow::response(buffer.str());
});
CROW_ROUTE(app, "/delete")([]() {
    std::ifstream file("static/delete.html");
    if (!file) return crow::response(404, "File not found");

    std::stringstream buffer;
    buffer << file.rdbuf();
    return crow::response(buffer.str());
});


    CROW_ROUTE(app, "/api/wastepickups").methods(crow::HTTPMethod::POST)([this](const crow::request& req, crow::response& res) {
        cout << "entered the post request route" << endl;        
        auto json = crow::json::load(req.body);
        if (!json) {
            res.code = 400;
            res.body = "Invalid JSON";
            res.end();
            return;
        }

        auto pickup = model.createPickup(json["wasteType"].s(), json["pickupLocation"].s(),
                                         json["pickupDateTime"].s(), json["username"].s());

        crow::json::wvalue response;
        response["id"] = pickup.id;
        res.code = 201;
        res.write(response.dump());
        res.end();
    });

std::cout << "Registering GET /api/wastepickups" << std::endl;
    // **READ (GET)**
    CROW_ROUTE(app, "/api/wastepickups").methods(crow::HTTPMethod::GET)([this](const crow::request& req, crow::response& res) {
        auto pickups = model.getAllPickups();
        crow::json::wvalue response;
        response["pickups"] = crow::json::wvalue::list();

        for (const auto& pickup : pickups) {
            crow::json::wvalue item;
            item["id"] = pickup.id;
            item["wasteType"] = pickup.wasteType;
            item["pickupLocation"] = pickup.pickupLocation;
            item["pickupDateTime"] = pickup.pickupDateTime;
            item["status"] = pickup.status;
            item["username"] = pickup.username;  // ✅ Fixed field name

            response["pickups"][response["pickups"].size()] = std::move(item);
        }
        res.set_header("Content-Type", "application/json");
        res.code = 200;
        res.write(response.dump());
        res.end();
    });

    // **UPDATE (PUT)**
std::cout << "Registering 3rd endpoint" << std::endl;
    CROW_ROUTE(app, "/api/wastepickups/<int>").methods(crow::HTTPMethod::PUT)([this](const crow::request& req, crow::response& res, int id) {
        auto json = crow::json::load(req.body);
        if (!json) {
            res.code = 400;
            res.body = "Invalid JSON";
            res.end();
            return;
        }

        bool updated = model.updatePickup(id, 
            json.has("status") ? std::string(json["status"].s()) : std::string(""),  // ✅ Fixed ternary operator
            json.has("pickupDateTime") ? std::string(json["pickupDateTime"].s()) : std::string("")
        );

        res.code = updated ? 200 : 404;
        res.body = updated ? "Pickup updated" : "Pickup not found";
        res.end();
    });
CROW_ROUTE(app, "/")([]() {
    std::ifstream file("static/index.html");  // Open the file
    if (!file) return crow::response(404, "File not found");  // Handle missing file

    std::stringstream buffer;
    buffer << file.rdbuf();  // Read file contents into a string
    return crow::response(buffer.str());  // Return HTML file contents as response
});

    // **DELETE**
std::cout << "Registering default route" << std::endl;
    CROW_ROUTE(app, "/api/wastepickups/<int>").methods(crow::HTTPMethod::DELETE)([this](const crow::request& req, crow::response& res, int id) {
        bool deleted = model.deletePickup(id);
        res.code = deleted ? 200 : 404;
        res.body = deleted ? "Pickup deleted" : "Pickup not found";
        res.end();
    });
std::cout << "finished registering" << std::endl;

}
