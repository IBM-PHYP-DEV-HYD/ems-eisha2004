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
                      Branch branchParm)
    : XyzEmpBase(nameParm, idParm, EmpType::Intern, statusParm, genderParm, dobParm, dojParm, dolParm),
      mCollege(collegeParm), mBranch(branchParm) {}

    void printSummary() const override {
        XyzEmpBase::printSummary();
        std::string cl = "College";
        std::string br = (mBranch==Branch::CSE?"CSE":(mBranch==Branch::CSIT?"CSIT":"ECE"));
        std::cout << " " << std::setw(6) << br << "\n";
    }

    void printDetails() const override {
        XyzEmpBase::printDetails();
        // print college string
        std::string cl;
        switch(mCollege) {
            case College::IITDelhi: cl="IIT Delhi"; break;
            case College::IITMumbai: cl="IIT Mumbai"; break;
            case College::IITKanpur: cl="IIT Kanpur"; break;
            case College::IITHyderabad: cl="IIT Hyderabad"; break;
            case College::NITWarangal: cl="NIT Warangal"; break;
            case College::NITTiruchi: cl="NIT Tiruchi"; break;
            case College::IIITHyderabad: cl="IIIT Hyderabad"; break;
            default: cl="Unknown";
        }
        std::string br = (mBranch==Branch::CSE?"CSE":(mBranch==Branch::CSIT?"CSIT":"ECE"));
        std::cout << " College:" << cl << " Branch:" << br << "\n";
    }
};

#endif // XYZINTERN_H
