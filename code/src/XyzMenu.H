#ifndef XYZ_MENU_H
#define XYZ_MENU_H

#include "XyzEmployeeManager.H"
#include "XyzEmployeeBuilder.H"
#include <string>

class XyzMenu {
private:
    XyzEmployeeManager mManager;


    void displayAddEmployeeMenu();
    void displayEmployeeDetailsMenu();
    void displayOthersMenu();

    
    void addRandomEmployees();
    void addEmployeeByType();
    void removeEmployee();
    void addLeaves();
    void convertInternToFullTime();
    void searchById();
    void searchByName();

   
    int getValidatedIntInput(const std::string& prompt, int min, int max);
    std::string getValidatedStringInput(const std::string& prompt);

public:
    void displayMainMenu();
};

#endif
