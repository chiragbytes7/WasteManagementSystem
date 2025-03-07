# Waste Pickup Management System

## Overview
The Waste Pickup Management System is a C++ web application that allows users to request and manage waste pickups. The system follows the MVC (Model-View-Controller) architecture and utilizes the Crow web framework for handling HTTP requests.
Directory called dynamic has 2 subdirectories called model and controller
Directory called static is the views directory
## Features
- Lightweight and efficient C++ backend
- REST API for managing waste pickup requests
- 4 main features which correspond to CRUD operations(post a request, get existing requests, update requuests, delete requests)
- Frontend dynamically binds to API endpoints in the background
- Minimal UI with functional buttons(statically served html, css and JS) 

## Technologies Used
- **C++** (Core application logic)
- **Crow** (Minimal C++ web framework)
- **HTML, CSS, JavaScript** (Frontend UI)
- **cURL/Postman** (Testing API requests)

## Project Structure
```
/waste-pickup-management
│──dynamic/
   │──controller/
│    │── main.cpp              # Entry point of the application
│    │── controller.h          # Controller header file
│    │── controller.cpp        # Handles HTTP routes
│  │──model/
│    │── model.h               # Model header file
│    │── model.cpp             # Business logic for waste pickups
│── static/               # Contains frontend files
│   │── index.html        # Main HTML page
│   │── style.css         # Stylesheet
│   │── script.js         # Client-side logic
│── README.md             # Documentation
```

## Installation and Setup
### Prerequisites
- C++ compiler (GCC or Clang recommended)
- Crow installed
- `g++` for compilation

### Build and Run
1. Clone the repository:
   git clone https://github.com/chiragbytes7/WasteManagementSystem.git
   cd dynamic(go into the dynamic directory)
   
2. Compile the application:
   g++ -o server main.cpp model.cpp controller.cpp -I/usr/local/include -lpthread

3. Run the server in the shell:
   ./server

4. Open the application in a browser:
   http://127.0.0.1:8080/

## Frontend UI
The frontend consists of an interactive HTML page that includes:
- A **button to load existing waste pickup requests** (binds to `GET /api/wastepickups`).
- A **form with input fields and a submit button** to create new pickup requests (binds to `POST /api/wastepickups`).
- A **dynamic table** that updates with the fetched pickup data.
- JavaScript functions that send and receive data from the backend API in real-time.

## API Endpoints
| Method |         Endpoint         | Description                        |
|--------|--------------------------|------------------------------------|
| GET    | `/api/wastepickups`      | Retrieve all waste pickup requests |
| POST   | `/api/wastepickups`      | Create a new waste pickup request  |
| PUT    | `/api/wastepickups/{id}` | Update an existing pickup request  |
| DELETE | `/api/wastepickups/{id}` | Remove a pickup request            |

## Testing the API
### Using `cURL`
- **Get all pickups:**
  ```sh
  curl -X GET http://127.0.0.1:8080/api/wastepickups
  ```
- **Create a new pickup request:**
  ```sh
  curl -X POST http://127.0.0.1:8080/api/wastepickups \
       -H "Content-Type: application/json" \
       -d '{ "wasteType": "Plastic", "pickupLocation": "123 Main St", "pickupDateTime": "2025-03-10T10:00:00", "username": "JohnDoe" }'
  ```

### Using Postman
1. Open Postman
2. Set method to `POST`
3. Enter `http://127.0.0.1:8080/api/wastepickups`
4. In the **Body** tab, select `raw` and set it to `JSON`
5. Add the request payload:
   ```json
   {
       "wasteType": "Plastic",
       "pickupLocation": "123 Main St",
       "pickupDateTime": "2025-03-10T10:00:00",
       "username": "JohnDoe"
   }
   ```
6. Click **Send**

## Future Enhancements
- Database integration for persistent storage
- Authentication and user roles
- Improved UI with dynamic status updates
- Deployment on a cloud server


