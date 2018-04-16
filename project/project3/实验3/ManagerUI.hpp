#ifndef MANAGER_UI_HPP
#define MANAGER_UI_HPP

#include "FamilyTree.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>
#include <map>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::map;
using std::vector;

typedef FamilyTree::FamilyMember FamilyMember;

class ManagerUI 
{
  public:
    ManagerUI(FamilyTree *tree) : m_familytree_ptr(tree) {}
    void PrintUI();
    void InputLoop();
    void insertAncestor();
    void insertWife();
    void insertChild();
    void updateMember();
    void deleteMember();
    void queryMember();
    void printTree();
    void statisticAnalyze();
    FamilyMember* handleMultiQueryResult(vector<FamilyMember*> &res);

  private:
    std::shared_ptr<FamilyTree> m_familytree_ptr;
    std::map<FamilyTree::Sex, string> SexToString {
        {FamilyTree::Sex::boy, "Male"},
        {FamilyTree::Sex::girl, "Female"},
        {FamilyTree::Sex::unknown, "Unknown"}
    };
    std::map<int, FamilyTree::Sex> IntToSex {
        {0, FamilyTree::Sex::girl},
        {1, FamilyTree::Sex::boy},
        {2, FamilyTree::Sex::unknown}
    };
    void printOneMember(FamilyMember *member) {
        cout << "ID: " << member->id << endl
             << "Name: " << member->name << endl
             << "Sex: " << SexToString[member->sex] << endl
             << "Age: " << member->age << endl
             << "Pass/not Pass: " << (member->dead ? "Yes" : "Not") << endl;
        if (member->sex == FamilyTree::Sex::girl)
        cout << "Divorced: " << (member->divorced ? "Yes" : "Not") << endl;
    }
    
    void printMembers(const vector<FamilyMember*> vec) {
        for (int i = 0; i < vec.size(); ++i) {
            cout << "The final result " << i << "is :" << endl;
            printOneMember(vec[i]);
        }
    }
};

#endif
