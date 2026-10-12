#ifndef TECHNICIAN_H
#define TECHNICIAN_H

#include "Customer.h"
#include <string>

// Inheritance: Technician derives publicly from Customer
class Technician : public Customer {
private:
    std::string specialization;

public:
    Technician();
    Technician(int id, const std::string& name, const std::string& phone, const std::string& specialization);
    ~Technician() override = default;

    std::string getSpecialization() const;
    void setSpecialization(const std::string& value);

    // Overridden virtual functions demonstrating runtime polymorphism
    std::string role() const override;
    void displayDetails() const override;
};

#endif // TECHNICIAN_H
