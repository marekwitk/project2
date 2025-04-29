#include <cassert>
#include <vector>
#include <string>
#include <iostream>
#include "pasjans.h"

void test_poprawne_pole() {
    std::cout << "Test poprawne_pole()..." << std::endl;
    assert(poprawne_pole("KOL1"));
    std::cout << "KOL1 OK" << std::endl;
    assert(poprawne_pole("POM4"));
    std::cout << "POM4 OK" << std::endl;
    assert(poprawne_pole("CEL3"));
    std::cout << "CEL3 OK" << std::endl;
    assert(!poprawne_pole("KOL9"));
    std::cout << "KOL9 OK (negatywny)" << std::endl;
    assert(!poprawne_pole("XYZ1"));
    std::cout << "XYZ1 OK (negatywny)" << std::endl;
}

void test_kombinacja() {
    std::cout << "Test kombinacja()..." << std::endl;
    std::vector<int> dobra = { 25, 11 }; 
    std::vector<int> zla = { 3, 4 };   
    assert(poprawna_kombinacja(dobra));
    std::cout << "poprawna_kombinacja(dobra) OK" << std::endl;
    assert(!poprawna_kombinacja(zla));
    std::cout << "poprawna_kombinacja(zla) OK (negatywny)" << std::endl;
}

int main() {
    test_poprawne_pole();
    test_kombinacja();
    std::cout << "Wszystkie testy zakończone sukcesem!" << std::endl;
    return 0;
}
