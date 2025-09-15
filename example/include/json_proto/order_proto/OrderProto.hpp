//  To parse this JSON data, first install
//
//      json.hpp  https://github.com/nlohmann/json
//
//  Then include this file, and then do
//
//     OrderProto data = nlohmann::json::parse(jsonString);

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

namespace order_proto {
    using nlohmann::json;

    #ifndef NLOHMANN_UNTYPED_order_proto_HELPER
    #define NLOHMANN_UNTYPED_order_proto_HELPER
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

    #ifndef NLOHMANN_OPTIONAL_order_proto_HELPER
    #define NLOHMANN_OPTIONAL_order_proto_HELPER
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

    struct ShippingAddress {
        std::optional<std::string> city;
        std::optional<std::string> country;
        std::optional<std::string> state;
        std::optional<std::string> street;
        std::optional<std::string> zip_code;
    };

    struct Customer {
        std::optional<std::string> customer_id;
        std::optional<std::string> first_name;
        std::optional<std::string> last_name;
        std::optional<ShippingAddress> shipping_address;
    };

    struct Item {
        std::optional<std::string> category;
        std::optional<std::string> name;
        std::optional<int64_t> quantity;
        std::optional<std::string> sku;
        std::optional<double> unit_price;
    };

    struct Pricing {
        std::optional<double> discount;
        std::optional<double> shipping_cost;
        std::optional<double> subtotal;
        std::optional<double> tax;
        std::optional<double> total;
    };

    struct OrderProto {
        std::optional<std::string> created_at;
        std::optional<Customer> customer;
        std::optional<std::string> fulfillment_status;
        std::optional<std::vector<Item>> items;
        std::optional<std::string> order_id;
        std::optional<std::string> payment_status;
        std::optional<Pricing> pricing;
        std::optional<std::string> updated_at;
    };
}

namespace order_proto {
    void from_json(const json & j, ShippingAddress & x);
    void to_json(json & j, const ShippingAddress & x);

    void from_json(const json & j, Customer & x);
    void to_json(json & j, const Customer & x);

    void from_json(const json & j, Item & x);
    void to_json(json & j, const Item & x);

    void from_json(const json & j, Pricing & x);
    void to_json(json & j, const Pricing & x);

    void from_json(const json & j, OrderProto & x);
    void to_json(json & j, const OrderProto & x);

    inline void from_json(const json & j, ShippingAddress& x) {
        x.city = get_stack_optional<std::string>(j, "city");
        x.country = get_stack_optional<std::string>(j, "country");
        x.state = get_stack_optional<std::string>(j, "state");
        x.street = get_stack_optional<std::string>(j, "street");
        x.zip_code = get_stack_optional<std::string>(j, "zipCode");
    }

    inline void to_json(json & j, const ShippingAddress & x) {
        j = json::object();
        j["city"] = x.city;
        j["country"] = x.country;
        j["state"] = x.state;
        j["street"] = x.street;
        j["zipCode"] = x.zip_code;
    }

    inline void from_json(const json & j, Customer& x) {
        x.customer_id = get_stack_optional<std::string>(j, "customerId");
        x.first_name = get_stack_optional<std::string>(j, "firstName");
        x.last_name = get_stack_optional<std::string>(j, "lastName");
        x.shipping_address = get_stack_optional<ShippingAddress>(j, "shippingAddress");
    }

    inline void to_json(json & j, const Customer & x) {
        j = json::object();
        j["customerId"] = x.customer_id;
        j["firstName"] = x.first_name;
        j["lastName"] = x.last_name;
        j["shippingAddress"] = x.shipping_address;
    }

    inline void from_json(const json & j, Item& x) {
        x.category = get_stack_optional<std::string>(j, "category");
        x.name = get_stack_optional<std::string>(j, "name");
        x.quantity = get_stack_optional<int64_t>(j, "quantity");
        x.sku = get_stack_optional<std::string>(j, "sku");
        x.unit_price = get_stack_optional<double>(j, "unitPrice");
    }

    inline void to_json(json & j, const Item & x) {
        j = json::object();
        j["category"] = x.category;
        j["name"] = x.name;
        j["quantity"] = x.quantity;
        j["sku"] = x.sku;
        j["unitPrice"] = x.unit_price;
    }

    inline void from_json(const json & j, Pricing& x) {
        x.discount = get_stack_optional<double>(j, "discount");
        x.shipping_cost = get_stack_optional<double>(j, "shippingCost");
        x.subtotal = get_stack_optional<double>(j, "subtotal");
        x.tax = get_stack_optional<double>(j, "tax");
        x.total = get_stack_optional<double>(j, "total");
    }

    inline void to_json(json & j, const Pricing & x) {
        j = json::object();
        j["discount"] = x.discount;
        j["shippingCost"] = x.shipping_cost;
        j["subtotal"] = x.subtotal;
        j["tax"] = x.tax;
        j["total"] = x.total;
    }

    inline void from_json(const json & j, OrderProto& x) {
        x.created_at = get_stack_optional<std::string>(j, "createdAt");
        x.customer = get_stack_optional<Customer>(j, "customer");
        x.fulfillment_status = get_stack_optional<std::string>(j, "fulfillmentStatus");
        x.items = get_stack_optional<std::vector<Item>>(j, "items");
        x.order_id = get_stack_optional<std::string>(j, "orderId");
        x.payment_status = get_stack_optional<std::string>(j, "paymentStatus");
        x.pricing = get_stack_optional<Pricing>(j, "pricing");
        x.updated_at = get_stack_optional<std::string>(j, "updatedAt");
    }

    inline void to_json(json & j, const OrderProto & x) {
        j = json::object();
        j["createdAt"] = x.created_at;
        j["customer"] = x.customer;
        j["fulfillmentStatus"] = x.fulfillment_status;
        j["items"] = x.items;
        j["orderId"] = x.order_id;
        j["paymentStatus"] = x.payment_status;
        j["pricing"] = x.pricing;
        j["updatedAt"] = x.updated_at;
    }
}
