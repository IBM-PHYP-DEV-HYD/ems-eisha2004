#include "XyzMenu.H"
#include <iostream>
#include <limits>
using namespace std;

int XyzMenu::getValidatedIntInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && ((value >= min && value <= max) || value == -1))
            return value;
        cout << "Invalid input! Enter between " << min << " and " << max << " (or -1 to exit).\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string XyzMenu::getValidatedStringInput(const string& prompt) {
    string value;
    cout << prompt;
    cin >> ws;
    getline(cin, value);
    return value;
}


void XyzMenu::displayMainMenu() {
    int choice;
    do {
        cout << "\n------------------------------------------------------------\n";
        cout << "|                        MAIN MENU                         |\n";
        cout << "------------------------------------------------------------\n";
        cout << "| 1. Add an Employee                                       |\n";
        cout << "| 2. Remove an Employee                                    |\n";
        cout << "| 3. Employee Details                                      |\n";
        cout << "| 4. Others                                                |\n";
        cout << "| -1. Exit                                                 |\n";
        cout << "------------------------------------------------------------\n";

        choice = getValidatedIntInput("Enter your choice (-1 to exit): ", 1, 4);
        cout << "\n";

        switch (choice) {
            case 1: displayAddEmployeeMenu(); break;
            case 2: removeEmployee(); break;
            case 3: displayEmployeeDetailsMenu(); break;
            case 4: displayOthersMenu(); break;
            case -1: cout << "Exiting system... Goodbye!\n"; break;
        }

    } while (choice != -1);
}


void XyzMenu::displayAddEmployeeMenu() {
    cout << "\n------------------------------------------------------------\n";
    cout << "|              SUB-MENU 1: ADD AN EMPLOYEE                 |\n";
    cout << "------------------------------------------------------------\n";
    cout << "| 1. Add an Employee at Random                             |\n";
    cout << "| 2. Add an Employee (F/C/I)                               |\n";
    cout << "| -1. Back to Main Menu                                    |\n";
    cout << "------------------------------------------------------------\n";

    int choice = getValidatedIntInput("Enter your choice: ", 1, 2);
    if (choice == -1) return;

    switch (choice) {
        case 1: addRandomEmployees(); break;
        case 2: addEmployeeByType(); break;
    }
}


void XyzMenu::displayEmployeeDetailsMenu() {
    cout << "\n------------------------------------------------------------\n";
    cout << "|            SUB-MENU 2: EMPLOYEE DETAILS                  |\n";
    cout << "------------------------------------------------------------\n";
    cout << "| 1. All Employees Summary                                 |\n";
    cout << "| 2. Employee Summary (F/C/I)                              |\n";
    cout << "| 3. Employee Summary (M/F)                                |\n";
    cout << "| 4. Employee Summary (A/I/R)                              |\n";
    cout << "| 5. Display Employee Details by ID                        |\n";
    cout << "| -1. Back to Main Menu                                    |\n";
    cout << "------------------------------------------------------------\n";

    int choice = getValidatedIntInput("Enter your choice: ", 1, 5);
    if (choice == -1) return;

    switch (choice) {
        case 1: mManager.printAllCurrent(); break;
        case 2: {
            string type = getValidatedStringInput("Enter Type (F/C/I): ");
            mManager.printSummaryByType(type);
            break;
        }
        case 3: {
            string gender = getValidatedStringInput("Enter Gender (M/F): ");
            mManager.printSummaryByGender(gender);
            break;
        }
        case 4: {
            string status = getValidatedStringInput("Enter Status (A/I/R): ");
            mManager.printSummaryByStatus(status);
            break;
        }
        case 5: {
            string id = getValidatedStringInput("Enter Employee ID: ");
            XyzEmpBase* e = mManager.findById(id);
            if (e) e->printDetails();
            else cout << "No employee found with ID: " << id << "\n";
            break;
        }
    }
}

void XyzMenu::displayOthersMenu() {
    cout << "\n------------------------------------------------------------\n";
    cout << "|                   SUB-MENU 3: OTHERS                     |\n";
    cout << "------------------------------------------------------------\n";
    cout << "| 1. Add 'n' number of leaves to all Full-Time employees   |\n";
    cout << "| 2. Convert an Intern to Full-Time employee               |\n";
    cout << "| 3. Search an Employee by ID                              |\n";
    cout << "| 4. Search an Employee by Name                            |\n";
    cout << "| -1. Back to Main Menu                                    |\n";
    cout << "------------------------------------------------------------\n";

    int choice = getValidatedIntInput("Enter your choice: ", 1, 4);
    if (choice == -1) return;

    switch (choice) {
        case 1: addLeaves(); break;
        case 2: convertInternToFullTime(); break;
        case 3: searchById(); break;
        case 4: searchByName(); break;
    }
}

void XyzMenu::addRandomEmployees() {
    int n = getValidatedIntInput("Enter number of random employees to add: ", 1, 20);
    srand(time(0));
    for (int i = 0; i < n; ++i) {
        int type = rand() % 3;
        if (type == 0)
            mManager.addFullTime(new XyzFullTimeEmployee());
        else if (type == 1)
            mManager.addContractor(new XyzContractorEmployee());
        else
            mManager.addIntern(new XyzInternEmployee());
    }
    cout << n << " random employees added successfully!\n";
}

void XyzMenu::addEmployeeByType() {
    string type = getValidatedStringInput("Enter Employee Type (F/C/I): ");
    if (type == "F" || type == "f")
        mManager.addFullTime(new XyzFullTimeEmployee());
    else if (type == "C" || type == "c")
        mManager.addContractor(new XyzContractorEmployee());
    else if (type == "I" || type == "i")
        mManager.addIntern(new XyzInternEmployee());
    else {
        cout << "Invalid type entered.\n";
        return;
    }
    cout << "Employee added successfully!\n";
}

void XyzMenu::removeEmployee() {
    if (mManager.isCurrentEmpty()) {
        cout << "\nNo employees to remove.\n";
        return;
    }

    string id = getValidatedStringInput("Enter Employee ID to remove: ");
    if (mManager.removeEmployeeById(id))
        cout << "Employee removed successfully!\n";
    else
        cout << "Employee not found.\n";
}

void XyzMenu::addLeaves() {
    int n = getValidatedIntInput("Enter number of leaves to add: ", 1, 22);
    mManager.addLeavesToAllFullTime(n);
    cout << "Leaves added successfully to all full-time employees.\n";
}

void XyzMenu::convertInternToFullTime() {
    string id = getValidatedStringInput("Enter Intern ID to convert: ");
    mManager.convertInternToFullTime(id);
}

void XyzMenu::searchById() {
    string id = getValidatedStringInput("Enter Employee ID: ");
    XyzEmpBase* e = mManager.findById(id);
    if (e)
        e->printDetails();
    else
        cout << "No employee found with ID: " << id << "\n";
}

void XyzMenu::searchByName() {
    string name = getValidatedStringInput("Enter name or part of name: ");
    mManager.findByName(name);
}
