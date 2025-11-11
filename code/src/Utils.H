#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "Enums.H"

// small helpers used by builder/manager

static inline std::string zeroPad4(int n) {
    std::ostringstream oss;
    oss << std::setw(4) << std::setfill('0') << n;
    return oss.str();
}

static inline std::string makeId(int seq, EmpType type) {
    std::string id = "XYZ";
    id += zeroPad4(seq);
    id.push_back(typeToChar(type));
    return id;
}

// random helpers
static inline void seedRandom() { std::srand((unsigned)std::time(nullptr)); }
static inline int randInt(int lo, int hi) { return lo + (std::rand() % (hi - lo + 1)); }

static inline Gender randGender() {
    int v = randInt(0,2);
    return v==0?Gender::MALE:(v==1?Gender::FEMALE:Gender::OTHER);
}

static inline EmpStatus randStatus() {
    int v = randInt(0,9);
    if (v <= 6) return EmpStatus::ACTIVE;
    if (v <= 8) return EmpStatus::INACTIVE;
    return EmpStatus::RESIGNED;
}

static inline Agency randAgency() {
    int v = randInt(0,2);
    return v==0?Agency::Avengers:(v==1?Agency::JusticeLeague:Agency::XMen);
}

static inline College randCollege() {
    int v = randInt(0,6);
    switch(v) {
        case 0: return College::IITDelhi;
        case 1: return College::IITMumbai;
        case 2: return College::IITKanpur;
        case 3: return College::IITHyderabad;
        case 4: return College::NITWarangal;
        case 5: return College::NITTiruchi;
        default: return College::IIITHyderabad;
    }
}

static inline Branch randBranch() {
    int v = randInt(0,2);
    return v==0?Branch::CSE:(v==1?Branch::CSIT:Branch::ECE);
}

// random date helpers (format YYYY-MM-DD)
static inline std::string makeRandomDOB() {
    int year = randInt(1975, 2002);
    int month = randInt(1,12);
    int day = randInt(1,28);
    std::ostringstream oss; oss<<year<<"-"<<std::setw(2)<<std::setfill('0')<<month<<"-"<<std::setw(2)<<std::setfill('0')<<day;
    return oss.str();
}
static inline std::string makeRandomDOJ() {
    int year = randInt(2016, 2024);
    int month = randInt(1,12);
    int day = randInt(1,28);
    std::ostringstream oss; oss<<year<<"-"<<std::setw(2)<<std::setfill('0')<<month<<"-"<<std::setw(2)<<std::setfill('0')<<day;
    return oss.str();
}

static inline std::vector<std::string> sampleNames() {
    return {
        "Asha","Bharat","Chirag","Deepa","Esha","Farah","Gaurav","Hina","Ishaan","Jaya",
        "Kunal","Lata","Manish","Neha","Omkar","Pooja","Ravi","Sana","Tarun","Usha",
        "Vikram","Wahid","Yamini","Zubin","Kriti","Ria","Arjun","Siddharth","Priya","Nikhil"
    };
}

#endif // UTILS_H
