#include "Customer.h"
#include <iostream>

Customer::Customer() : id(0), name(""), phone("") {}

Customer::Customer(int id, const std::string& name, const std::string& phone)
    : id(id), name(name), phone(phone) {}

Customer::~Customer() {}

int Customer::getId() const {
    return id;
}

std::string Customer::getName() const {
    return name;
}

std::string Customer::getPhone() const {
    return phone;
}

void Customer::setName(const std::string& value) {
    name = value;
}

void Customer::setPhone(const std::string& value) {
    phone = value;
}

std::string Customer::role() const {
    return "Customer";
}

void Customer::displayDetails() const {
    std::cout << "[Customer] ID: " << id
              << " | Name: " << name
              << " | Phone: " << phone
              << " | Role: " << role() << "\n";
}
