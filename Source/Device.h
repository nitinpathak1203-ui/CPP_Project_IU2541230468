#ifndef DEVICE_H
#define DEVICE_H

#include <string>

class Device {
private:
    int id{0};
    int customerId{0};
    std::string type;
    std::string brand;
    std::string model;
    std::string issue;

public:
    Device();
    Device(int id, int customerId, const std::string& type, const std::string& brand, const std::string& model, const std::string& issue);
    ~Device() = default;

    int getId() const;
    int getCustomerId() const;
    std::string getType() const;
    std::string getBrand() const;
    std::string getModel() const;
    std::string getIssue() const;

    void setIssue(const std::string& value);
    void displayDetails() const;
};

#endif // DEVICE_H
