#include <iostream>
#include "cmds.h"

int main(int argc, char* argv[]) {
    IntSetController ctrl(std::cin, std::cout, std::cerr);
    return ctrl.process();
}
