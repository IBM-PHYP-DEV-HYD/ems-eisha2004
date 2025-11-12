#ifndef XYZEMPLOYEEBUILDER_H
#define XYZEMPLOYEEBUILDER_H

#include "XyzEmployeeBase.H"
#include "XyzFullTimeEmployee.H"
#include "XyzContractorEmployee.H"
#include "XyzInternEmployee.H"
#include "Utils.H"

// ---------------------------------------------------------------------------
// XyzEmployeeBuilder
//  - Implements the Builder pattern to create Employee objects dynamically.
//  - Used by XyzEmployeeManager to add employees at random or on demand.
// ---------------------------------------------------------------------------

class XyzEmployeeBuilder {
private:
    static int sSeq;   // keeps track of sequential ID numbers

public:
    XyzEmployeeBuilder() = default;

    // Creates a random employee (FullTime, Contractor, or Intern)
    static XyzEmpBase* buildRandom();

    // Builds a minimal resigned employee record (for resigned deque)
    static XyzEmpBase* buildResignedMinimal(XyzEmpBase* e);
};

#endif // XYZEMPLOYEEBUILDER_H
