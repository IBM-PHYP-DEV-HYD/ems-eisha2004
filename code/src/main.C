#include <iostream>
#include "XyzEmployeeManager.H"

void printMainMenu() {
    std::cout << "\nMain Menu:\n1 Add an Employee\n2 Remove an Employee\n3 Employee Details\n4 Others\n-1 Exit\nEnter choice: ";
}

void printAddMenu() {
    std::cout << "\nAdd Menu:\n1 Add Random\n2 Add Full-Time\n3 Add Contractor\n4 Add Intern\nEnter choice: ";
}

void printDetailsMenu() {
    std::cout << "\nDetails Menu:\n1 All Employees Summary\n2 Resigned Employees Summary\n3 Search by ID\n4 Search by Name\nEnter choice: ";
}

void printOthersMenu() {
    std::cout << "\nOthers Menu:\n1 Add n leaves to all Full-Time\n2 Convert Intern/Contractor to Full-Time\n3 Add n random employees (test)\nEnter choice: ";
}

int main() {
    XyzEmployeeManager mgr;
    int choice = 0;
    while (true) {
        printMainMenu();
        std::cin >> choice;
        if (choice == -1) break;
        if (choice == 1) {
            printAddMenu();
            int c; std::cin>>c;
            if (c==1) { mgr.addEmployeeRandom(); std::cout<<"Added random employee.\n"; }
            else if (c==2) { // manual add fulltime (quick sample)
                XyzFullTimeEmployee* e = new XyzFullTimeEmployee("ManualFT", "XYZ9999F", EmpStatus::ACTIVE, Gender::MALE, "1990-01-01", "2020-01-01", 0);
                mgr.addFullTime(e);
                std::cout<<"Added Manual FullTime\n";
            } else if (c==3) {
                XyzContractorEmployee* e = new XyzContractorEmployee("ManualC", "XYZ9998C", EmpStatus::ACTIVE, Gender::FEMALE, "1992-01-01", "2023-01-01", "2024-01-01", Agency::Avengers);
                mgr.addContractor(e);
                std::cout<<"Added Manual Contractor\n";
            } else if (c==4) {
                XyzInternEmployee* e = new XyzInternEmployee("ManualI", "XYZ9997I", EmpStatus::ACTIVE, Gender::MALE, "2000-01-01", "2024-03-01", "2024-09-01", College::IITDelhi, Branch::CSE);
                mgr.addIntern(e);
                std::cout<<"Added Manual Intern\n";
            }
        } else if (choice == 2) {
            std::cout << "Enter Emp ID to remove: ";
            std::string id; std::cin >> id;
            if (mgr.removeEmployeeById(id)) std::cout<<"Removed and moved to resigned.\n";
            else std::cout<<"Employee not found.\n";
        } else if (choice == 3) {
            printDetailsMenu();
            int c; std::cin>>c;
            if (c==1) mgr.printAllCurrent();
            else if (c==2) mgr.printAllResigned();
            else if (c==3) {
                std::cout<<"Enter ID: "; std::string id; std::cin>>id;
                XyzEmpBase* e = mgr.findById(id);
                if (e) e->printDetails(); else std::cout<<"Not found.\n";
            } else if (c==4) {
                std::cout<<"Enter name or substring: "; std::string nm; std::cin>>nm;
                mgr.findByName(nm);
            }
        } else if (choice == 4) {
            printOthersMenu();
            int c; std::cin>>c;
            if (c==1) {
                std::cout<<"Enter n leaves to add: "; int n; std::cin>>n;
                mgr.addLeavesToAllFullTime(n);
                std::cout<<"Added leaves.\n";
            } else if (c==2) {
                std::cout<<"Enter Emp ID to convert to Full-Time: "; std::string id; std::cin>>id;
                if (mgr.convertToFullTime(id)) std::cout<<"Converted.\n"; else std::cout<<"Convert failed (not found or already FT).\n";
            } else if (c==3) {
                std::cout<<"Enter n (default 10): "; int n; std::cin>>n;
                if (n<=0) n = 10;
                mgr.addNEmployeesRandom(n);
                std::cout<<"Added "<<n<<" random employees.\n";
            }
        } else {
            std::cout<<"Invalid choice\n";
        }
        mgr.printSummaryCounts();
    }

    std::cout<<"Exiting. Goodbye.\n";
    return 0;
}
