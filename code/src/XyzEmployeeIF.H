#ifndef XYZEMPLOYEEIF_H
#define XYZEMPLOYEEIF_H

#include <string>
#include "Enums.H"

class XyzEmpIF {
public:
    virtual ~XyzEmpIF() {}
    virtual std::string getName() const = 0;
    virtual std::string getId() const = 0;
    virtual EmpType getType() const = 0;
    virtual EmpStatus getStatus() const = 0;
    virtual Gender getGender() const = 0;
    virtual std::string getDob() const = 0;
    virtual std::string getDoj() const = 0;
    virtual std::string getDol() const = 0;
    virtual void setStatus(EmpStatus s) = 0;
    virtual void setDol(const std::string& dol) = 0;

    virtual void printSummary() const = 0;
    virtual void printDetails() const = 0;
};

#endif // XYZEMPLOYEEIF_H
