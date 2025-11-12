#ifndef XYZEMPLOYEEMANAGER_H
#define XYZEMPLOYEEMANAGER_H

#include <string>
#include "EDLL.H"
#include "XyzEmployeeBase.H"
#include "XyzFullTimeEmployee.H"
#include "XyzContractorEmployee.H"
#include "XyzInternEmployee.H"
#include "Enums.H"

class XyzEmployeeManager {
private:
    EDLL<XyzEmpBase*> mCurrentEmployees;
    EDLL<XyzEmpBase*> mResignedEmployees;

public:
  
    void addFullTime(XyzFullTimeEmployee* e);
    void addContractor(XyzContractorEmployee* e);
    void addIntern(XyzInternEmployee* e);

    bool removeEmployeeById(const std::string& id);

    XyzEmpBase* findById(const std::string& id);
    void findByName(const std::string& namePart);

    void printAllCurrent() const;
    void printAllResigned() const;
    void printSummaryByType(const std::string& type) const;
    void printSummaryByGender(const std::string& gender) const;
    void printSummaryByStatus(const std::string& status) const;

    void addLeavesToAllFullTime(int n);
    void convertInternToFullTime(const std::string& id);
    void printSummaryCounts() const;

    bool isCurrentEmpty() const;
    bool isResignedEmpty() const;
};

#endif // XYZEMPLOYEEMANAGER_H
