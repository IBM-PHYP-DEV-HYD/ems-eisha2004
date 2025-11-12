#include "XyzEmployeeBase.H"
#include <iostream>
#include <iomanip>

XyzEmpBase::XyzEmpBase(const std::string &nameParm,
                       const std::string &idParm,
                       EmpType typeParm,
                       EmpStatus statusParm,
                       Gender genderParm,
                       const std::string &dobParm,
                       const std::string &dojParm,
                       const std::string &dolParm)
    : mName(nameParm), mId(idParm), mType(typeParm),
      mStatus(statusParm), mGender(genderParm),
      mDob(dobParm), mDoj(dojParm), mDol(dolParm) {}

std::string XyzEmpBase::getName() const { return mName; }
std::string XyzEmpBase::getId() const { return mId; }
EmpType XyzEmpBase::getType() const { return mType; }
EmpStatus XyzEmpBase::getStatus() const { return mStatus; }
Gender XyzEmpBase::getGender() const { return mGender; }
std::string XyzEmpBase::getDob() const { return mDob; }
std::string XyzEmpBase::getDoj() const { return mDoj; }
std::string XyzEmpBase::getDol() const { return mDol; }

void XyzEmpBase::setStatus(EmpStatus s) { mStatus = s; }
void XyzEmpBase::setDol(const std::string& dol) { mDol = dol; }
XyzEmpBase::~XyzEmpBase() {}

// ─────────────────────────────────────────────────────────────
// Summary (one-line table row format for listing employees)
// ─────────────────────────────────────────────────────────────
void XyzEmpBase::printSummary() const {
    std::cout << "| " << std::left << std::setw(23) << mName
              << "| " << std::setw(11) << mId
              << "| " << std::setw(11)<< (mType==EmpType::FullTime ? "FullTime" :
                  (mType==EmpType::Contractor ? "Contract" : "Intern"))
              << "| " << std::setw(13)<< (mStatus==EmpStatus::ACTIVE ? "Active" :
                  (mStatus==EmpStatus::INACTIVE ? "Inactive" : "Resigned"))
              << "| " << std::setw(10)<< (mGender==Gender::MALE ? "Male" :
                  (mGender==Gender::FEMALE ? "Female" : "Other"))
              << "| " << std::setw(14) << mDob
              << "| " << std::setw(16) << mDoj
              << "|";
   
}

// ─────────────────────────────────────────────────────────────
// Detailed (box-style) info for a single employee
// ─────────────────────────────────────────────────────────────
void XyzEmpBase::printDetails() const {
    std::cout << "------------------------------------------\n";
    std::cout << "| Employee Name   : " << mName << "\n";
    std::cout << "| Employee ID     : " << mId << "\n";
    std::cout << "| Employee Type   : "
              << (mType==EmpType::FullTime ? "Full-Time" :
                  (mType==EmpType::Contractor ? "Contractor" : "Intern")) << "\n";
    std::cout << "| Employee Status : "
              << (mStatus==EmpStatus::ACTIVE ? "Active" :
                  (mStatus==EmpStatus::INACTIVE ? "Inactive" : "Resigned")) << "\n";
    std::cout << "| Gender          : "
              << (mGender==Gender::MALE ? "Male" :
                  (mGender==Gender::FEMALE ? "Female" : "Other")) << "\n";
    std::cout << "| Date of Birth   : " << mDob << "\n";
    std::cout << "| Date of Joining : " << mDoj << "\n";
    std::cout << "| Date of Leaving : " << mDol << "\n";
}
