#include "XyzEmployeeManager.H"
#include "XyzFullTimeEmployee.H"
#include "XyzContractorEmployee.H"
#include "XyzInternEmployee.H"
#include <iostream>
#include <cstring>

XyzEmployeeManager::XyzEmployeeManager() {
    seedRandom();
}

XyzEmployeeManager::~XyzEmployeeManager() {
    // delete all employee pointers in both deques
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
    // if resigned by random, move minimal to resigned deque
    if (e->getStatus() == EmpStatus::RESIGNED) {
        // build minimal resigned copy
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
            // construct minimal resigned copy
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
            if (e->getType() == EmpType::FullTime) return false; // already
            // create full-time with same name/id/gender/dob/doj; new ID must end with F: change last char
            std::string oldid = e->getId();
            if (oldid.size()>=1) oldid[oldid.size()-1] = 'F';
            XyzFullTimeEmployee* nf = new XyzFullTimeEmployee(e->getName(), oldid, EmpStatus::ACTIVE, e->getGender(), e->getDob(), e->getDoj(), 0);
            // delete old
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

void XyzEmployeeManager::printAllCurrent() const {
    std::cout << "Current Employees Summary:\n";
    auto it = mCurrentDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        e->printSummary();
        it.next();
    }
}

void XyzEmployeeManager::printAllResigned() const {
    std::cout << "Resigned Employees Summary:\n";
    auto it = mResignedDeque.getIterator();
    while (it.hasNext()) {
        XyzEmpBase* e = it.value();
        e->printSummary();
        it.next();
    }
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
    std::cout << "Counts: Current="<<total<<" (Full="<<full<<" Ctr="<<cont<<" Int="<<intern<<") Resigned="<<resigned<<"\n";
}
