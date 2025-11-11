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
                          Agency agencyParm);

    Agency getAgency() const;

    void printSummary() const override;
    void printDetails() const override;
};

#endif // XYZCONTRACTOR_H
