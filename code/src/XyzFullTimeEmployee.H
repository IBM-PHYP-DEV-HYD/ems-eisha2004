#ifndef XYZFULLTIME_H
#define XYZFULLTIME_H

#include "XyzEmployeeBase.H"
#include "Config.H"
#include <iostream>

class XyzFullTimeEmployee : public XyzEmpBase {
    int mLeavesAvailed;
public:
    XyzFullTimeEmployee(const std::string& nameParm,
                        const std::string& idParm,
                        EmpStatus statusParm,
                        Gender genderParm,
                        const std::string& dobParm,
                        const std::string& dojParm,
                        int leavesAvailedParm = 0)
    : XyzEmpBase(nameParm, idParm, EmpType::FullTime, statusParm, genderParm, dobParm, dojParm, "NA"),
      mLeavesAvailed(leavesAvailedParm) {}

    int getLeavesAvailed() const { return mLeavesAvailed; }
    void addLeaves(int n) { mLeavesAvailed += n; if (mLeavesAvailed < 0) mLeavesAvailed = 0; if (mLeavesAvailed > MAX_LEAVES_FULLTIME) mLeavesAvailed = MAX_LEAVES_FULLTIME; }

    void printSummary() const override {
        XyzEmpBase::printSummary();
        std::cout << " " << std::setw(3) << mLeavesAvailed << "/" << std::setw(3) << MAX_LEAVES_FULLTIME << "\n";
    }

    void printDetails() const override {
        XyzEmpBase::printDetails();
        std::cout << " LeavesAvailed:" << mLeavesAvailed << " LeavesLeft:" << (MAX_LEAVES_FULLTIME - mLeavesAvailed) << "\n";
    }
};

#endif // XYZFULLTIME_H
