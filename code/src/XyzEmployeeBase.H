#ifndef XYZEMPBASE_H
#define XYZEMPBASE_H
#include <iostream>
#include <string>
#include <iomanip>
#include "XyzEmployeeIF.H"
#include "Enums.H"

class XyzEmpBase : public XyzEmpIF {
protected:
    std::string mName;
    std::string mId; // e.g. XYZ0001F
    EmpType mType;
    EmpStatus mStatus;
    Gender mGender;
    std::string mDob;
    std::string mDoj;
    std::string mDol; // "NA" when not applicable

public:
    XyzEmpBase(const std::string& nameParm,
               const std::string& idParm,
               EmpType typeParm,
               EmpStatus statusParm,
               Gender genderParm,
               const std::string& dobParm,
               const std::string& dojParm,
               const std::string& dolParm = "NA")
    : mName(nameParm), mId(idParm), mType(typeParm), mStatus(statusParm),
      mGender(genderParm), mDob(dobParm), mDoj(dojParm), mDol(dolParm) {}

    virtual ~XyzEmpBase() {}

    // Getters
    std::string getName() const override { return mName; }
    std::string getId() const override { return mId; }
    EmpType getType() const override { return mType; }
    EmpStatus getStatus() const override { return mStatus; }
    Gender getGender() const override { return mGender; }
    std::string getDob() const override { return mDob; }
    std::string getDoj() const override { return mDoj; }
    std::string getDol() const override { return mDol; }

    // Setters
    void setStatus(EmpStatus s) override { mStatus = s; }
    void setDol(const std::string& dol) override { mDol = dol; }

    // summaries - base prints common columns; derived classes append more
    virtual void printSummary() const override {
        // simple fixed-width summary: ID | Name | Type | Status | Gender | DOJ
        std::cout << std::left << std::setw(10) << mId << " "
                  << std::setw(20) << mName << " "
                  << std::setw(8) << (mType==EmpType::FullTime?"Full":"Ctr") << " "
                  << std::setw(8) << (mStatus==EmpStatus::ACTIVE?"ACT":"RES") << " "
                  << std::setw(6) << (mGender==Gender::MALE?"M":(mGender==Gender::FEMALE?"F":"O")) << " "
                  << std::setw(10) << mDoj;
    }

    virtual void printDetails() const override {
        printSummary();
        std::cout << " DOB:" << mDob << " DOL:" << mDol;
    }
};

#endif // XYZEMPBASE_H
