#include "XyzEmployeeBuilder.H"
#include <sstream>
#include <iostream>

int XyzEmployeeBuilder::sSeq = 1;

XyzEmployeeBuilder::XyzEmployeeBuilder() {
    bName = "Unknown";
    bType = EmpType::Unknown;
    bStatus = EmpStatus::ACTIVE;
    bGender = Gender::MALE;
    bDob = "1990-01-01";
    bDoj = "2020-01-01";
    bDol = "NA";
    bLeaves = 0;
    bAgency = Agency::None;
    bCollege = College::None;
    bBranch = Branch::UnknownBranch;
}

XyzEmployeeBuilder& XyzEmployeeBuilder::setName(const std::string& n){ bName=n; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setType(EmpType t){ bType=t; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setStatus(EmpStatus s){ bStatus=s; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setGender(Gender g){ bGender=g; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setDob(const std::string& d){ bDob=d; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setDoj(const std::string& d){ bDoj=d; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setDol(const std::string& d){ bDol=d; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setLeaves(int l){ bLeaves=l; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setAgency(Agency a){ bAgency=a; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setCollege(College c){ bCollege=c; return *this; }
XyzEmployeeBuilder& XyzEmployeeBuilder::setBranch(Branch b){ bBranch=b; return *this; }

void XyzEmployeeBuilder::randomize() {
    // assign a random type, then type-specific fields
    int t = randInt(0,2);
    if (t==0) bType = EmpType::FullTime;
    else if (t==1) bType = EmpType::Contractor;
    else bType = EmpType::Intern;

    // names: simple generated
    std::ostringstream n;
    n << "Emp" << sSeq;
    bName = n.str();
    bGender = randGender();
    bStatus = randStatus();
    bDob = makeRandomDOB();
    bDoj = makeRandomDOJ();
    bDol = "NA";
    if (bType == EmpType::FullTime) {
        bLeaves = randInt(0, MAX_LEAVES_FULLTIME);
        // FullTime DOJ -> DOL NA
    } else if (bType == EmpType::Contractor) {
        // DOL = DOJ + 1year -> for simplicity mark as string "1yr-from-doj" or compute naive
        bAgency = randAgency();
        // naive DOL: increment year by 1
        int y, m, d;
        if (sscanf(bDoj.c_str(), "%d-%d-%d", &y,&m,&d)==3) {
            y += 1;
            std::ostringstream dol; dol<<y<<"-"<<std::setw(2)<<std::setfill('0')<<m<<"-"<<std::setw(2)<<std::setfill('0')<<d;
            bDol = dol.str();
        } else bDol = "NA";
    } else if (bType == EmpType::Intern) {
        bCollege = randCollege();
        bBranch = randBranch();
        // naive DOL: +6 months
        int y, m, d;
        if (sscanf(bDoj.c_str(), "%d-%d-%d", &y,&m,&d)==3) {
            m += 6; if (m>12) { y += 1; m -= 12; }
            std::ostringstream dol; dol<<y<<"-"<<std::setw(2)<<std::setfill('0')<<m<<"-"<<std::setw(2)<<std::setfill('0')<<d;
            bDol = dol.str();
        } else bDol = "NA";
    }
}

XyzEmpBase* XyzEmployeeBuilder::build() {
    if (bType == EmpType::Unknown) bType = EmpType::FullTime;
    std::string id = makeId(sSeq, bType);
    ++sSeq;
    if (bType == EmpType::FullTime) {
        XyzFullTimeEmployee* e = new XyzFullTimeEmployee(bName, id, bStatus, bGender, bDob, bDoj, bLeaves);
        return e;
    } else if (bType == EmpType::Contractor) {
        XyzContractorEmployee* e = new XyzContractorEmployee(bName, id, bStatus, bGender, bDob, bDoj, bDol, bAgency);
        return e;
    } else { // Intern
        XyzInternEmployee* e = new XyzInternEmployee(bName, id, bStatus, bGender, bDob, bDoj, bDol, bCollege, bBranch);
        return e;
    }
}

XyzEmpBase* XyzEmployeeBuilder::buildResignedMinimal(XyzEmpBase* src) {
    if (!src) return nullptr;
    // create a copy with minimal fields as separate XyzEmpBase derived object. For simplicity use base class pointer with same derived type but copy minimal fields.
    // We'll create a XyzEmpBase object (using FullTime class as generic container with NA for leaves) OR reuse src type but set fields minimal.
    // Here: create new XyzEmpBase-like object by creating a new XyzEmpBase derived container: use XyzEmpBase by creating a "FullTime" with NA fields but type set to src->getType() [id will keep type suffix].
    // Simpler: if src is FullTime -> create FullTime with leaves 0 and set DOL; Contractor/Intern -> create corresponding type but only preserve the necessary fields.

    EmpType t = src->getType();
    std::string name = src->getName();
    std::string id = src->getId();
    EmpStatus status = EmpStatus::RESIGNED;
    Gender g = src->getGender();
    std::string dob = src->getDob();
    std::string doj = src->getDoj();
    std::string dol = src->getDol();

    if (t == EmpType::FullTime) {
        return new XyzFullTimeEmployee(name, id, status, g, dob, doj, 0);
    } else if (t == EmpType::Contractor) {
        // agency unknown; set to None
        return new XyzContractorEmployee(name, id, status, g, dob, doj, dol, Agency::None);
    } else {
        return new XyzInternEmployee(name, id, status, g, dob, doj, dol, College::None, Branch::UnknownBranch);
    }
}
