#include "XyzFullTimeEmployee.H"
#include <iostream>
#include <iomanip>

XyzFullTimeEmployee::XyzFullTimeEmployee(const std::string& nameParm,
                                         const std::string& idParm,
                                         EmpStatus statusParm,
                                         Gender genderParm,
                                         const std::string& dobParm,
                                         const std::string& dojParm,
                                         int leavesAvailedParm)
    : XyzEmpBase(nameParm, idParm, EmpType::FullTime, statusParm, genderParm, dobParm, dojParm, "NA"),
      mLeavesAvailed(leavesAvailedParm) {
    if (mLeavesAvailed < 0) mLeavesAvailed = 0;
    if (mLeavesAvailed > 22) mLeavesAvailed = 22;
}

int XyzFullTimeEmployee::getLeavesAvailed() const {
    return mLeavesAvailed;
}

void XyzFullTimeEmployee::addLeaves(int n) {
    if (n <= 0) return;
    mLeavesAvailed += n;
    if (mLeavesAvailed > 22) mLeavesAvailed = 22;
}

void XyzFullTimeEmployee::printSummary() const {
    XyzEmpBase::printSummary();
    std::cout << std::left << std::setw(12)  << mLeavesAvailed
              << " | " << std::left << std::setw(14) << "NA"
              << " | " << std::left << std::setw(7)  << "NA"
              << " | " << std::left << std::setw(11) << "NA"
              << " |" << std::endl;
}


void XyzFullTimeEmployee::printDetails() const {
    XyzEmpBase::printDetails();
    std::string leavesInfo = std::to_string(mLeavesAvailed) + "/22";
    std::cout <<std::left << std::setw(12) << leavesInfo
              <<" | "<<std::left << std::setw(13) << "NA"
              <<" | "<< std::left << std::setw(6) << "NA"
              <<" | "<< std::left << std::setw(14) << "NA" << " |";
}
