//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     BadRequest data = nlohmann::json::parse(jsonString);

#pragma once

#include <optional>
#include "json.hpp"

#ifndef NLOHMANN_OPT_HELPER
#define NLOHMANN_OPT_HELPER
namespace nlohmann {
    template <typename T>
    struct adl_serializer<std::shared_ptr<T>> {
        static void to_json(json & j, const std::shared_ptr<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::shared_ptr<T> from_json(const json & j) {
            if (j.is_null()) return std::make_shared<T>(); else return std::make_shared<T>(j.get<T>());
        }
    };
    template <typename T>
    struct adl_serializer<std::optional<T>> {
        static void to_json(json & j, const std::optional<T> & opt) {
            if (!opt) j = nullptr; else j = *opt;
        }

        static std::optional<T> from_json(const json & j) {
            if (j.is_null()) return std::make_optional<T>(); else return std::make_optional<T>(j.get<T>());
        }
    };
}
#endif

namespace error_response {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_error_response_HELPER
    #define NLOHMANN_UNTYPED_error_response_HELPER
    inline json get_untyped(const json & j, const char * property) {
        if (j.find(property) != j.end()) {
            return j.at(property).get<json>();
        }
        return json();
    }

    inline json get_untyped(const json & j, std::string property) {
        return get_untyped(j, property.data());
    }
    #endif

    #ifndef NLOHMANN_OPTIONAL_error_response_HELPER
    #define NLOHMANN_OPTIONAL_error_response_HELPER
    template <typename T>
    inline std::shared_ptr<T> get_heap_optional(const json & j, const char * property) {
        auto it = j.find(property);
        if (it != j.end() && !it->is_null()) {
            return j.at(property).get<std::shared_ptr<T>>();
        }
        return std::shared_ptr<T>();
    }

    template <typename T>
    inline std::shared_ptr<T> get_heap_optional(const json & j, std::string property) {
        return get_heap_optional<T>(j, property.data());
    }
    template <typename T>
    inline std::optional<T> get_stack_optional(const json & j, const char * property) {
        auto it = j.find(property);
        if (it != j.end() && !it->is_null()) {
            return j.at(property).get<std::optional<T>>();
        }
        return std::optional<T>();
    }

    template <typename T>
    inline std::optional<T> get_stack_optional(const json & j, std::string property) {
        return get_stack_optional<T>(j, property.data());
    }
    #endif

    struct BadRequest {
        std::optional<int64_t> code;
        std::optional<std::string> details;
        std::optional<std::string> msg;
        std::optional<std::string> request_id;
        std::optional<std::string> sub_code;
        std::optional<std::string> sub_msg;
    };
}

namespace error_response {
    void from_json(const json & j, BadRequest & x);
    void to_json(json & j, const BadRequest & x);

    inline void from_json(const json & j, BadRequest& x) {
        x.code = get_stack_optional<int64_t>(j, "code");
        x.details = get_stack_optional<std::string>(j, "details");
        x.msg = get_stack_optional<std::string>(j, "msg");
        x.request_id = get_stack_optional<std::string>(j, "request_id");
        x.sub_code = get_stack_optional<std::string>(j, "sub_code");
        x.sub_msg = get_stack_optional<std::string>(j, "sub_msg");
    }

    inline void to_json(json & j, const BadRequest & x) {
        j = json::object();
        j["code"] = x.code;
        j["details"] = x.details;
        j["msg"] = x.msg;
        j["request_id"] = x.request_id;
        j["sub_code"] = x.sub_code;
        j["sub_msg"] = x.sub_msg;
    }
}
