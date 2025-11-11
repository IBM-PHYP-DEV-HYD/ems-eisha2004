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
    int t = randInt(0,2);
    if (t==0) bType = EmpType::FullTime;
    else if (t==1) bType = EmpType::Contractor;
    else bType = EmpType::Intern;

    // pick a name from the sample list
    auto names = sampleNames();
    int ni = randInt(0, (int)names.size()-1);
    std::ostringstream n;
    n << names[ni] << randInt(0,999); // add number to reduce duplication
    bName = n.str();

    bGender = randGender();
    bStatus = randStatus();
    bDob = makeRandomDOB();
    bDoj = makeRandomDOJ();
    bDol = "NA";

    if (bType == EmpType::FullTime) {
        bLeaves = randInt(0, MAX_LEAVES_FULLTIME);
    } else if (bType == EmpType::Contractor) {
        bAgency = randAgency();
        // DOL = DOJ + 1 year (naive)
        int y,m,d;
        if (sscanf(bDoj.c_str(), "%d-%d-%d", &y,&m,&d)==3) {
            y += 1;
            std::ostringstream dol; dol<<y<<"-"<<std::setw(2)<<std::setfill('0')<<m<<"-"<<std::setw(2)<<std::setfill('0')<<d;
            bDol = dol.str();
        }
    } else if (bType == EmpType::Intern) {
        bCollege = randCollege();
        bBranch = randBranch();
        int y,m,d;
        if (sscanf(bDoj.c_str(), "%d-%d-%d", &y,&m,&d)==3) {
            m += 6; if (m>12) { y += 1; m -= 12; }
            std::ostringstream dol; dol<<y<<"-"<<std::setw(2)<<std::setfill('0')<<m<<"-"<<std::setw(2)<<std::setfill('0')<<d;
            bDol = dol.str();
        }
    }
}

XyzEmpBase* XyzEmployeeBuilder::build() {
    if (bType == EmpType::Unknown) bType = EmpType::FullTime;
    std::string id = makeId(sSeq, bType);
    ++sSeq;
    if (bType == EmpType::FullTime) {
        return new XyzFullTimeEmployee(bName, id, bStatus, bGender, bDob, bDoj, bLeaves);
    } else if (bType == EmpType::Contractor) {
        return new XyzContractorEmployee(bName, id, bStatus, bGender, bDob, bDoj, bDol, bAgency);
    } else {
        return new XyzInternEmployee(bName, id, bStatus, bGender, bDob, bDoj, bDol, bCollege, bBranch);
    }
}

XyzEmpBase* XyzEmployeeBuilder::buildResignedMinimal(XyzEmpBase* src) {
    if (!src) return nullptr;
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
        return new XyzContractorEmployee(name, id, status, g, dob, doj, dol, Agency::None);
    } else {
        return new XyzInternEmployee(name, id, status, g, dob, doj, dol, College::None, Branch::UnknownBranch);
    }
}
