#include "XyzMenu.H"
#include "Utils.H"   // <-- add this so you can call seedRandom()

int main() {
    seedRandom();    // <-- this line ensures real randomness
    XyzMenu menu;
    menu.displayMainMenu();
    return 0;
}
