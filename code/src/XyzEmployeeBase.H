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
               const std::string &dolParm = "NA");

    virtual ~XyzEmpBase();

    // getters
    std::string getName() const override;
    std::string getId() const override;
    EmpType getType() const override;
    EmpStatus getStatus() const override;
    Gender getGender() const override;
    std::string getDob() const override;
    std::string getDoj() const override;
    std::string getDol() const override;

    // updatables
    void setStatus(EmpStatus s) override;
    void setDol(const std::string& dol) override;

    // printing helpers (base prints common columns)
    virtual void printSummary() const override;
    virtual void printDetails() const override;
};

#endif // XYZEMPBASE_H
