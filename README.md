# 🛠️ Device Repair Center — C++ Object-Oriented Project

**Enrollment Number:** `IU2541230468`  
**Project Code:** `CPP33`  
**Repository:** [CPP_Project_IU2541230468](https://github.com/nitinpathak1203-ui/CPP_Project_IU2541230468)

---

## 📖 Project Overview
The **Device Repair Center** is an object-oriented software system developed in C++17 to automate repair shop workflows:
- Customer profile registration and verification
- Hardware device intake and issue reporting
- Technician specialization and assignment
- Multi-stage repair status transitions (`Pending` ➔ `In Progress` ➔ `Completed`)
- Dynamic billing and financial revenue analytics
- Pipe-delimited persistent file storage (`Data/*.txt`)

---

## 🏗️ Object-Oriented Architecture (OOP Concepts)
1. **Encapsulation:** Protected/private data members accessed strictly through verified getters and setters.
2. **Inheritance:** `Technician` class publicly derives from `Customer`, reusing identity fields while extending technical specializations.
3. **Runtime Polymorphism:** Overridden virtual functions (`virtual role()` and `virtual displayDetails()`) dispatched dynamically via base class pointers (`const Customer* basePtr`).
4. **Dynamic Memory Allocation:** Collections are dynamically allocated on the heap using `new Entity[capacity]` and freed via `delete[]` in destructors with geometric capacity expansion.
5. **File Persistence:** Automatic load on initialization and auto-save on mutation using `FileManager`.
6. **Exception-Safe Input:** Number and currency parser utilizing `std::stoi` and `std::stod` with `try-catch` blocks.

---

## 📂 Project Structure
```
DeviceRepairCenter/
├── Source/                 # Modular C++ header (.h) and implementation (.cpp) files
│   ├── Customer.h & Customer.cpp
│   ├── Technician.h & Technician.cpp
│   ├── Device.h & Device.cpp
│   ├── RepairJob.h & RepairJob.cpp
│   ├── FileManager.h & FileManager.cpp
│   ├── RepairCenter.h & RepairCenter.cpp
│   └── main.cpp
├── Data/                   # Persistent pipe-delimited data files
│   ├── customers.txt
│   ├── devices.txt
│   ├── technicians.txt
│   └── jobs.txt
├── Diagrams/               # UML Diagrams (.png images & .puml PlantUML sources)
│   ├── UseCase.png & .puml
│   ├── ClassDiagram.png & .puml
│   ├── Sequence1_MainTransaction.png & .puml
│   ├── Sequence2_UpdateJob.png & .puml
│   └── Workflow.png & WORKFLOW.md
├── Screenshots/            # High-resolution console execution captures (1-8)
├── Executable/             # Target folder for compiled binary
├── build.bat               # 1-Click compiler script
├── run.bat                 # 1-Click runner script
├── ProjectReport.pdf       # Formal academic project report
├── README.txt              # Standard text documentation
└── Submission_Checklist.txt# Completed verification checklist
```

---

## ⚙️ Compilation & Execution

### Option A: Using 1-Click Scripts (Windows)
1. Double-click `build.bat` to compile with g++.
2. Double-click `run.bat` to launch the application.

### Option B: Manual Command Line
```bash
g++ -std=c++17 Source/main.cpp Source/Customer.cpp Source/Device.cpp Source/RepairJob.cpp Source/Technician.cpp Source/FileManager.cpp Source/RepairCenter.cpp -o Executable/DeviceRepairCenter.exe
```
Run the executable:
```bash
Executable\DeviceRepairCenter.exe
```

---

## 📋 System Menu (1 to 9)
```text
=======================================================
           WELCOME TO DEVICE REPAIR CENTER             
    Enrollment: IU2541230468 | Project Code: CPP33     
=======================================================
 1. Add Record (Customer / Device / Technician)
 2. Display Records
 3. Search Record
 4. Update Record (Repair Job)
 5. Delete Record (Repair Job)
 6. Main Transaction / Process (Create Repair Job)
 7. Generate Summary Report
 8. Save / Load Data Files
 9. Exit System
=======================================================
```

---

## 🎓 Academic Deliverables
- **Formal Project Report:** `ProjectReport.pdf` (All 13 sections with embedded diagrams and test matrix)
- **Submission Template:** `IU2541230468_CPP33_Submission_Template.docx`, `.pdf`, `.png`
- **Submission ZIP Package:** `IU2541230468_CPP33_Project.zip`
