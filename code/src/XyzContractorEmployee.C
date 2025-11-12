#include "XyzContractorEmployee.H"
#include <iomanip>
#include <iostream>

// Utility function to convert Agency enum to string
static inline std::string agencyToString(Agency a) {
    switch (a) {
        case Agency::Avengers: return "Avengers";
        case Agency::JusticeLeague: return "JusticeLeague";
        case Agency::XMen: return "XMen";
        default: return "NA";
    }
}

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

void XyzContractorEmployee::printSummary() const {
    XyzEmpBase::printSummary();
    std::cout << std::left << std::setw(12)  << "NA"
              << " | " << std::left << std::setw(14) << agencyToString(mAgency)
              << " | " << std::left << std::setw(7)  << "NA"
              << " | " << std::left << std::setw(11) << "NA"
              << " |" << std::endl;
}


void XyzContractorEmployee::printDetails() const {
    XyzEmpBase::printDetails();
    std::cout << " | " << std::left << std::setw(11) << "NA"
              << " | " << std::left << std::setw(14) << agencyToString(mAgency)
              << " | " << std::left << std::setw(7) << "NA"
              << " | " << std::left << std::setw(6) << "NA" << " | ";
}
