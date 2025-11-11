#include "XyzInternEmployee.H"
#include <iomanip>
#include <iostream>

XyzInternEmployee::XyzInternEmployee(const std::string& nameParm,
                                     const std::string& idParm,
                                     EmpStatus statusParm,
                                     Gender genderParm,
                                     const std::string& dobParm,
                                     const std::string& dojParm,
                                     const std::string& dolParm,
                                     College collegeParm,
                                     Branch branchParm)
    : XyzEmpBase(nameParm, idParm, EmpType::Intern, statusParm, genderParm, dobParm, dojParm, dolParm),
      mCollege(collegeParm), mBranch(branchParm) {}

static std::string collegeToString(College c) {
    switch(c) {
        case College::IITDelhi: return "IIT Delhi";
        case College::IITMumbai: return "IIT Mumbai";
        case College::IITKanpur: return "IIT Kanpur";
        case College::IITHyderabad: return "IIT Hyderabad";
        case College::NITWarangal: return "NIT Warangal";
        case College::NITTiruchi: return "NIT Tiruchi";
        case College::IIITHyderabad: return "IIIT Hyderabad";
        default: return "Unknown";
    }
}
static std::string branchToString(Branch b) {
    switch(b) {
        case Branch::CSE: return "CSE";
        case Branch::CSIT: return "CSIT";
        case Branch::ECE: return "ECE";
        default: return "Unknown";
    }
}

void XyzInternEmployee::printSummary() const {
    XyzEmpBase::printSummary();
    std::cout << " " << std::setw(6) << branchToString(mBranch) << "\n";
}

void XyzInternEmployee::printDetails() const {
    XyzEmpBase::printDetails();
    std::cout << "| College        : " << collegeToString(mCollege) << "\n";
    std::cout << "| Branch         : " << branchToString(mBranch) << "\n";
    std::cout << "------------------------------------------\n";
}
