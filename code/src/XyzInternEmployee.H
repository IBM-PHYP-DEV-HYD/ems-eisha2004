#ifndef XYZINTERN_H
#define XYZINTERN_H

#include "XyzEmployeeBase.H"
#include "Enums.H"

class XyzInternEmployee : public XyzEmpBase {
    College mCollege;
    Branch mBranch;
public:
    // ✅ Default constructor
    XyzInternEmployee()
        : XyzEmpBase("Default Intern", "IN001", EmpType::Intern, EmpStatus::ACTIVE, Gender::FEMALE,
                     "2000-08-12", "2024-05-01", "NA"),
          mCollege(College::IITDelhi), mBranch(Branch::CSE) {}

    // ✅ Existing parameterized constructor
    XyzInternEmployee(const std::string& nameParm,
                      const std::string& idParm,
                      EmpStatus statusParm,
                      Gender genderParm,
                      const std::string& dobParm,
                      const std::string& dojParm,
                      const std::string& dolParm,
                      College collegeParm,
                      Branch branchParm);

    College getCollege() const;
    Branch getBranch() const;

    void printSummary() const override;
    void printDetails() const override;
};

#endif // XYZINTERN_H
