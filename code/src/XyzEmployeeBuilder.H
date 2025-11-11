#ifndef XYZBUILDER_H
#define XYZBUILDER_H

#include "XyzEmployeeBase.H"
#include "XyzFullTimeEmployee.H"
#include "XyzContractorEmployee.H"
#include "XyzInternEmployee.H"
#include "Utils.H"

class XyzEmployeeBuilder {
private:
    static int sSeq;
    // builder fields:
    std::string bName;
    EmpType bType;
    EmpStatus bStatus;
    Gender bGender;
    std::string bDob;
    std::string bDoj;
    std::string bDol;
    int bLeaves;
    Agency bAgency;
    College bCollege;
    Branch bBranch;

public:
    XyzEmployeeBuilder();
    XyzEmployeeBuilder& setName(const std::string& n);
    XyzEmployeeBuilder& setType(EmpType t);
    XyzEmployeeBuilder& setStatus(EmpStatus s);
    XyzEmployeeBuilder& setGender(Gender g);
    XyzEmployeeBuilder& setDob(const std::string& d);
    XyzEmployeeBuilder& setDoj(const std::string& d);
    XyzEmployeeBuilder& setDol(const std::string& d);
    XyzEmployeeBuilder& setLeaves(int l);
    XyzEmployeeBuilder& setAgency(Agency a);
    XyzEmployeeBuilder& setCollege(College c);
    XyzEmployeeBuilder& setBranch(Branch b);

    void randomize();
    XyzEmpBase* build();
    static XyzEmpBase* buildResignedMinimal(XyzEmpBase* src);
};

#endif // XYZBUILDER_H
