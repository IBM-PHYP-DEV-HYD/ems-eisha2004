#include "XyzContractorEmployee.H"
#include <iomanip>
#include <iostream>

XyzContractorEmployee::XyzContractorEmployee(const std::string& nameParm,
                                             const std::string& idParm,
                                             EmpStatus statusParm,
                                             Gender genderParm,
                                             const std::string& dobParm,
                                             const std::string& dojParm,
                                             const std::string& dolParm,
                                             Agency agencyParm)
    : XyzEmpBase(nameParm, idParm, EmpType::Contractor, statusParm, genderParm, dobParm, dojParm, dolParm),
      mAgency(agencyParm) {}

Agency XyzContractorEmployee::getAgency() const {
    return mAgency;
}

static std::string agencyToString(Agency a) {
    switch(a) {
        case Agency::Avengers: return "Avengers";
        case Agency::JusticeLeague: return "JusticeLeague";
        case Agency::XMen: return "X-Men";
        default: return "None";
    }
}

void XyzContractorEmployee::printSummary() const {
    XyzEmpBase::printSummary();
    std::cout << " " << std::setw(10) << agencyToString(mAgency) << "\n";
}

void XyzContractorEmployee::printDetails() const {
    XyzEmpBase::printDetails();
    std::cout << "| External Agency : " << agencyToString(mAgency) << "\n";
    std::cout << "------------------------------------------\n";
}
