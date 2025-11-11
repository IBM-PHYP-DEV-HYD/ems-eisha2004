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
                        int leavesAvailedParm = 0);

    int getLeavesAvailed() const;
    void addLeaves(int n); // adds n leaves (can be negative to subtract) - clamped

    void printSummary() const override;
    void printDetails() const override;
};

#endif // XYZFULLTIME_H
