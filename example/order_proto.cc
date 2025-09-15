#include <iostream>
#include "json_proto/order_proto/OrderProto.hpp"

// Print all fields of ShippingAddress
void print_shipping_address(const order_proto::ShippingAddress& address) {
    if (address.street) std::cout << "  Street: " << *address.street << std::endl;
    if (address.city) std::cout << "  City: " << *address.city << std::endl;
    if (address.state) std::cout << "  State: " << *address.state << std::endl;
    if (address.zip_code) std::cout << "  Zip Code: " << *address.zip_code << std::endl;
    if (address.country) std::cout << "  Country: " << *address.country << std::endl;
}

// Print all fields of Customer
void print_customer(const order_proto::Customer& customer) {
    if (customer.customer_id) std::cout << "Customer ID: " << *customer.customer_id << std::endl;
    if (customer.first_name) std::cout << "First Name: " << *customer.first_name << std::endl;
    if (customer.last_name) std::cout << "Last Name: " << *customer.last_name << std::endl;
    if (customer.shipping_address) {
        std::cout << "Shipping Address:" << std::endl;
        print_shipping_address(*customer.shipping_address);
    }
}

// Print all fields of Item
void print_item(const order_proto::Item& item) {
    if (item.sku) std::cout << "  SKU: " << *item.sku << std::endl;
    if (item.name) std::cout << "  Name: " << *item.name << std::endl;
    if (item.category) std::cout << "  Category: " << *item.category << std::endl;
    if (item.quantity) std::cout << "  Quantity: " << *item.quantity << std::endl;
    if (item.unit_price) std::cout << "  Unit Price: $" << *item.unit_price << std::endl;
    std::cout << "  ---" << std::endl;
}

// Print all fields of Pricing
void print_pricing(const order_proto::Pricing& pricing) {
    if (pricing.subtotal) std::cout << "  Subtotal: $" << *pricing.subtotal << std::endl;
    if (pricing.discount) std::cout << "  Discount: $" << *pricing.discount << std::endl;
    if (pricing.tax) std::cout << "  Tax: $" << *pricing.tax << std::endl;
    if (pricing.shipping_cost) std::cout << "  Shipping Cost: $" << *pricing.shipping_cost << std::endl;
    if (pricing.total) std::cout << "  Total: $" << *pricing.total << std::endl;
}

// Print all fields of the entire OrderProto
void print_order(const order_proto::OrderProto& order) {
    std::cout << "=== Order Details ===" << std::endl;
    
    if (order.order_id) std::cout << "Order ID: " << *order.order_id << std::endl;
    if (order.created_at) std::cout << "Created At: " << *order.created_at << std::endl;
    if (order.updated_at) std::cout << "Updated At: " << *order.updated_at << std::endl;
    if (order.payment_status) std::cout << "Payment Status: " << *order.payment_status << std::endl;
    if (order.fulfillment_status) std::cout << "Fulfillment Status: " << *order.fulfillment_status << std::endl;
    
    if (order.customer) {
        std::cout << "\nCustomer Information:" << std::endl;
        print_customer(*order.customer);
    }
    
    if (order.items && !order.items->empty()) {
        std::cout << "\nItems (" << order.items->size() << " items):" << std::endl;
        for (const auto& item : *order.items) {
            print_item(item);
        }
    }
    
    if (order.pricing) {
        std::cout << "\nPricing Information:" << std::endl;
        print_pricing(*order.pricing);
    }
    
    std::cout << "====================" << std::endl;
}

// Example 1: Parse complete order JSON
void parse_complete_order() {
    std::string json_str = R"({
        "orderId": "ORD12345",
        "createdAt": "2023-10-15T10:30:00Z",
        "customer": {
            "customerId": "CUST001",
            "firstName": "John",
            "lastName": "Doe",
            "shippingAddress": {
                "street": "123 Main St",
                "city": "New York",
                "state": "NY",
                "zipCode": "10001",
                "country": "USA"
            }
        },
        "items": [
            {
                "sku": "SKU001",
                "name": "Laptop",
                "category": "Electronics",
                "quantity": 1,
                "unitPrice": 999.99
            },
            {
                "sku": "SKU002",
                "name": "Mouse",
                "category": "Electronics",
                "quantity": 2,
                "unitPrice": 25.50
            }
        ],
        "pricing": {
            "subtotal": 1050.99,
            "discount": 50.99,
            "tax": 100.00,
            "shippingCost": 15.00,
            "total": 1115.00
        },
        "paymentStatus": "PAID",
        "fulfillmentStatus": "SHIPPED",
        "updatedAt": "2023-10-16T14:20:00Z"
    })";

    try {
        auto json_obj = nlohmann::json::parse(json_str);
        order_proto::OrderProto order = json_obj.get<order_proto::OrderProto>();
        print_order(order);
    } catch (const std::exception& e) {
        std::cout << "Parse error: " << e.what() << std::endl;
    }
}

// Example 2: Parse order with partial fields
void parse_partial_order() {
    std::string json_str = R"({
        "orderId": "ORD67890",
        "createdAt": "2023-10-17T09:15:00Z",
        "paymentStatus": "PENDING",
        "customer": {
            "firstName": "Alice",
            "lastName": "Smith"
        }
    })";

    try {
        auto json_obj = nlohmann::json::parse(json_str);
        order_proto::OrderProto order = json_obj.get<order_proto::OrderProto>();
        print_order(order);
    } catch (const std::exception& e) {
        std::cout << "Parse error: " << e.what() << std::endl;
    }
}

// Example 3: Parse empty object
void parse_empty_order() {
    std::string json_str = "{}";

    try {
        auto json_obj = nlohmann::json::parse(json_str);
        order_proto::OrderProto order = json_obj.get<order_proto::OrderProto>();
        print_order(order);
    } catch (const std::exception& e) {
        std::cout << "Parse error: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "=== OrderProto JSON Parsing Examples ===" << std::endl;
    
    std::cout << "\n1. Complete order:" << std::endl;
    parse_complete_order();
    
    std::cout << "\n2. Partial order:" << std::endl;
    parse_partial_order();
    
    std::cout << "\n3. Empty order:" << std::endl;
    parse_empty_order();
    
    return 0;
}