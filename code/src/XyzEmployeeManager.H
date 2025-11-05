#ifndef XYZMANAGER_H
#define XYZMANAGER_H

#include "EDLL.H"
#include "XyzEmployeeBase.H"
#include "XyzEmployeeBuilder.H"
#include <string>

class XyzEmployeeManager {
    EDLL<XyzEmpBase*> mCurrentDeque; // ACTIVE + INACTIVE
    EDLL<XyzEmpBase*> mResignedDeque; // minimal info objects
public:
    XyzEmployeeManager();
    ~XyzEmployeeManager();

    // Add operations
    void addEmployeeRandom();
    void addNEmployeesRandom(int n);
    void addFullTime(XyzFullTimeEmployee* e);
    void addContractor(XyzContractorEmployee* e);
    void addIntern(XyzInternEmployee* e);

    // Remove (resign)
    bool removeEmployeeById(const std::string& id);

    // Searches
    XyzEmpBase* findById(const std::string& id);
    void findByName(const std::string& namePart); // prints matches

    // Conversions
    bool convertToFullTime(const std::string& id);

    // Leaves
    void addLeavesToAllFullTime(int n);

    // Print
    void printAllCurrent() const;
    void printAllResigned() const;

    // helpers
    void printSummaryCounts() const;
};

#endif // XYZMANAGER_H
