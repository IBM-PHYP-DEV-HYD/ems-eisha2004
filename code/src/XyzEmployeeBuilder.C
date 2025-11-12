#include "XyzEmployeeBuilder.H"
#include "XyzFullTimeEmployee.H"
#include "XyzContractorEmployee.H"
#include "XyzInternEmployee.H"
#include "Utils.H"
#include <iostream>

int XyzEmployeeBuilder::sSeq = 1;

XyzEmpBase* XyzEmployeeBuilder::buildRandom() {
    static bool seeded = false;
    if (!seeded) { seedRandom(); seeded = true; }

    int typeVal = randInt(0, 2);
    EmpType type = (typeVal == 0 ? EmpType::FullTime :
                   (typeVal == 1 ? EmpType::Contractor : EmpType::Intern));

    std::string name   = randName();
    EmpStatus status   = randStatus();
    Gender gender      = randGender();
    std::string dob    = makeRandomDOB();
    std::string doj    = makeRandomDOJ();
    std::string dol    = "NA";
    std::string id     = makeUniqueId(type);

    if (status == EmpStatus::RESIGNED) dol = "2024-12-31";

    if (type == EmpType::FullTime) {
        int leaves = randInt(0, 22);
        return new XyzFullTimeEmployee(name, id, status, gender, dob, doj, leaves);
    }
    else if (type == EmpType::Contractor) {
        Agency agency = randAgency();
        return new XyzContractorEmployee(name, id, status, gender, dob, doj, dol, agency);
    }
    else {
        College college = randCollege();
        Branch branch = randBranch();
        return new XyzInternEmployee(name, id, status, gender, dob, doj, dol, college, branch);
    }
}
