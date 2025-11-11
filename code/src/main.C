#include "XyzEmployeeManager.H"
#include "XyzFullTimeEmployee.H"
#include "XyzContractorEmployee.H"
#include "XyzInternEmployee.H"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

static void printLineBox() {
    cout << "------------------------------------------" << endl;
}

static int safeReadIntPrompt(const string &prompt, bool mustBePositive=false) {
    int val;
    while (true) {
        if (!prompt.empty()) cout << prompt;
        if (cin >> val) {
            if (mustBePositive && val <= 0) {
                cout << "Please enter a positive integer.\n";
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        }
        cout << "Invalid input, Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static string safeReadToken(const string &prompt) {
    string s;
    cout << prompt;
    cin >> s;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return s;
}

static void printMainMenu() {
    printLineBox();
    cout << "|               MAIN MENU                |" << endl;
    printLineBox();
    cout << "| 1. Add an Employee                     |" << endl;
    cout << "| 2. Remove an Employee                  |" << endl;
    cout << "| 3. Employee Details                    |" << endl;
    cout << "| 4. Others                              |" << endl;
    cout << "| -1. Exit                               |" << endl;
    printLineBox();
    cout << "Enter choice: ";
}

static void printAddMenu() {
    printLineBox();
    cout << "|               ADD MENU                 |" << endl;
    printLineBox();
    cout << "| 1. Add Random                          |" << endl;
    cout << "| 2. Add Full-Time Employee              |" << endl;
    cout << "| 3. Add Contractor                      |" << endl;
    cout << "| 4. Add Intern                          |" << endl;
    printLineBox();
    cout << "Enter choice: ";
}

static void printDetailsMenu() {
    printLineBox();
    cout << "|             DETAILS MENU               |" << endl;
    printLineBox();
    cout << "| 1. All Employees Summary               |" << endl;
    cout << "| 2. Resigned Employees Summary          |" << endl;
    cout << "| 3. Search by ID                        |" << endl;
    cout << "| 4. Search by Name                      |" << endl;
    printLineBox();
    cout << "Enter choice: ";
}

static void printOthersMenu() {
    printLineBox();
    cout << "|              OTHERS MENU               |" << endl;
    printLineBox();
    cout << "| 1. Add 'n' leaves to all Full-Time     |" << endl;
    cout << "| 2. Convert Intern/Contractor to FT     |" << endl;
    cout << "| 3. Search by ID                        |" << endl;
    cout << "| 4. Search by Name                      |" << endl;
    printLineBox();
    cout << "Enter choice: ";
}

int main() {
    XyzEmployeeManager mgr;

    while (true) {
        printMainMenu();
        int mainChoice;
        if (!(cin >> mainChoice)) {
            cout << "Invalid input, Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (mainChoice == -1) {
            cout << "Exiting Employee Management System\n";
            break;
        }

        switch (mainChoice) {
            case 1: {
                printAddMenu();
                int addChoice = safeReadIntPrompt("", true);
                switch (addChoice) {
                    case 1: {
                        int n = safeReadIntPrompt("Enter number of random employees to add: ", true);
                        if (n > 1000) { cout << "Please choose <= 1000.\n"; break; }
                        mgr.addNEmployeesRandom(n);
                        cout << "Added " << n << " random employee(s).\n";
                        mgr.printSummaryCounts();
                        break;
                    }
                    case 2: {
                        // manual full-time quick
                        string name = safeReadToken("Enter Name (single token): ");
                        // let builder generate ID uniqueness for random, for manual we'll ask id or auto-generate simple one
                        string id = safeReadToken("Enter ID (or type auto): ");
                        if (id == "auto") id = "XYZ0000F";
                        XyzFullTimeEmployee* e = new XyzFullTimeEmployee(name, id, EmpStatus::ACTIVE, Gender::MALE, "1995-01-01", "2023-01-01", 0);
                        mgr.addFullTime(e);
                        cout << "Manual Full-Time employee added.\n";
                        mgr.printSummaryCounts();
                        break;
                    }
                    case 3: {
                        string name = safeReadToken("Enter Name (single token): ");
                        string id = safeReadToken("Enter ID (or type auto): ");
                        if (id == "auto") id = "XYZ0000C";
                        XyzContractorEmployee* e = new XyzContractorEmployee(name, id, EmpStatus::ACTIVE, Gender::FEMALE, "1994-01-01", "2024-01-01", "2025-01-01", Agency::Avengers);
                        mgr.addContractor(e);
                        cout << "Manual Contractor added.\n";
                        mgr.printSummaryCounts();
                        break;
                    }
                    case 4: {
                        string name = safeReadToken("Enter Name (single token): ");
                        string id = safeReadToken("Enter ID (or type auto): ");
                        if (id == "auto") id = "XYZ0000I";
                        XyzInternEmployee* e = new XyzInternEmployee(name, id, EmpStatus::ACTIVE, Gender::OTHER, "2000-01-01", "2024-03-01", "2024-09-01", College::IITDelhi, Branch::CSE);
                        mgr.addIntern(e);
                        cout << "Manual Intern added.\n";
                        mgr.printSummaryCounts();
                        break;
                    }
                    default:
                        cout << "Invalid choice in Add Menu.\n";
                }
                break;
            }

            case 2: {
                printLineBox(); cout << "|           REMOVE AN EMPLOYEE           |\n"; printLineBox();
                if (mgr.isCurrentEmpty()) {
                    cout << "| No employees available to remove.      |\n";
                    printLineBox();
                    break;
                }
                string id;
                cout << "Enter Employee ID to remove: ";
                cin >> id;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (mgr.removeEmployeeById(id)) {
                    cout << "Employee removed and moved to resigned deque.\n";
                } else {
                    cout << "Employee not found.\n";
                }
                mgr.printSummaryCounts();
                break;
            }

            case 3: {
                printDetailsMenu();
                int dchoice = safeReadIntPrompt("", true);
                switch (dchoice) {
                    case 1:
                        if (mgr.isCurrentEmpty()) cout << "No current employees to display.\n";
                        else mgr.printAllCurrent();
                        break;
                    case 2:
                        if (mgr.isResignedEmpty()) cout << "No resigned employees to display.\n";
                        else mgr.printAllResigned();
                        break;
                    case 3: {
                        string id = safeReadToken("Enter Employee ID: ");
                        XyzEmpBase* e = mgr.findById(id);
                        if (e) e->printDetails();
                        else cout << "Employee not found.\n";
                        break;
                    }
                    case 4: {
                        string namePart = safeReadToken("Enter name or substring: ");
                        mgr.findByName(namePart);
                        break;
                    }
                    default:
                        cout << "Invalid choice in Details Menu.\n";
                }
                break;
            }

            case 4: {
                printOthersMenu();
                int och = safeReadIntPrompt("", true);
                switch (och) {
                    case 1: {
                        int n = safeReadIntPrompt("Enter n leaves to ADD to all Full-Time employees: ");
                        if (n == 0) { cout << "No change.\n"; break; }
                        mgr.addLeavesToAllFullTime(n);
                        cout << "Added " << n << " leaves (max restricted to 22).\n";
                        break;
                    }
                    case 2: {
                        string id = safeReadToken("Enter Employee ID to convert to Full-Time: ");
                        if (mgr.convertToFullTime(id)) cout << "Converted to Full-Time.\n"; else cout << "Conversion failed (not found or already FT).\n";
                        break;
                    }
                    case 3: {
                        string id = safeReadToken("Search by ID: ");
                        XyzEmpBase* e = mgr.findById(id);
                        if (e) e->printDetails(); else cout << "Not found.\n";
                        break;
                    }
                    case 4: {
                        string namePart = safeReadToken("Search by Name (part): ");
                        mgr.findByName(namePart);
                        break;
                    }
                    default:
                        cout << "Invalid option in Others Menu\n";
                }
                break;
            }

            default:
                cout << "Invalid main menu choice\n";
        }
    }

    return 0;
}
