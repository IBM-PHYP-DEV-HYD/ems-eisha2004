#ifndef XYZEMPBASE_H
#define XYZEMPBASE_H

#include <string>
#include <iostream>
#include <iomanip>
#include "XyzEmployeeIF.H"
#include "Enums.H"

class XyzEmpBase : public XyzEmpIF {
protected:
    std::string mName;
    std::string mId;
    EmpType mType;
    EmpStatus mStatus;
    Gender mGender;
    std::string mDob;
    std::string mDoj;
    std::string mDol;

public:
    XyzEmpBase(const std::string &nameParm,
               const std::string &idParm,
               EmpType typeParm,
               EmpStatus statusParm,
               Gender genderParm,
               const std::string &dobParm,
               const std::string &dojParm,
               const std::string &dolParm = "NA")
        : mName(nameParm), mId(idParm), mType(typeParm),
          mStatus(statusParm), mGender(genderParm),
          mDob(dobParm), mDoj(dojParm), mDol(dolParm) {}

    virtual ~XyzEmpBase() {}

    // getters
    std::string getName() const override { return mName; }
    std::string getId() const override { return mId; }
    EmpType getType() const override { return mType; }
    EmpStatus getStatus() const override { return mStatus; }
    Gender getGender() const override { return mGender; }
    std::string getDob() const override { return mDob; }
    std::string getDoj() const override { return mDoj; }
    std::string getDol() const override { return mDol; }

    // updatables
    void setStatus(EmpStatus s) override { mStatus = s; }
    void setDol(const std::string& dol) override { mDol = dol; }

    // printing helpers
    virtual void printSummary() const override {
        // ID | Name | Type | Status | Gender | DOJ | Extra (derived prints)
        std::cout << std::left << std::setw(10) << mId << " "
                  << std::setw(18) << mName << " "
                  << std::setw(4) << (mType==EmpType::FullTime?"FT":(mType==EmpType::Contractor?"CT":"IN")) << " "
                  << std::setw(8) << (mStatus==EmpStatus::ACTIVE?"ACTIVE":(mStatus==EmpStatus::INACTIVE?"INACTIVE":"RESIGNED")) << " "
                  << std::setw(6) << (mGender==Gender::MALE?"M":(mGender==Gender::FEMALE?"F":"O")) << " "
                  << std::setw(10) << mDoj;
    }

    virtual void printDetails() const override {
        std::cout << "------------------------------------------\n";
        std::cout << "| Employee Name : " << mName << "\n";
        std::cout << "| Employee ID   : " << mId << "\n";
        std::cout << "| Employee Type : " << (mType==EmpType::FullTime?"Full-Time":(mType==EmpType::Contractor?"Contractor":"Intern")) << "\n";
        std::cout << "| Employee Status: " << (mStatus==EmpStatus::ACTIVE?"Active":(mStatus==EmpStatus::INACTIVE?"Inactive":"Resigned")) << "\n";
        std::cout << "| Gender        : " << (mGender==Gender::MALE?"Male":(mGender==Gender::FEMALE?"Female":"Other")) << "\n";
        std::cout << "| Date of Birth : " << mDob << "\n";
        std::cout << "| Date of Joining: " << mDoj << "\n";
        std::cout << "| Date of Leaving: " << mDol << "\n";
    }
};

#endif // XYZEMPBASE_H
