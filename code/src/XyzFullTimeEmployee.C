#include "XyzFullTimeEmployee.H"
#include <iomanip>
#include <iostream>

XyzFullTimeEmployee::XyzFullTimeEmployee(const std::string& nameParm,
                                         const std::string& idParm,
                                         EmpStatus statusParm,
                                         Gender genderParm,
                                         const std::string& dobParm,
                                         const std::string& dojParm,
                                         int leavesAvailedParm)
    : XyzEmpBase(nameParm, idParm, EmpType::FullTime, statusParm, genderParm, dobParm, dojParm, "NA"),
      mLeavesAvailed(leavesAvailedParm) 
{
    if (mLeavesAvailed < 0) mLeavesAvailed = 0;
    if (mLeavesAvailed > MAX_LEAVES_FULLTIME) mLeavesAvailed = MAX_LEAVES_FULLTIME;
}

int XyzFullTimeEmployee::getLeavesAvailed() const {
    return mLeavesAvailed;
}

void XyzFullTimeEmployee::addLeaves(int n) {
    // n may be positive or negative
    if (n == 0) return;
    int newv = mLeavesAvailed + n;
    if (newv < 0) newv = 0;
    if (newv > MAX_LEAVES_FULLTIME) newv = MAX_LEAVES_FULLTIME;
    mLeavesAvailed = newv;
}

void XyzFullTimeEmployee::printSummary() const {
    XyzEmpBase::printSummary();
    std::cout << " " << std::setw(3) << mLeavesAvailed << "/" << std::setw(3) << MAX_LEAVES_FULLTIME << "\n";
}

void XyzFullTimeEmployee::printDetails() const {
    XyzEmpBase::printDetails();
    std::cout << "| Leaves Availed : " << mLeavesAvailed << "\n";
    std::cout << "| Leaves Left    : " << (MAX_LEAVES_FULLTIME - mLeavesAvailed) << "\n";
    std::cout << "-------------------------------------------------------------------------------\n";
}
