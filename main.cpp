#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <httplib.h>
#include <unordered_map>
#include <fstream>

using json = nlohmann::json;

// A simple in-memory user database for demonstration
const std::unordered_map<std::string, std::string> users = {
        {"admin", "password123"},
        {"user", "hello"}
};

// A simple secret token for demonstration
const std::string SECRET_TOKEN = "my-super-secret-token-12345";

// Helper function to check for a valid token
bool is_token_valid(const httplib::Request& req) {
    std::string auth_header = req.get_header_value("Authorization");
    return auth_header == "Bearer " + SECRET_TOKEN;
}

int main() {
    std::cout << "Starting C++ Authenticated Backend..." << std::endl;

    httplib::Server svr;

    // --- Public Endpoint: Login ---
    svr.Post("/api/login", [](const httplib::Request& req, httplib::Response& res) {
        try {
            json login_data = json::parse(req.body);
            std::string username = login_data.value("username", "");
            std::string password = login_data.value("password", "");

            auto it = users.find(username);
            if (it != users.end() && it->second == password) {
                // Login successful, return the token
                json response = {{"message", "Login successful"}, {"token", SECRET_TOKEN}};
                res.set_content(response.dump(), "application/json");
            } else {
                // Login failed
                json response = {{"error", "Invalid credentials"}};
                res.status = 401; // Unauthorized
                res.set_content(response.dump(), "application/json");
            }
        } catch (const json::parse_error& e) {
            json response = {{"error", "Bad Request"}, {"message", "Invalid JSON"}};
            res.status = 400;
            res.set_content(response.dump(), "application/json");
        }
    });

    // --- Protected Endpoint: Dashboard Data ---
    svr.Get("/api/dashboard", [](const httplib::Request& req, httplib::Response& res) {
        // FIX 1: Check for authentication directly inside the handler
        if (!is_token_valid(req)) {
            json error_response = {{"error", "Unauthorized"}, {"message", "Invalid or missing token"}};
            res.set_content(error_response.dump(), "application/json");
            res.status = 401;
            return;
        }

        // If token is valid, proceed
        json response = {
                {"user", "Authenticated User"},
                {"data", {"Welcome to the dashboard!", "This is protected data.", "Here are your stats: 42"}}
        };
        res.set_content(response.dump(), "application/json");
    });

    // --- File Serving ---
    // We will serve the React build files from the 'frontend/dist' directory
    std::string www_path = std::string(WWW_ROOT_PATH) + "/frontend/dist";
    std::cout << "Mounting web UI from: " << www_path << std::endl;
    svr.set_mount_point("/", www_path);

    // FIX 2: Add a catch-all handler to serve index.html for client-side routing
    svr.Get(".*", [&](const httplib::Request& req, httplib::Response& res) {
        // If the request is for an API endpoint, don't handle it here.
        if (req.path.rfind("/api/", 0) == 0) {
            return;
        }
        // If the request looks like it's for a file (has a dot), let the mount point handle it.
        if (req.path.find('.') != std::string::npos) {
            return;
        }
        // Otherwise, serve the index.html file.
        std::ifstream index_file(www_path + "/index.html");
        if (index_file.is_open()) {
            std::string content((std::istreambuf_iterator<char>(index_file)), std::istreambuf_iterator<char>());
            res.set_content(content, "text/html");
        } else {
            res.status = 404;
            res.set_content("Not Found", "text/plain");
        }
    });

    std::cout << "Server started successfully!" << std::endl;
    std::cout << "Open your browser and go to: http://localhost:8080" << std::endl;
    std::cout << "Press Ctrl+C in this console to stop the server." << std::endl;

    svr.listen("localhost", 8080);

    return 0;
}