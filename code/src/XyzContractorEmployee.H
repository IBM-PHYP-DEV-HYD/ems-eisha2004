#ifndef XYZCONTRACTOR_H
#define XYZCONTRACTOR_H

#include "XyzEmployeeBase.H"
#include "Enums.H"
#include <iostream>

class XyzContractorEmployee : public XyzEmpBase {
    Agency mAgency;
public:
    XyzContractorEmployee(const std::string& nameParm,
                          const std::string& idParm,
                          EmpStatus statusParm,
                          Gender genderParm,
                          const std::string& dobParm,
                          const std::string& dojParm,
                          const std::string& dolParm,
                          Agency agencyParm)
    : XyzEmpBase(nameParm, idParm, EmpType::Contractor, statusParm, genderParm, dobParm, dojParm, dolParm),
      mAgency(agencyParm) {}

    Agency getAgency() const { return mAgency; }

    void printSummary() const override {
        XyzEmpBase::printSummary();
        std::string ag = (mAgency==Agency::Avengers?"Avengers":(mAgency==Agency::JusticeLeague?"Justice":"X-Men"));
        std::cout << " " << std::setw(10) << ag << "\n";
    }

    void printDetails() const override {
        XyzEmpBase::printDetails();
        std::string ag = (mAgency==Agency::Avengers?"Avengers":(mAgency==Agency::JusticeLeague?"JusticeLeague":"X-Men"));
        std::cout << " Agency:" << ag << "\n";
    }
};

#endif // XYZCONTRACTOR_H
