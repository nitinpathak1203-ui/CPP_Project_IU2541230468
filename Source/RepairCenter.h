#ifndef REPAIRCENTER_H
#define REPAIRCENTER_H

#include "Customer.h"
#include "Device.h"
#include "RepairJob.h"
#include "Technician.h"
#include <string>

class RepairCenter {
private:
    // Dynamic memory pointers for entity collections
    Customer* customers{nullptr};
    Device* devices{nullptr};
    RepairJob* jobs{nullptr};
    Technician* technicians{nullptr};

    // Tracking counts and capacities for dynamic resizing
    int customerCount{0};
    int deviceCount{0};
    int jobCount{0};
    int technicianCount{0};

    int customerCap{10};
    int deviceCap{10};
    int jobCap{10};
    int technicianCap{10};

    std::string dataDir;

    // Dynamic array growth helpers
    void growCustomers();
    void growDevices();
    void growJobs();
    void growTechnicians();

    // Validation & string cleaning helpers
    static bool validPhone(const std::string& phone);
    static std::string clean(const std::string& input);

public:
    explicit RepairCenter(const std::string& dataDirectory = "Data");
    ~RepairCenter();

    // Prevent inadvertent shallow copying of dynamic arrays
    RepairCenter(const RepairCenter&) = delete;
    RepairCenter& operator=(const RepairCenter&) = delete;

    // File Persistence
    void load();
    void save() const;

    // Minimum Menu Operations
    void menuAddRecord();
    void addCustomer();
    void addDevice();
    void addTechnician();
    void displayAll() const;
    void search() const;
    void updateJob();
    void deleteJob();
    void processRepair();   // Main Transaction / Process
    void report() const;    // Summary Report
    void menuSaveLoad();

    // Entity lookup helpers
    Customer* findCustomer(int id) const;
    Device* findDevice(int id) const;
    Technician* findTechnician(int id) const;
    RepairJob* findJob(int id) const;

    // Main execution loop
    void run();
};

#endif // REPAIRCENTER_H
