#include "FamilyTree.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <map>
#include <vector>
#include "ManagerUI.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;

typedef FamilyTree::FamilyMember FamilyMember;

int main() {
    ManagerUI ui(new FamilyTree());
    ui.InputLoop();
    return 0;
}
