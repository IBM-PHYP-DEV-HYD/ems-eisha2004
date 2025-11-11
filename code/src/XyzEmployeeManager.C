#include "XyzEmployeeManager.H"
#include "XyzFullTimeEmployee.H"
#include "XyzContractorEmployee.H"
#include "XyzInternEmployee.H"
#include <iostream>
#include <cstring>
#include <iomanip>

XyzEmployeeManager::XyzEmployeeManager() {
    seedRandom();
}

XyzEmployeeManager::~XyzEmployeeManager() {
    auto it = mCurrentDeque.getIterator();
    while (it.hasNext()) {
        delete it.value();
        it.next();
    }
    it = mResignedDeque.getIterator();
    while (it.hasNext()) {
        delete it.value();
        it.next();
    }
}

void XyzEmployeeManager::addEmployeeRandom() {
    XyzEmployeeBuilder b;
    b.randomize();
    XyzEmpBase* e = b.build();
    if (e->getStatus() == EmpStatus::RESIGNED) {
        XyzEmpBase* r = XyzEmployeeBuilder::buildResignedMinimal(e);
        mResignedDeque.pushBack(r);
        delete e;
    } else {
        mCurrentDeque.pushBack(e);
    }
}

void XyzEmployeeManager::addNEmployeesRandom(int n) {
    for (int i=0;i<n;++i) addEmployeeRandom();
}

void XyzEmployeeManager::addFullTime(XyzFullTimeEmployee* e) {
    if (!e) return;
    if (e->getStatus() == EmpStatus::RESIGNED) {
        mResignedDeque.pushBack(XyzEmployeeBuilder::buildResignedMinimal(e));
        delete e;
    } else mCurrentDeque.pushBack(e);
}

void XyzEmployeeManager::addContractor(XyzContractorEmployee* e) {
    if (!e) return;
    if (e->getStatus() == EmpStatus::RESIGNED) {
        mResignedDeque.pushBack(XyzEmployeeBuilder::buildResignedMinimal(e));
        delete e;
    } else mCurrentDeque.pushBack(e);
}

void XyzEmployeeManager::addIntern(XyzInternEmployee* e) {
    if (!e) return;
    if (e->getStatus() == EmpStatus::RESIGNED) {
        mResignedDeque.pushBack(XyzEmployeeBuilder::buildResignedMinimal(e));
        delete e;
    } else mCurrentDeque.pushBack(e);
}

XyzEmpBase* XyzEmployeeManager::findById(const std::string& id) {
    auto it = mCurrentDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        if (e->getId() == id) return e;
        it.next();
    }
    return nullptr;
}

void XyzEmployeeManager::findByName(const std::string& namePart) {
    bool found=false;
    auto it = mCurrentDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        if (e->getName().find(namePart) != std::string::npos) {
            e->printSummary();
            std::cout << "\n";
            found = true;
        }
        it.next();
    }
    if (!found) std::cout << "No matches found in current employees for '"<<namePart<<"'\n";
}

bool XyzEmployeeManager::removeEmployeeById(const std::string& id) {
    int index = 0;
    auto it = mCurrentDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        if (e->getId() == id) {
            XyzEmpBase* r = XyzEmployeeBuilder::buildResignedMinimal(e);
            mResignedDeque.pushBack(r);
            delete e;
            mCurrentDeque.removeAt(index);
            return true;
        }
        it.next();
        ++index;
    }
    return false;
}

bool XyzEmployeeManager::convertToFullTime(const std::string& id) {
    int index = 0;
    auto it = mCurrentDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        if (e->getId() == id) {
            if (e->getType() == EmpType::FullTime) return false;
            std::string oldid = e->getId();
            if (oldid.size()>=1) oldid[oldid.size()-1] = 'F';
            XyzFullTimeEmployee* nf = new XyzFullTimeEmployee(e->getName(), oldid, EmpStatus::ACTIVE, e->getGender(), e->getDob(), e->getDoj(), 0);
            delete e;
            mCurrentDeque.removeAt(index);
            mCurrentDeque.insertAt(index, nf);
            return true;
        }
        it.next();
        ++index;
    }
    return false;
}

void XyzEmployeeManager::addLeavesToAllFullTime(int n) {
    auto it = mCurrentDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        if (e->getType() == EmpType::FullTime) {
            XyzFullTimeEmployee* ft = static_cast<XyzFullTimeEmployee*>(e);
            ft->addLeaves(n);
        }
        it.next();
    }
}

static void printSummaryHeaderBox() {
    std::cout << "--------------------------------------------------------------------------------------------------------\n";
    std::cout << "| ID      | Name            | Type | Status  | G | DOJ      | Extra\n";
    std::cout << "--------------------------------------------------------------------------------------------------------\n";
}

/*void XyzFullTimeEmployee::printEmployeeDetails() {
    cout << "| "<<left<<setw(22)<<mName<<" | "<<left<<setw(10)<<mEmpID<<" | "<<left<<setw(10)<<"Full Time"<<" | "
    <<left<<setw(12)<<((mStatus==XyzEmployeeEnums::Active)?"Active":((mStatus==XyzEmployeeEnums::Inactive)?"Inactive":"Resigned"))<<" | "
    <<left<<setw(9)<<((mGender==XyzEmployeeEnums::Male)?"Male":"Female")<<" | "<<left<<setw(13)<<mDOB<<" | "<<left<<setw(15)<<mDOJ<<" | "
    <<left<<setw(11)<<mLeavesLeft<<" | "<<left<<setw(14)<<mLeavesAvailed<<" | "<<left<<setw(14)<<"NA"<<" | "<<left<<setw(7)<<"NA"<<" | "
    <<left<<setw(6)<<"NA"<<" |\n";
}*/
void XyzEmployeeManager::printAllCurrent() const {
    std::cout << "Current Employees Summary:\n";
    if (mCurrentDeque.empty()) {
        std::cout << "No current employees to display.\n";
        return;
    }
    printSummaryHeaderBox();
    auto it = mCurrentDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        // print a line using the base/derived printSummary formatting
        std::ostringstream oss;
        // use printSummary to output formatted part, but we will capture to cout directly
        e->printSummary();
        // for readability endline after summary
        std::cout << "\n";
        it.next();
    }
    std::cout << "-------------------------------------------\n";
}

void XyzEmployeeManager::printAllResigned() const {
    std::cout << "Resigned Employees Summary:\n";
    if (mResignedDeque.empty()) {
        std::cout << "No resigned employees to display.\n";
        return;
    }
    printSummaryHeaderBox();
    auto it = mResignedDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        e->printSummary();
        std::cout << "\n";
        it.next();
    }
    std::cout << "---------------------------------------------------------------\n";
}

void XyzEmployeeManager::printSummaryCounts() const {
    int total = mCurrentDeque.size();
    int resigned = mResignedDeque.size();
    int full=0, cont=0, intern=0;
    auto it = mCurrentDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        if (e->getType()==EmpType::FullTime) ++full;
        if (e->getType()==EmpType::Contractor) ++cont;
        if (e->getType()==EmpType::Intern) ++intern;
        it.next();
    }
    std::cout << "Current Employees: " << total << " | FullTime: " << full << " | Contractor: " << cont << " | Intern: " << intern << " | Resigned: " << resigned << "\n";
}
