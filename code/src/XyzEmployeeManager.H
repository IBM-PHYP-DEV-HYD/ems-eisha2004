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
    // Add employees
    void addFullTime(XyzFullTimeEmployee* e);
    void addContractor(XyzContractorEmployee* e);
    void addIntern(XyzInternEmployee* e);

    // Remove employee
    bool removeEmployeeById(const std::string& id);

    // Search/find
    XyzEmpBase* findById(const std::string& id);
    void findByName(const std::string& namePart);

    // Print summaries
    void printAllCurrent() const;
    void printAllResigned() const;
    void printSummaryByType(const std::string& type) const;
    void printSummaryByGender(const std::string& gender) const;
    void printSummaryByStatus(const std::string& status) const;

    // Other operations
    void addLeavesToAllFullTime(int n);
    void convertInternToFullTime(const std::string& id);
    void printSummaryCounts() const;

    // Utility
    bool isCurrentEmpty() const;
    bool isResignedEmpty() const;
};

#endif // XYZEMPLOYEEMANAGER_H
