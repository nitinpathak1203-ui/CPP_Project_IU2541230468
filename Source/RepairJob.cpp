#include "RepairJob.h"
#include <iostream>
#include <iomanip>

RepairJob::RepairJob()
    : id(0), deviceId(0), technicianId(0), status("Pending"), diagnosis("N/A"), cost(0.0) {}

RepairJob::RepairJob(int id, int deviceId, int technicianId, const std::string& status, const std::string& diagnosis, double cost)
    : id(id), deviceId(deviceId), technicianId(technicianId), status(status), diagnosis(diagnosis), cost(cost) {}

int RepairJob::getId() const {
    return id;
}

int RepairJob::getDeviceId() const {
    return deviceId;
}

int RepairJob::getTechnicianId() const {
    return technicianId;
}

std::string RepairJob::getStatus() const {
    return status;
}

std::string RepairJob::getDiagnosis() const {
    return diagnosis;
}

double RepairJob::getCost() const {
    return cost;
}

void RepairJob::setStatus(const std::string& value) {
    status = value;
}

void RepairJob::setDiagnosis(const std::string& value) {
    diagnosis = value;
}

void RepairJob::setCost(double value) {
    cost = value;
}

void RepairJob::displayDetails() const {
    std::cout << "[Repair Job] ID: " << id
              << " | Device ID: " << deviceId
              << " | Technician ID: " << technicianId
              << " | Status: " << status
              << " | Diagnosis: " << diagnosis
              << " | Cost: Rs." << std::fixed << std::setprecision(2) << cost << "\n";
}
