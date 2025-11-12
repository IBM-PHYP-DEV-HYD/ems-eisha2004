#ifndef ENUMS_H
#define ENUMS_H

// Employee Type
enum class EmpType { FullTime, Contractor, Intern, Unknown };

// Employee Status
enum class EmpStatus { ACTIVE, INACTIVE, RESIGNED };

// Gender Type
enum class Gender { MALE, FEMALE, OTHER };

// External Agencies
enum class Agency { Avengers, JusticeLeague, XMen, None };

// Colleges
enum class College { 
    IITDelhi, IITMumbai, IITKanpur, IITHyderabad, 
    NITWarangal, NITTiruchi, IIITHyderabad, None 
};

// Branches
enum class Branch { CSE, CSIT, ECE, UnknownBranch };

// Helper function — returns char for employee type
static inline char typeToChar(EmpType t) {
    switch (t) {
        case EmpType::FullTime:   return 'F';
        case EmpType::Contractor: return 'C';
        case EmpType::Intern:     return 'I';
        default:                  return 'X';
    }
}

// Optional helpers for printing (you’ll need them later)
static inline const char* statusToString(EmpStatus s) {
    switch (s) {
        case EmpStatus::ACTIVE:   return "Active";
        case EmpStatus::INACTIVE: return "Inactive";
        case EmpStatus::RESIGNED: return "Resigned";
        default:                  return "Unknown";
    }
}

static inline const char* genderToString(Gender g) {
    switch (g) {
        case Gender::MALE:   return "Male";
        case Gender::FEMALE: return "Female";
        case Gender::OTHER:  return "Other";
        default:             return "Unknown";
    }
}

#endif // ENUMS_H
