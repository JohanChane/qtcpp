cmake_minimum_required(VERSION 3.16)
project(qtcpp_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(nlohmann_json 3.12.0 REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/example/include
)

add_executable(example_basic_usage
    example/basic_usage.cc
    example/include/json_proto/user_profile/UserProfile.hpp
)

target_link_libraries(example_basic_usage
    PRIVATE nlohmann_json::nlohmann_json
)

add_executable(example_array_usage
    example/array_usage.cc
    example/include/json_proto/error_response/ApiError.hpp
)

target_link_libraries(example_basic_usage
    PRIVATE nlohmann_json::nlohmann_json
)

add_executable(example_bad_request
    example/bad_request.cc
    example/include/json_proto/error_response/BadRequest.hpp
)

target_link_libraries(example_bad_request
    PRIVATE nlohmann_json::nlohmann_json
)

add_executable(example_order_proto
    example/order_proto.cc
    example/include/json_proto/order_proto/OrderProto.hpp
)

target_link_libraries(example_order_proto
    PRIVATE nlohmann_json::nlohmann_json
)