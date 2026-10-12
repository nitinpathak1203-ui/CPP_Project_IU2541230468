#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
protected:
    int id{0};
    std::string name;
    std::string phone;

public:
    // Default and parameterized constructors
    Customer();
    Customer(int id, const std::string& name, const std::string& phone);
    virtual ~Customer();

    // Getters and Setters (Encapsulation)
    int getId() const;
    std::string getName() const;
    std::string getPhone() const;

    void setName(const std::string& value);
    void setPhone(const std::string& value);

    // Virtual functions for runtime polymorphism
    virtual std::string role() const;
    virtual void displayDetails() const;
};

#endif // CUSTOMER_H
