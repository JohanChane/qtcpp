#include <iostream>
#include <string>
#include "json_proto/user_profile/UserProfile.hpp"

using namespace user_profile;
using nlohmann::json;

int main() {
    // Example JSON string
    std::string jsonString = R"(
        {
            "id": 12345,
            "username": "john_doe",
            "email": "john.doe@example.com",
            "date_of_birth": "1990-01-15",
            "is_active": true
        }
    )";

    try {
        // Parse JSON string
        UserProfile profile = json::parse(jsonString);

        // Access parsed data
        std::cout << "User Information:" << std::endl;
        
        if (profile.id.has_value()) {
            std::cout << "ID: " << profile.id.value() << std::endl;
        }
        
        if (profile.username.has_value()) {
            std::cout << "Username: " << profile.username.value() << std::endl;
        }
        
        if (profile.email.has_value()) {
            std::cout << "Email: " << profile.email.value() << std::endl;
        }
        
        if (profile.date_of_birth.has_value()) {
            std::cout << "Date of Birth: " << profile.date_of_birth.value() << std::endl;
        }
        
        if (profile.is_active.has_value()) {
            std::cout << "Active Status: " << (profile.is_active.value() ? "Yes" : "No") << std::endl;
        }

        // Test case with missing fields
        std::string partial_json_string = R"(
            {
                "id": 67890,
                "username": "jane_smith"
            }
        )";

        std::cout << "\nPartial User Information:" << std::endl;
        UserProfile partial_profile = json::parse(partial_json_string);
        
        std::cout << "ID: " << partial_profile.id.value_or(-1) << std::endl;
        std::cout << "Username: " << partial_profile.username.value_or("Unknown") << std::endl;
        
        // Use value_or to provide default values
        std::cout << "Email: " << partial_profile.email.value_or("Not set") << std::endl;
        std::cout << "Active Status: " << (partial_profile.is_active.value_or(false) ? "Yes" : "No") << std::endl;

        // Convert object back to JSON
        json j = partial_profile;
        std::cout << "\nConverted back to JSON: " << j.dump(2) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "JSON parsing error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}