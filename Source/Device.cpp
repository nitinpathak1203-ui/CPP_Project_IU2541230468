#include "Device.h"
#include <iostream>

Device::Device() : id(0), customerId(0), type(""), brand(""), model(""), issue("") {}

Device::Device(int id, int customerId, const std::string& type, const std::string& brand, const std::string& model, const std::string& issue)
    : id(id), customerId(customerId), type(type), brand(brand), model(model), issue(issue) {}

int Device::getId() const {
    return id;
}

int Device::getCustomerId() const {
    return customerId;
}

std::string Device::getType() const {
    return type;
}

std::string Device::getBrand() const {
    return brand;
}

std::string Device::getModel() const {
    return model;
}

std::string Device::getIssue() const {
    return issue;
}

void Device::setIssue(const std::string& value) {
    issue = value;
}

void Device::displayDetails() const {
    std::cout << "[Device] ID: " << id
              << " | Customer ID: " << customerId
              << " | Type: " << type
              << " | Brand & Model: " << brand << " " << model
              << " | Reported Issue: " << issue << "\n";
}
