#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include "json_proto/error_response/BadRequest.hpp"

using nlohmann::json;

void test_bad_request() {
    std::cout << "=== Testing BadRequest JSON parsing ===" << std::endl;
    
    // Test case 1: Complete JSON object
    std::cout << "\n1. Testing complete JSON object:" << std::endl;
    std::string json_str1 = R"({
        "code": 400,
        "details": "Invalid parameter: name",
        "msg": "Bad Request",
        "request_id": "req_123456",
        "sub_code": "INVALID_PARAM",
        "sub_msg": "Parameter validation failed"
    })";
    
    try {
        auto json_obj1 = json::parse(json_str1);
        error_response::BadRequest bad_request1 = json_obj1.get<error_response::BadRequest>();
        
        std::cout << "Code: " << (bad_request1.code ? std::to_string(*bad_request1.code) : "null") << std::endl;
        std::cout << "Details: " << (bad_request1.details ? *bad_request1.details : "null") << std::endl;
        std::cout << "Msg: " << (bad_request1.msg ? *bad_request1.msg : "null") << std::endl;
        std::cout << "Request ID: " << (bad_request1.request_id ? *bad_request1.request_id : "null") << std::endl;
        std::cout << "Sub Code: " << (bad_request1.sub_code ? *bad_request1.sub_code : "null") << std::endl;
        std::cout << "Sub Msg: " << (bad_request1.sub_msg ? *bad_request1.sub_msg : "null") << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test case 2: Partial JSON object
    std::cout << "\n2. Testing partial JSON object:" << std::endl;
    std::string json_str2 = R"({
        "code": 404,
        "msg": "Not Found",
        "request_id": "req_789012"
    })";
    
    try {
        auto json_obj2 = json::parse(json_str2);
        error_response::BadRequest bad_request2 = json_obj2.get<error_response::BadRequest>();
        
        std::cout << "Code: " << (bad_request2.code ? std::to_string(*bad_request2.code) : "null") << std::endl;
        std::cout << "Details: " << (bad_request2.details ? *bad_request2.details : "null") << std::endl;
        std::cout << "Msg: " << (bad_request2.msg ? *bad_request2.msg : "null") << std::endl;
        std::cout << "Request ID: " << (bad_request2.request_id ? *bad_request2.request_id : "null") << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test case 3: Empty JSON object
    std::cout << "\n3. Testing empty JSON object:" << std::endl;
    std::string json_str3 = "{}";
    
    try {
        auto json_obj3 = json::parse(json_str3);
        error_response::BadRequest bad_request3 = json_obj3.get<error_response::BadRequest>();
        
        std::cout << "All fields should be null:" << std::endl;
        std::cout << "Has code: " << (bad_request3.code.has_value() ? "yes" : "no") << std::endl;
        std::cout << "Has details: " << (bad_request3.details.has_value() ? "yes" : "no") << std::endl;
        std::cout << "Has msg: " << (bad_request3.msg.has_value() ? "yes" : "no") << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test case 4: Serialize back to JSON
    std::cout << "\n4. Testing serialization back to JSON:" << std::endl;
    try {
        error_response::BadRequest bad_request4;
        bad_request4.code = 500;
        bad_request4.msg = "Internal Server Error";
        bad_request4.request_id = "req_999999";
        
        json j = bad_request4;
        std::string serialized = j.dump(2);  // Pretty print with 2-space indentation
        std::cout << "Serialized JSON:" << std::endl;
        std::cout << serialized << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test case 5: JSON with null values
    std::cout << "\n5. Testing JSON with null values:" << std::endl;
    std::string json_str5 = R"({
        "code": null,
        "msg": "Error occurred",
        "details": null,
        "request_id": "req_555555"
    })";
    
    try {
        auto json_obj5 = json::parse(json_str5);
        error_response::BadRequest bad_request5 = json_obj5.get<error_response::BadRequest>();
        
        std::cout << "Code: " << (bad_request5.code.has_value() ? "has value" : "null") << std::endl;
        std::cout << "Details: " << (bad_request5.details.has_value() ? "has value" : "null") << std::endl;
        std::cout << "Msg: " << (bad_request5.msg ? *bad_request5.msg : "null") << std::endl;
        std::cout << "Request ID: " << (bad_request5.request_id ? *bad_request5.request_id : "null") << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }

    // Test case 6: Testing invalid JSON
    std::cout << "\n6. Testing invalid JSON:" << std::endl;
    std::string json_str6 = R"({
        "code": "invalid_string",  // Should be a number
        "msg": "Error"
    })";
    
    try {
        auto json_obj6 = json::parse(json_str6);
        error_response::BadRequest bad_request6 = json_obj6.get<error_response::BadRequest>();
        std::cout << "Unexpected success - should have thrown an exception" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Expected error: " << e.what() << std::endl;
    }
}

int main() {
    test_bad_request();
    return 0;
}