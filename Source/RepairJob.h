#ifndef REPAIRJOB_H
#define REPAIRJOB_H

#include <string>

class RepairJob {
private:
    int id{0};
    int deviceId{0};
    int technicianId{0};
    std::string status;     // "Pending", "In Progress", "Completed"
    std::string diagnosis;
    double cost{0.0};

public:
    RepairJob();
    RepairJob(int id, int deviceId, int technicianId, const std::string& status, const std::string& diagnosis, double cost);
    ~RepairJob() = default;

    int getId() const;
    int getDeviceId() const;
    int getTechnicianId() const;
    std::string getStatus() const;
    std::string getDiagnosis() const;
    double getCost() const;

    void setStatus(const std::string& value);
    void setDiagnosis(const std::string& value);
    void setCost(double value);
    void displayDetails() const;
};

#endif // REPAIRJOB_H
