#include "RepairCenter.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <filesystem>

namespace {
std::string trimStr(const std::string& str) {
    size_t start = 0;
    while (start < str.size() && (str[start] == ' ' || str[start] == '\t' || str[start] == '\r' || str[start] == '\n')) start++;
    size_t end = str.size();
    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || str[end - 1] == '\r' || str[end - 1] == '\n')) end--;
    return str.substr(start, end - start);
}

std::string askString(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int askInt(const std::string& prompt) {
    while (true) {
        std::string s = trimStr(askString(prompt));
        try {
            size_t idx = 0;
            int val = std::stoi(s, &idx);
            if (idx == s.size() && val >= 0) {
                return val;
            }
        } catch (...) {}
        std::cout << " [!] Error: Please enter a valid non-negative integer.\n";
    }
}

double askDouble(const std::string& prompt) {
    while (true) {
        std::string s = trimStr(askString(prompt));
        try {
            size_t idx = 0;
            double val = std::stod(s, &idx);
            if (idx == s.size() && val >= 0.0) {
                return val;
            }
        } catch (...) {}
        std::cout << " [!] Error: Please enter a valid non-negative amount.\n";
    }
}

std::string getField(const std::vector<std::string>& row, size_t index) {
    return (index < row.size()) ? row[index] : "";
}
}

RepairCenter::RepairCenter(const std::string& dataDirectory)
    : dataDir(dataDirectory) {
    customers = new Customer[customerCap];
    devices = new Device[deviceCap];
    jobs = new RepairJob[jobCap];
    technicians = new Technician[technicianCap];
    load();
}

RepairCenter::~RepairCenter() {
    save();
    delete[] customers;
    delete[] devices;
    delete[] jobs;
    delete[] technicians;
    customers = nullptr;
    devices = nullptr;
    jobs = nullptr;
    technicians = nullptr;
}

bool RepairCenter::validPhone(const std::string& phone) {
    int digits = 0;
    for (unsigned char c : phone) {
        if (std::isdigit(c)) digits++;
    }
    return (digits >= 10 && digits <= 15);
}

std::string RepairCenter::clean(const std::string& input) {
    std::string out = input;
    for (char& c : out) {
        if (c == '|' || c == '\n' || c == '\r') {
            c = ' ';
        }
    }
    // Trim spaces
    size_t start = 0;
    while (start < out.size() && out[start] == ' ') start++;
    size_t end = out.size();
    while (end > start && out[end - 1] == ' ') end--;
    return out.substr(start, end - start);
}

void RepairCenter::growCustomers() {
    int newCap = customerCap * 2;
    Customer* newArr = new Customer[newCap];
    for (int i = 0; i < customerCount; i++) {
        newArr[i] = customers[i];
    }
    delete[] customers;
    customers = newArr;
    customerCap = newCap;
}

void RepairCenter::growDevices() {
    int newCap = deviceCap * 2;
    Device* newArr = new Device[newCap];
    for (int i = 0; i < deviceCount; i++) {
        newArr[i] = devices[i];
    }
    delete[] devices;
    devices = newArr;
    deviceCap = newCap;
}

void RepairCenter::growJobs() {
    int newCap = jobCap * 2;
    RepairJob* newArr = new RepairJob[newCap];
    for (int i = 0; i < jobCount; i++) {
        newArr[i] = jobs[i];
    }
    delete[] jobs;
    jobs = newArr;
    jobCap = newCap;
}

void RepairCenter::growTechnicians() {
    int newCap = technicianCap * 2;
    Technician* newArr = new Technician[newCap];
    for (int i = 0; i < technicianCount; i++) {
        newArr[i] = technicians[i];
    }
    delete[] technicians;
    technicians = newArr;
    technicianCap = newCap;
}

Customer* RepairCenter::findCustomer(int id) const {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i].getId() == id) return &customers[i];
    }
    return nullptr;
}

Device* RepairCenter::findDevice(int id) const {
    for (int i = 0; i < deviceCount; i++) {
        if (devices[i].getId() == id) return &devices[i];
    }
    return nullptr;
}

Technician* RepairCenter::findTechnician(int id) const {
    for (int i = 0; i < technicianCount; i++) {
        if (technicians[i].getId() == id) return &technicians[i];
    }
    return nullptr;
}

RepairJob* RepairCenter::findJob(int id) const {
    for (int i = 0; i < jobCount; i++) {
        if (jobs[i].getId() == id) return &jobs[i];
    }
    return nullptr;
}

void RepairCenter::load() {
    try {
        std::filesystem::create_directories(dataDir);
    } catch (...) {}

    // Load Customers
    auto customerRows = FileManager::readRows(dataDir + "/customers.txt");
    for (const auto& row : customerRows) {
        try {
            if (row.size() >= 3) {
                if (customerCount == customerCap) growCustomers();
                customers[customerCount++] = Customer(std::stoi(getField(row, 0)),
                                                      getField(row, 1),
                                                      getField(row, 2));
            }
        } catch (...) {}
    }

    // Load Devices
    auto deviceRows = FileManager::readRows(dataDir + "/devices.txt");
    for (const auto& row : deviceRows) {
        try {
            if (row.size() >= 6) {
                if (deviceCount == deviceCap) growDevices();
                devices[deviceCount++] = Device(std::stoi(getField(row, 0)),
                                                std::stoi(getField(row, 1)),
                                                getField(row, 2),
                                                getField(row, 3),
                                                getField(row, 4),
                                                getField(row, 5));
            }
        } catch (...) {}
    }

    // Load Technicians
    auto techRows = FileManager::readRows(dataDir + "/technicians.txt");
    for (const auto& row : techRows) {
        try {
            if (row.size() >= 4) {
                if (technicianCount == technicianCap) growTechnicians();
                technicians[technicianCount++] = Technician(std::stoi(getField(row, 0)),
                                                            getField(row, 1),
                                                            getField(row, 2),
                                                            getField(row, 3));
            }
        } catch (...) {}
    }

    // Load Repair Jobs
    auto jobRows = FileManager::readRows(dataDir + "/jobs.txt");
    for (const auto& row : jobRows) {
        try {
            if (row.size() >= 6) {
                if (jobCount == jobCap) growJobs();
                jobs[jobCount++] = RepairJob(std::stoi(getField(row, 0)),
                                             std::stoi(getField(row, 1)),
                                             std::stoi(getField(row, 2)),
                                             getField(row, 3),
                                             getField(row, 4),
                                             std::stod(getField(row, 5)));
            }
        } catch (...) {}
    }
}

void RepairCenter::save() const {
    try {
        std::filesystem::create_directories(dataDir);

        std::vector<std::string> cRows, dRows, tRows, jRows;

        for (int i = 0; i < customerCount; i++) {
            cRows.push_back(std::to_string(customers[i].getId()) + "|" +
                            clean(customers[i].getName()) + "|" +
                            clean(customers[i].getPhone()));
        }

        for (int i = 0; i < deviceCount; i++) {
            dRows.push_back(std::to_string(devices[i].getId()) + "|" +
                            std::to_string(devices[i].getCustomerId()) + "|" +
                            clean(devices[i].getType()) + "|" +
                            clean(devices[i].getBrand()) + "|" +
                            clean(devices[i].getModel()) + "|" +
                            clean(devices[i].getIssue()));
        }

        for (int i = 0; i < technicianCount; i++) {
            tRows.push_back(std::to_string(technicians[i].getId()) + "|" +
                            clean(technicians[i].getName()) + "|" +
                            clean(technicians[i].getPhone()) + "|" +
                            clean(technicians[i].getSpecialization()));
        }

        for (int i = 0; i < jobCount; i++) {
            jRows.push_back(std::to_string(jobs[i].getId()) + "|" +
                            std::to_string(jobs[i].getDeviceId()) + "|" +
                            std::to_string(jobs[i].getTechnicianId()) + "|" +
                            clean(jobs[i].getStatus()) + "|" +
                            clean(jobs[i].getDiagnosis()) + "|" +
                            std::to_string(jobs[i].getCost()));
        }

        FileManager::writeRows(dataDir + "/customers.txt", cRows);
        FileManager::writeRows(dataDir + "/devices.txt", dRows);
        FileManager::writeRows(dataDir + "/technicians.txt", tRows);
        FileManager::writeRows(dataDir + "/jobs.txt", jRows);
    } catch (const std::exception& e) {
        std::cerr << " [!] Warning saving data: " << e.what() << "\n";
    }
}

void RepairCenter::menuAddRecord() {
    std::cout << "\n--- ADD RECORD MENU ---\n";
    std::cout << "1. Add Customer\n";
    std::cout << "2. Add Device\n";
    std::cout << "3. Add Technician\n";
    std::cout << "4. Return to Main Menu\n";
    int choice = askInt("Select option (1-4): ");
    switch (choice) {
        case 1: addCustomer(); break;
        case 2: addDevice(); break;
        case 3: addTechnician(); break;
        case 4: return;
        default: std::cout << " [!] Invalid option.\n"; break;
    }
}

void RepairCenter::addCustomer() {
    std::cout << "\n=== ADD CUSTOMER ===\n";
    int id = askInt("Enter Customer ID: ");
    if (findCustomer(id)) {
        std::cout << " [!] Error: Customer ID " << id << " already exists!\n";
        return;
    }

    std::string name = clean(askString("Enter Customer Name: "));
    std::string phone = clean(askString("Enter Phone Number (10-15 digits): "));

    if (name.empty()) {
        std::cout << " [!] Error: Name cannot be empty.\n";
        return;
    }
    if (!validPhone(phone)) {
        std::cout << " [!] Error: Invalid phone number format. Must contain 10 to 15 digits.\n";
        return;
    }

    if (customerCount == customerCap) growCustomers();
    customers[customerCount++] = Customer(id, name, phone);
    save();
    std::cout << " [✓] Customer added and saved successfully.\n";
}

void RepairCenter::addDevice() {
    std::cout << "\n=== ADD DEVICE ===\n";
    if (customerCount == 0) {
        std::cout << " [!] Please add at least one customer first.\n";
        return;
    }

    int id = askInt("Enter Device ID: ");
    if (findDevice(id)) {
        std::cout << " [!] Error: Device ID " << id << " already exists!\n";
        return;
    }

    int cid = askInt("Enter Owner Customer ID: ");
    if (!findCustomer(cid)) {
        std::cout << " [!] Error: Customer ID " << cid << " not found!\n";
        return;
    }

    std::string type = clean(askString("Enter Device Type (e.g., Smartphone, Laptop, Tablet): "));
    std::string brand = clean(askString("Enter Brand (e.g., Apple, Samsung, Dell): "));
    std::string model = clean(askString("Enter Model (e.g., iPhone 13, Inspiron 15): "));
    std::string issue = clean(askString("Enter Reported Issue: "));

    if (type.empty() || brand.empty() || issue.empty()) {
        std::cout << " [!] Error: Type, Brand, and Reported Issue cannot be blank.\n";
        return;
    }

    if (deviceCount == deviceCap) growDevices();
    devices[deviceCount++] = Device(id, cid, type, brand, model, issue);
    save();
    std::cout << " [✓] Device added and saved successfully.\n";
}

void RepairCenter::addTechnician() {
    std::cout << "\n=== ADD TECHNICIAN ===\n";
    int id = askInt("Enter Technician ID: ");
    if (findTechnician(id)) {
        std::cout << " [!] Error: Technician ID " << id << " already exists!\n";
        return;
    }

    std::string name = clean(askString("Enter Technician Name: "));
    std::string phone = clean(askString("Enter Phone Number (10-15 digits): "));
    std::string spec = clean(askString("Enter Specialization (e.g., Hardware, Screen, Motherboard): "));

    if (name.empty() || spec.empty() || !validPhone(phone)) {
        std::cout << " [!] Error: Invalid technician data provided.\n";
        return;
    }

    if (technicianCount == technicianCap) growTechnicians();
    technicians[technicianCount++] = Technician(id, name, phone, spec);
    save();
    std::cout << " [✓] Technician added and saved successfully.\n";
}

void RepairCenter::displayAll() const {
    std::cout << "\n=======================================================\n";
    std::cout << "               DEVICE REPAIR CENTER RECORDS            \n";
    std::cout << "=======================================================\n";

    std::cout << "\n--- CUSTOMERS (" << customerCount << ") ---\n";
    if (customerCount == 0) {
        std::cout << "  No customer records found.\n";
    } else {
        std::cout << std::left << std::setw(8) << "ID"
                  << std::setw(22) << "Name"
                  << std::setw(16) << "Phone"
                  << "Role\n";
        std::cout << "-------------------------------------------------------\n";
        for (int i = 0; i < customerCount; i++) {
            std::cout << std::left << std::setw(8) << customers[i].getId()
                      << std::setw(22) << customers[i].getName()
                      << std::setw(16) << customers[i].getPhone()
                      << customers[i].role() << "\n";
        }
    }

    std::cout << "\n--- DEVICES (" << deviceCount << ") ---\n";
    if (deviceCount == 0) {
        std::cout << "  No device records found.\n";
    } else {
        std::cout << std::left << std::setw(8) << "ID"
                  << std::setw(12) << "Owner ID"
                  << std::setw(14) << "Type"
                  << std::setw(20) << "Model"
                  << "Reported Issue\n";
        std::cout << "-------------------------------------------------------\n";
        for (int i = 0; i < deviceCount; i++) {
            std::string fullModel = devices[i].getBrand() + " " + devices[i].getModel();
            std::cout << std::left << std::setw(8) << devices[i].getId()
                      << std::setw(12) << devices[i].getCustomerId()
                      << std::setw(14) << devices[i].getType()
                      << std::setw(20) << fullModel
                      << devices[i].getIssue() << "\n";
        }
    }

    std::cout << "\n--- TECHNICIANS (" << technicianCount << ") [Polymorphism Demo] ---\n";
    if (technicianCount == 0) {
        std::cout << "  No technician records found.\n";
    } else {
        // Demonstrating runtime polymorphism via base pointer Customer*
        for (int i = 0; i < technicianCount; i++) {
            const Customer* basePtr = &technicians[i];
            basePtr->displayDetails();
        }
    }

    std::cout << "\n--- REPAIR JOBS (" << jobCount << ") ---\n";
    if (jobCount == 0) {
        std::cout << "  No repair jobs found.\n";
    } else {
        std::cout << std::left << std::setw(8) << "Job ID"
                  << std::setw(10) << "Dev ID"
                  << std::setw(10) << "Tech ID"
                  << std::setw(14) << "Status"
                  << std::setw(12) << "Cost (Rs)"
                  << "Diagnosis\n";
        std::cout << "----------------------------------------------------------------------\n";
        for (int i = 0; i < jobCount; i++) {
            std::cout << std::left << std::setw(8) << jobs[i].getId()
                      << std::setw(10) << jobs[i].getDeviceId()
                      << std::setw(10) << jobs[i].getTechnicianId()
                      << std::setw(14) << jobs[i].getStatus()
                      << std::setw(12) << std::fixed << std::setprecision(2) << jobs[i].getCost()
                      << jobs[i].getDiagnosis() << "\n";
        }
    }
    std::cout << "=======================================================\n";
}

void RepairCenter::search() const {
    std::cout << "\n=== SEARCH RECORD ===\n";
    int id = askInt("Enter Record ID to search: ");
    bool found = false;

    Customer* c = findCustomer(id);
    if (c) {
        std::cout << " [✓] Found in Customers:\n  ";
        c->displayDetails();
        found = true;
    }

    Device* d = findDevice(id);
    if (d) {
        std::cout << " [✓] Found in Devices:\n  ";
        d->displayDetails();
        found = true;
    }

    Technician* t = findTechnician(id);
    if (t) {
        std::cout << " [✓] Found in Technicians:\n  ";
        t->displayDetails();
        found = true;
    }

    RepairJob* j = findJob(id);
    if (j) {
        std::cout << " [✓] Found in Repair Jobs:\n  ";
        j->displayDetails();
        found = true;
    }

    if (!found) {
        std::cout << " [!] No record found with ID " << id << ".\n";
    }
}

void RepairCenter::updateJob() {
    std::cout << "\n=== UPDATE REPAIR JOB ===\n";
    int id = askInt("Enter Repair Job ID to update: ");
    RepairJob* j = findJob(id);
    if (!j) {
        std::cout << " [!] Error: Repair Job ID " << id << " not found.\n";
        return;
    }

    std::cout << "Current Job Details: ";
    j->displayDetails();

    std::cout << "Select New Status:\n";
    std::cout << " 1. Pending\n";
    std::cout << " 2. In Progress\n";
    std::cout << " 3. Completed\n";
    int stChoice = askInt("Choice (1-3): ");
    std::string newStatus;
    if (stChoice == 1) newStatus = "Pending";
    else if (stChoice == 2) newStatus = "In Progress";
    else if (stChoice == 3) newStatus = "Completed";
    else {
        std::cout << " [!] Invalid status choice.\n";
        return;
    }

    std::string diag = clean(askString("Enter Updated Diagnosis / Repair Notes: "));
    double cost = askDouble("Enter Final / Updated Repair Cost (Rs.): ");

    j->setStatus(newStatus);
    if (!diag.empty()) j->setDiagnosis(diag);
    j->setCost(cost);

    save();
    std::cout << " [✓] Repair Job " << id << " successfully updated and saved.\n";
}

void RepairCenter::deleteJob() {
    std::cout << "\n=== DELETE REPAIR JOB ===\n";
    int id = askInt("Enter Repair Job ID to delete: ");
    int index = -1;
    for (int i = 0; i < jobCount; i++) {
        if (jobs[i].getId() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        std::cout << " [!] Error: Repair Job ID " << id << " not found.\n";
        return;
    }

    for (int i = index; i < jobCount - 1; i++) {
        jobs[i] = jobs[i + 1];
    }
    jobCount--;
    save();
    std::cout << " [✓] Repair Job " << id << " removed successfully.\n";
}

void RepairCenter::processRepair() {
    std::cout << "\n=======================================================\n";
    std::cout << "       MAIN TRANSACTION: CREATE & PROCESS REPAIR JOB   \n";
    std::cout << "=======================================================\n";

    if (deviceCount == 0) {
        std::cout << " [!] Transaction aborted: Please register at least one device first.\n";
        return;
    }
    if (technicianCount == 0) {
        std::cout << " [!] Transaction aborted: Please register at least one technician first.\n";
        return;
    }

    int jobId = askInt("Enter New Repair Job ID: ");
    if (findJob(jobId)) {
        std::cout << " [!] Error: Job ID " << jobId << " already exists!\n";
        return;
    }

    int devId = askInt("Enter Device ID for repair: ");
    Device* dev = findDevice(devId);
    if (!dev) {
        std::cout << " [!] Error: Device ID " << devId << " does not exist!\n";
        return;
    }

    int techId = askInt("Enter Assignee Technician ID: ");
    Technician* tech = findTechnician(techId);
    if (!tech) {
        std::cout << " [!] Error: Technician ID " << techId << " does not exist!\n";
        return;
    }

    std::cout << "\nAssigning Device: [" << dev->getBrand() << " " << dev->getModel()
              << "] to Technician: [" << tech->getName() << " (" << tech->getSpecialization() << ")]\n";

    std::string diag = clean(askString("Enter Initial Diagnosis / Inspection Notes: "));
    if (diag.empty()) diag = "Device intake and diagnostic testing started";

    if (jobCount == jobCap) growJobs();
    jobs[jobCount++] = RepairJob(jobId, devId, techId, "In Progress", diag, 0.0);
    save();

    std::cout << " [✓] SUCCESS: Main Transaction Complete!\n";
    std::cout << "     Repair Job #" << jobId << " created and assigned successfully.\n";
}

void RepairCenter::report() const {
    std::cout << "\n=======================================================\n";
    std::cout << "          DEVICE REPAIR CENTER - SUMMARY REPORT         \n";
    std::cout << "=======================================================\n";

    int pending = 0;
    int inProgress = 0;
    int completed = 0;
    double totalRevenue = 0.0;

    for (int i = 0; i < jobCount; i++) {
        if (jobs[i].getStatus() == "Pending") pending++;
        else if (jobs[i].getStatus() == "In Progress") inProgress++;
        else if (jobs[i].getStatus() == "Completed") {
            completed++;
            totalRevenue += jobs[i].getCost();
        }
    }

    std::cout << " Total Registered Customers : " << customerCount << "\n";
    std::cout << " Total Registered Devices   : " << deviceCount << "\n";
    std::cout << " Total Active Technicians   : " << technicianCount << "\n";
    std::cout << " Total Repair Jobs Tracked  : " << jobCount << "\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << " Jobs Pending Inspection    : " << pending << "\n";
    std::cout << " Jobs In Progress           : " << inProgress << "\n";
    std::cout << " Jobs Completed             : " << completed << "\n";
    std::cout << "-------------------------------------------------------\n";
    std::cout << " Total Revenue Realized     : Rs." << std::fixed << std::setprecision(2) << totalRevenue << "\n";
    if (completed > 0) {
        std::cout << " Average Ticket Value       : Rs." << std::fixed << std::setprecision(2) << (totalRevenue / completed) << "\n";
    }
    std::cout << "=======================================================\n";
}

void RepairCenter::menuSaveLoad() {
    std::cout << "\n--- FILE PERSISTENCE MENU ---\n";
    std::cout << "1. Save Current In-Memory Records to Disk\n";
    std::cout << "2. Reload All Records from Data Files\n";
    std::cout << "3. Cancel\n";
    int choice = askInt("Choose option (1-3): ");
    if (choice == 1) {
        save();
        std::cout << " [✓] All records successfully saved to " << dataDir << "/*.txt files.\n";
    } else if (choice == 2) {
        customerCount = deviceCount = jobCount = technicianCount = 0;
        load();
        std::cout << " [✓] Records successfully reloaded from disk.\n";
    }
}

void RepairCenter::run() {
    std::cout << "\n=======================================================\n";
    std::cout << "           WELCOME TO DEVICE REPAIR CENTER             \n";
    std::cout << "    Enrollment: IU2541230468 | Project Code: CPP33     \n";
    std::cout << "=======================================================\n";

    while (true) {
        std::cout << "\n------------------ SYSTEM MAIN MENU -------------------\n";
        std::cout << " 1. Add Record (Customer / Device / Technician)\n";
        std::cout << " 2. Display Records\n";
        std::cout << " 3. Search Record\n";
        std::cout << " 4. Update Record (Repair Job)\n";
        std::cout << " 5. Delete Record (Repair Job)\n";
        std::cout << " 6. Main Transaction / Process (Create Repair Job)\n";
        std::cout << " 7. Generate Summary Report\n";
        std::cout << " 8. Save / Load Data Files\n";
        std::cout << " 9. Exit System\n";
        std::cout << "-------------------------------------------------------\n";

        int choice = askInt("Enter your choice (1-9): ");
        switch (choice) {
            case 1: menuAddRecord(); break;
            case 2: displayAll(); break;
            case 3: search(); break;
            case 4: updateJob(); break;
            case 5: deleteJob(); break;
            case 6: processRepair(); break;
            case 7: report(); break;
            case 8: menuSaveLoad(); break;
            case 9:
                save();
                std::cout << "\n [✓] All records safely preserved. Goodbye!\n";
                return;
            default:
                std::cout << " [!] Please select an option between 1 and 9.\n";
                break;
        }
    }
}
