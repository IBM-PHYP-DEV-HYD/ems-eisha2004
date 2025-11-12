#ifndef XYZEMPLOYEEBUILDER_H
#define XYZEMPLOYEEBUILDER_H

#include "XyzEmployeeBase.H"
#include "XyzFullTimeEmployee.H"
#include "XyzContractorEmployee.H"
#include "XyzInternEmployee.H"
#include "Utils.H"



class XyzEmployeeBuilder {
private:
    static int sSeq;   

public:
    XyzEmployeeBuilder() = default;

    static XyzEmpBase* buildRandom();

    static XyzEmpBase* buildResignedMinimal(XyzEmpBase* e);
};

#endif // XYZEMPLOYEEBUILDER_H
