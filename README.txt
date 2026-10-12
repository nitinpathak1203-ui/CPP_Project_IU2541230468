================================================================================
                    DEVICE REPAIR CENTER — C++ OOP PROJECT
               Enrollment: IU2541230468 | Project Code: CPP33
================================================================================

1. PROJECT OVERVIEW
-------------------
The Device Repair Center application is a modular, menu-driven C++ software
designed to streamline repair shop operations: customer registration, device
intake, technician dispatching, job diagnosis tracking, financial reporting,
and file persistence.

2. REQUIREMENTS & COMPATIBILITY
-------------------------------
- Windows 10 / 11
- C++17 compliant compiler (MinGW-w64 g++, Dev-C++, Code::Blocks, or MSVC)
- Standard C++ Standard Library

3. HOW TO COMPILE
-----------------
Option A (Fast 1-Click Batch):
  Double-click "build.bat" from the project root folder.

Option B (Manual Terminal Command):
  From the project root folder, execute:
  g++ -std=c++17 Source/main.cpp Source/Customer.cpp Source/Device.cpp Source/RepairJob.cpp Source/Technician.cpp Source/FileManager.cpp Source/RepairCenter.cpp -o Executable/DeviceRepairCenter.exe

4. HOW TO RUN
-------------
Option A: Double-click "run.bat"
Option B: Run from command line:
  Executable\DeviceRepairCenter.exe

*IMPORTANT: Always run the executable from the project root directory so that
 relative file paths to Data/*.txt resolve correctly.

5. DIRECTORY STRUCTURE
----------------------
DeviceRepairCenter/
├── Source/                 -> main.cpp and modular .h and .cpp class files
├── Data/                   -> Pipe-delimited persistence files (.txt)
│   ├── customers.txt
│   ├── devices.txt
│   ├── technicians.txt
│   └── jobs.txt
├── Diagrams/               -> UML diagrams (.png images and .puml sources)
│   ├── UseCase.png & .puml
│   ├── ClassDiagram.png & .puml
│   ├── Sequence1_MainTransaction.png & .puml
│   ├── Sequence2_UpdateJob.png & .puml
│   └── Workflow.png & WORKFLOW.md
├── Screenshots/            -> Execution captures showing key operations
│   ├── 01_main_menu.png
│   ├── 02_add_customer.png
│   ├── 03_add_device_technician.png
│   ├── 04_display_records.png
│   ├── 05_search_record.png
│   ├── 06_main_transaction_create_job.png
│   ├── 07_update_and_report.png
│   └── 08_persistence_verification.png
├── Executable/             -> Target folder for compiled binary
├── build.bat               -> One-click compilation script
├── run.bat                 -> One-click execution script
├── ProjectReport.pdf       -> Formal academic report with diagrams & testing
├── Submission_Checklist.txt-> Completed submission verification
└── README.txt              -> This documentation file

6. CORE OOP CONCEPTS IMPLEMENTED
---------------------------------
1. Classes & Objects: Separate Customer, Technician, Device, RepairJob, RepairCenter, FileManager.
2. Encapsulation: Private/protected member variables accessed via public getters/setters.
3. Constructors & Destructor: Parameterized initialization; destructor safely deletes heap arrays.
4. Inheritance: Technician publicly derives from Customer.
5. Runtime Polymorphism: Virtual functions role() and displayDetails() overridden in Technician;
   polymorphic dispatch demonstrated in RepairCenter::displayAll().
6. Dynamic Memory: Manual array allocation using new Entity[capacity] with dynamic capacity
   doubling and cleanup via delete[].
7. File Persistence: Automatic loading on startup, saving after mutations, and persistence across exits.
8. Exception Handling: Safe numeric and string parsing using try-catch blocks.

================================================================================
                       AUTHOR: IU2541230468 (CPP33)
================================================================================
