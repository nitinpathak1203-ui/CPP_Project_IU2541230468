#include "Technician.h"
#include <iostream>

Technician::Technician() : Customer(), specialization("") {}

Technician::Technician(int id, const std::string& name, const std::string& phone, const std::string& specialization)
    : Customer(id, name, phone), specialization(specialization) {}

std::string Technician::getSpecialization() const {
    return specialization;
}

void Technician::setSpecialization(const std::string& value) {
    specialization = value;
}

std::string Technician::role() const {
    return "Technician";
}

void Technician::displayDetails() const {
    std::cout << "[Technician] ID: " << id
              << " | Name: " << name
              << " | Phone: " << phone
              << " | Role: " << role()
              << " | Specialization: " << specialization << "\n";
}
