#include <iostream>
#include "json_proto/error_response/ApiError.hpp"

int main() {
    std::cout << "=== API Error Response Example ===" << std::endl;
    
    // Example 1: Parse error response JSON
    std::cout << "\n1. Parse error response JSON:" << std::endl;
    
    std::string json_str = R"({
        "success": false,
        "error": {
            "code": 102,
            "message": "Validation failed",
            "details": [
                {
                    "field": "email",
                    "issue": "is not a valid email address",
                    "message": ""
                },
                {
                    "field": "password",
                    "issue": "",
                    "message": "must be at least 8 characters long"
                }
            ]
        }
    })";

    try {
        auto api_error = nlohmann::json::parse(json_str).get<error_response::ApiError>();
        
        std::cout << "Success: " << std::boolalpha << api_error.success.value_or(false) << std::endl;
        
        if (api_error.error) {
            auto error = api_error.error.value();
            std::cout << "Error Code: " << error.code.value_or(0) << std::endl;
            std::cout << "Error Message: " << error.message.value_or("") << std::endl;
            
            if (error.details) {
                std::cout << "Error Details:" << std::endl;
                for (const auto& detail : error.details.value()) {
                    std::cout << "  - Field: " << detail.field.value_or("") << std::endl;
                    std::cout << "    Issue: " << detail.issue.value_or("") << std::endl;
                    std::cout << "    Message: " << detail.message.value_or("") << std::endl;
                }
            }
        }

    } catch (const std::exception& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
    }

    // Example 2: Create error response object and serialize to JSON
    std::cout << "\n2. Create error response object and serialize:" << std::endl;
    
    error_response::ApiError custom_error;
    custom_error.success = false;
    
    error_response::Error error_obj;
    error_obj.code = 404;
    error_obj.message = "Resource not found";
    
    error_response::Detail detail1;
    detail1.field = "user_id";
    detail1.message = "User does not exist";
    
    std::vector<error_response::Detail> details = {detail1};
    error_obj.details = details;
    
    custom_error.error = error_obj;
    
    nlohmann::json j = custom_error;
    std::cout << "Generated JSON:" << std::endl;
    std::cout << j.dump(2) << std::endl;

    // Example 3: Handle missing optional fields
    std::cout << "\n3. Handle incomplete error response:" << std::endl;
    
    std::string partial_json = R"({
        "success": false,
        "error": {
            "code": 500
        }
    })";
    
    try {
        auto partial_error = nlohmann::json::parse(partial_json).get<error_response::ApiError>();
        std::cout << "Success: " << std::boolalpha << partial_error.success.value_or(false) << std::endl;
        
        if (partial_error.error) {
            auto error = partial_error.error.value();
            std::cout << "Error Code: " << error.code.value_or(0) << std::endl;
            std::cout << "Error Message: " << error.message.value_or("(no message)") << std::endl;
            
            if (error.details) {
                std::cout << "Details count: " << error.details.value().size() << std::endl;
            } else {
                std::cout << "No details provided" << std::endl;
            }
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Parse error: " << e.what() << std::endl;
    }

    return 0;
}