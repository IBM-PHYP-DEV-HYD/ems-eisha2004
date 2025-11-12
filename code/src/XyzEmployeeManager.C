#include "XyzEmployeeManager.H"
#include <iostream>
#include <iomanip>
using namespace std;

static void printHeaderBox() {
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "| " << left << setw(22) << "Employee Name"
         << " | " << setw(10) << "ID"
         << " | " << setw(10) << "Type"
         << " | " << setw(12) << "Status"
         << " | " << setw(9)  << "Gender"
         << " | " << setw(13) << "DOB"
         << " | " << setw(15) << "DOJ"
         << " | " << setw(11) << "Leaves"
         << " | " << setw(14) << "Agency"
         << " | " << setw(7)  << "Branch"
         << " | " << setw(11)  << "College"
         << " |\n";
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void XyzEmployeeManager::addFullTime(XyzFullTimeEmployee* e) { mCurrentEmployees.pushBack(e); }
void XyzEmployeeManager::addContractor(XyzContractorEmployee* e) { mCurrentEmployees.pushBack(e); }
void XyzEmployeeManager::addIntern(XyzInternEmployee* e) { mCurrentEmployees.pushBack(e); }

bool XyzEmployeeManager::removeEmployeeById(const string& id) {
    int index = 0;
    auto it = mCurrentEmployees.getIterator();
    while (it.hasNext()) {
        if (it.value()->getId() == id) {
            XyzEmpBase* emp = it.value();
            emp->setStatus(EmpStatus::RESIGNED);
            emp->setDol("2025-11-12"); 
            mResignedEmployees.pushBack(emp);
            mCurrentEmployees.removeAt(index);
            cout << "Employee " << id << " marked as resigned.\n";
            return true;
        }
        it.next();
        ++index;
    }
    cout << "Employee ID " << id << " not found.\n";
    return false;
}

bool XyzEmployeeManager::isCurrentEmpty() const { return mCurrentEmployees.empty(); }
bool XyzEmployeeManager::isResignedEmpty() const { return mResignedEmployees.empty(); }

void XyzEmployeeManager::printAllCurrent() const {
    if (mCurrentEmployees.empty()) { cout << "No current employees.\n"; return; }
    printHeaderBox();
    auto it = mCurrentEmployees.getIterator();
    while (it.hasNext()) {
        it.value()->printSummary();
        it.next();
    }
    cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
}

void XyzEmployeeManager::printAllResigned() const {
    if (mResignedEmployees.empty()) { cout << "No resigned employees.\n"; return; }
    printHeaderBox();
    auto it = mResignedEmployees.getIterator();
    while (it.hasNext()) {
        it.value()->printSummary();
        it.next();
    }
}

XyzEmpBase* XyzEmployeeManager::findById(const string& id) {
    auto it = mCurrentEmployees.getIterator();
    while (it.hasNext()) {
        if (it.value()->getId() == id)
            return it.value();
        it.next();
    }
    return nullptr;
}

void XyzEmployeeManager::findByName(const string& namePart) {
    bool found = false;
    auto it = mCurrentEmployees.getIterator();
    while (it.hasNext()) {
        if (it.value()->getName().find(namePart) != string::npos) {
            if (!found) printHeaderBox();
            it.value()->printDetails();
            found = true;
        }
        it.next();
    }
    if (!found)
        cout << "No employees found with name containing '" << namePart << "'.\n";
}

void XyzEmployeeManager::addLeavesToAllFullTime(int n) {
    auto it = mCurrentEmployees.getIterator();
    bool any = false;
    while (it.hasNext()) {
        if (it.value()->getType() == EmpType::FullTime) {
            auto ft = static_cast<XyzFullTimeEmployee*>(it.value());
            ft->addLeaves(n);
            any = true;
        }
        it.next();
    }
    if (any) cout << "Leaves added successfully to all full-time employees.\n";
    else cout << "No full-time employees found.\n";
}

void XyzEmployeeManager::convertInternToFullTime(const string& id) {
    int index = 0;
    auto it = mCurrentEmployees.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* base = it.value();
        if (base->getId() == id && base->getType() == EmpType::Intern) {
            auto intern = static_cast<XyzInternEmployee*>(base);
            auto ft = new XyzFullTimeEmployee(
                intern->getName(),
                intern->getId(),
                intern->getStatus(),
                intern->getGender(),
                intern->getDob(),
                intern->getDoj(),
                0);
            mCurrentEmployees.removeAt(index);
            mCurrentEmployees.insertAt(index, ft);
            cout << "Intern converted to Full-Time successfully!\n";
            delete intern;
            return;
        }
        it.next();
        ++index;
    }
    cout << "No intern found with ID " << id << ".\n";
}

void XyzEmployeeManager::printSummaryByType(const string& type) const {
    bool found = false;
    auto it = mCurrentEmployees.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        if ((type == "F" || type == "f") && e->getType() == EmpType::FullTime ||
            (type == "C" || type == "c") && e->getType() == EmpType::Contractor ||
            (type == "I" || type == "i") && e->getType() == EmpType::Intern) {
            if (!found) printHeaderBox();
            e->printSummary();
            found = true;
        }
        it.next();
    }
    if (!found) cout << "No employees of type " << type << " found.\n";
}

void XyzEmployeeManager::printSummaryByGender(const string& gender) const {
    bool found = false;
    auto it = mCurrentEmployees.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        if ((gender == "M" || gender == "m") && e->getGender() == Gender::MALE ||
            (gender == "F" || gender == "f") && e->getGender() == Gender::FEMALE ||
            (gender == "O" || gender == "o") && e->getGender() == Gender::OTHER) {
            if (!found) printHeaderBox();
            e->printSummary();
            found = true;
        }
        it.next();
    }
    if (!found) cout << "No employees found with gender " << gender << ".\n";
}

void XyzEmployeeManager::printSummaryByStatus(const string& status) const {
    bool found = false;
    auto it = mCurrentEmployees.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        if ((status == "A" || status == "a") && e->getStatus() == EmpStatus::ACTIVE ||
            (status == "I" || status == "i") && e->getStatus() == EmpStatus::INACTIVE ||
            (status == "R" || status == "r") && e->getStatus() == EmpStatus::RESIGNED) {
            if (!found) printHeaderBox();
            e->printSummary();
            found = true;
        }
        it.next();
    }
    if (!found) cout << "No employees found with status " << status << ".\n";
}

void XyzEmployeeManager::printSummaryCounts() const {
    int ft = 0, ct = 0, in = 0;
    auto it = mCurrentEmployees.getIterator();
    while (it.hasNext()) {
        auto e = it.value();
        if (e->getType() == EmpType::FullTime) ft++;
        else if (e->getType() == EmpType::Contractor) ct++;
        else if (e->getType() == EmpType::Intern) in++;
        it.next();
    }
    cout << "\nSummary: FullTime=" << ft << " | Contractor=" << ct << " | Intern=" << in << "\n";
}
