#include "XyzInternEmployee.H"
#include <iomanip>
#include <iostream>
#include"Utils.H"

static inline std::string collegeToString(College c) {
    switch (c) {
        case College::IITDelhi: return "IIT Delhi";
        case College::IITMumbai: return "IIT Mumbai";
        case College::IITKanpur: return "IIT Kanpur";
        case College::IITHyderabad: return "IIT Hyderabad";
        case College::NITWarangal: return "NIT Warangal";
        case College::NITTiruchi: return "NIT Tiruchi";
        case College::IIITHyderabad: return "IIIT Hyderabad";
        default: return "NA";
    }
}

static inline std::string branchToString(Branch b) {
    switch (b) {
        case Branch::CSE: return "CSE";
        case Branch::CSIT: return "CSIT";
        case Branch::ECE: return "ECE";
        default: return "NA";
    }
}

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
      mCollege(collegeParm),
      mBranch(branchParm) {}

XyzInternEmployee::XyzInternEmployee()
  : XyzEmpBase(
        randName(),
        makeUniqueId(EmpType::Intern),
        EmpType::Intern,
        randStatus(),
        randGender(),
        makeRandomDOB(),
        makeRandomDOJ(),
        std::string("NA")
    ),
    mCollege(randCollege()),
    mBranch(randBranch())
{
    if (getStatus() == EmpStatus::RESIGNED) {
        setDol("2024-12-31");  
    }
}
College XyzInternEmployee::getCollege() const { return mCollege; }
Branch XyzInternEmployee::getBranch() const { return mBranch; }

void XyzInternEmployee::printSummary() const {
    XyzEmpBase::printSummary();
    std::cout << std::left << std::setw(12)  << "NA"
              << " | " << std::left << std::setw(14) << "NA"
              << " | " << std::left << std::setw(7)  << branchToString(mBranch)
              << " | " << std::left << std::setw(15) << collegeToString(mCollege)
              << " |" << std::endl;
}

void XyzInternEmployee::printDetails() const {
    XyzEmpBase::printDetails();
    std::cout << " | " << std::left << std::setw(11) << "NA"
              << " | " << std::left << std::setw(14) << "NA"
              << " | " << std::left << std::setw(7) << branchToString(mBranch)
              << " | " << std::left << std::setw(15) << collegeToString(mCollege)
              <<" | "
              ;
}
