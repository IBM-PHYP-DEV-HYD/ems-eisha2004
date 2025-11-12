#ifndef XYZFULLTIME_H
#define XYZFULLTIME_H

#include "XyzEmployeeBase.H"

class XyzFullTimeEmployee : public XyzEmpBase {
    int mLeavesAvailed; 
public:

    XyzFullTimeEmployee()
        : XyzEmpBase("Default FT", "FT001", EmpType::FullTime, EmpStatus::ACTIVE, Gender::MALE,
                     "1990-01-01", "2020-01-01", "NA"),
          mLeavesAvailed(0) {}

  
    XyzFullTimeEmployee(const std::string& nameParm,
                        const std::string& idParm,
                        EmpStatus statusParm,
                        Gender genderParm,
                        const std::string& dobParm,
                        const std::string& dojParm,
                        int leavesAvailedParm = 0);

    int getLeavesAvailed() const;
    void addLeaves(int n);
    void printSummary() const override;
    void printDetails() const override;
};

#endif // XYZFULLTIME_H
