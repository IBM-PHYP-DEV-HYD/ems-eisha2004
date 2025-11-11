#ifndef XYZEMPLOYEEMANAGER_H
#define XYZEMPLOYEEMANAGER_H

#include "EDLL.H"
#include "XyzEmployeeBase.H"
#include "XyzEmployeeBuilder.H"
#include <string>

class XyzEmployeeManager {
    EDLL<XyzEmpBase*> mCurrentDeque; // ACTIVE + INACTIVE
    EDLL<XyzEmpBase*> mResignedDeque; // Resigned(removed from the company)
public:
    XyzEmployeeManager();
    ~XyzEmployeeManager();

    
    void addEmployeeRandom();
    void addNEmployeesRandom(int n);
    void addFullTime(XyzFullTimeEmployee* e);
    void addContractor(XyzContractorEmployee* e);
    void addIntern(XyzInternEmployee* e);

    
    bool removeEmployeeById(const std::string& id);

   
    XyzEmpBase* findById(const std::string& id);
    void findByName(const std::string& namePart); 

    
    bool convertToFullTime(const std::string& id);
    bool isCurrentEmpty() const { return mCurrentDeque.empty(); }
    bool isResignedEmpty() const { return mResignedDeque.empty(); }

    
    void addLeavesToAllFullTime(int n);

    // Print
    void printAllCurrent() const;
    void printAllResigned() const;

   
    void printSummaryCounts() const;
};

#endif // XYZEMPLOYEEMANAGER_H
