//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     UserProfile data = nlohmann::json::parse(jsonString);

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

namespace user_profile {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_user_profile_HELPER
    #define NLOHMANN_UNTYPED_user_profile_HELPER
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

    #ifndef NLOHMANN_OPTIONAL_user_profile_HELPER
    #define NLOHMANN_OPTIONAL_user_profile_HELPER
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

    struct UserProfile {
        std::optional<std::string> date_of_birth;
        std::optional<std::string> email;
        std::optional<int64_t> id;
        std::optional<bool> is_active;
        std::optional<std::string> username;
    };
}

namespace user_profile {
    void from_json(const json & j, UserProfile & x);
    void to_json(json & j, const UserProfile & x);

    inline void from_json(const json & j, UserProfile& x) {
        x.date_of_birth = get_stack_optional<std::string>(j, "date_of_birth");
        x.email = get_stack_optional<std::string>(j, "email");
        x.id = get_stack_optional<int64_t>(j, "id");
        x.is_active = get_stack_optional<bool>(j, "is_active");
        x.username = get_stack_optional<std::string>(j, "username");
    }

    inline void to_json(json & j, const UserProfile & x) {
        j = json::object();
        j["date_of_birth"] = x.date_of_birth;
        j["email"] = x.email;
        j["id"] = x.id;
        j["is_active"] = x.is_active;
        j["username"] = x.username;
    }
}
