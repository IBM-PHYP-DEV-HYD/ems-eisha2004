#ifndef XYZINTERN_H
#define XYZINTERN_H

#include "XyzEmployeeBase.H"
#include "Enums.H"
#include <iostream>

class XyzInternEmployee : public XyzEmpBase {
    College mCollege;
    Branch mBranch;

public:
    XyzInternEmployee(const std::string& nameParm,
                      const std::string& idParm,
                      EmpStatus statusParm,
                      Gender genderParm,
                      const std::string& dobParm,
                      const std::string& dojParm,
                      const std::string& dolParm,
                      College collegeParm,
                      Branch branchParm);

    void printSummary() const override;
    void printDetails() const override;
};

#endif // XYZINTERN_H
