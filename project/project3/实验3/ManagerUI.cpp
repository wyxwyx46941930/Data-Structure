#include "ManagerUI.hpp"
#include "FamilyTree.hpp"
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <memory>
#include <cstdlib>
#include <map>
void ManagerUI::PrintUI() 
{
    cout << "Menu" << endl
        << "1. insertWife" << endl
        << "2. insertChild" << endl
        << "3. updateMember" << endl
        << "4. deleteMember" << endl
        << "5. find" << endl
        << "6. printMembers" << endl
        << "7. count all member's amount" << endl 
        << "0. out" << endl ;
    cout << "Your choice:" ;
}

void ManagerUI::InputLoop() 
{
    int command = 0;
    while (!m_familytree_ptr->root) 
    {
        insertAncestor();
    }
    system("clear");
    PrintUI();
    while (cin >> command, !cin.eof() && command != 0) 
    {
        
        if (!m_familytree_ptr->root) 
        {
            cout << "The ancestor had gone ! The process has been over!" << endl;
            return;
        }
        switch(command) 
        {
            case 1:
            {
                insertWife(); 
                break;
            }

            case 2:
            {
                insertChild(); 
                break;
            }

            case 3:
            {
                updateMember(); 
                break;
            }

            case 4:
            {
                deleteMember(); 
                break;
            }

            case 5:
            {
                queryMember(); 
                break;
            }

            case 6:
            {
                printTree(); 
                break;
            }

            case 7:
            {
                statisticAnalyze(); 
                break;
            }
            default:
            {
                cout << "Enter Default" << endl; 
                break;
            }
        }
        while(1)
        {   
            cout << "please enter Y to continue:";
            char temp ;
            cin >> temp ;
            if(temp == 'Y')
            {
                break ;
            }
            else
            {
                continue ;
            }
        }
        system("clear") ;
        PrintUI();
    }
}

void ManagerUI::insertAncestor() {
    cout << "Welcome to your Family-Tree management system!" << endl ;
    cout << endl ;
    cout << endl ;
    cout << "Setting a ancestor" << endl;
    cout << "You should enter as this format:" 
         << "[name] [age] [pass/not pass](0/1)" << endl;
    string t_name;
    int t_age = 0;
    int t_int_is_dead = 0;
    cout << "Name:";
    cin >> t_name ;
    cout << "Age:" ;
    cin >> t_age ;
    cout << "Pass/not Pass:" ; 
    cin >> t_int_is_dead;
    m_familytree_ptr->insertWife(new FamilyMember(t_name, FamilyTree::Sex::boy, t_age, t_int_is_dead ? true:false) , nullptr);
}

void ManagerUI::insertWife() {
    cout << "@ insertWife" << endl
         << "You should enter as this format:" << endl
         << "[name] [age] [divorced/not divorced](0/1) [pass/not pass](0/1)" << endl;
    string t_name;
    int t_age = 0;
    int t_int_is_divorced, t_int_is_dead = 0;
    cout << "Name:";
    cin >> t_name ;
    cout << "Age:" ;
    cin >> t_age ;
    cout << "Divorced/not Divorced:";
    cin >> t_int_is_divorced ;
    cout << "Pass/not Pass:" ; 
    cin >> t_int_is_dead;
    auto newWife = new FamilyMember(t_name, FamilyTree::Sex::girl, t_age, t_int_is_dead ? true:false, t_int_is_divorced ? true:false);
    cout << "Please cin her [husband's name]" << endl;
    cout << "Husband's name:";
    cin >> t_name;
    auto query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
        return person->name == t_name;
    });
    if (query_res.size() == 0) {
        cout << "It's a error to find her husband" << endl;
        return;
    }
    FamilyMember *husband = nullptr;
    if (query_res.size() > 1)
        husband = handleMultiQueryResult(query_res);
    else
        husband = query_res[0];
    m_familytree_ptr->insertWife(newWife, husband);
}

void ManagerUI::insertChild() {
    cout << "@ insertChild" << endl
         << "Sex choice [0: female 1: male 2: unknown]" << endl
         << "You should enter as this format:" << endl
         << "[name] [sex] [age] [pass/not pass](0/1)" << endl;
    string t_name;
    int t_age = 0, t_int_sex = 0;
    int t_int_is_dead = 0;
    cout << "Name:";
    cin >> t_name ;
    cout << "Sex:" ;
    cin >> t_int_sex ;
    cout << "Age:" ;
    cin >> t_age ;
    cout << "Pass/not Pass:" ; 
    cin >> t_int_is_dead;
    auto newChild = new FamilyMember(t_name, IntToSex[t_int_sex], t_age, t_int_is_dead ? true:false);
    cout << "Please cin his or her [mother's name]" << endl;
    cout << "Mother's name:" ;
    cin >> t_name;
    auto query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
        return person->name == t_name;
    });
    FamilyMember *mother = nullptr;
    if (query_res.size() == 0) {
        cout << "It is a error to find his/her mother" << endl;
        return;
    }
    if (query_res.size() > 1)
        mother = handleMultiQueryResult(query_res);
    else
        mother = query_res[0];
    m_familytree_ptr->insertChild(newChild, mother);
}

void ManagerUI::updateMember() {
    cout << "@ updateMember" << endl
         << "Enter the member's name" << endl;
    string t_name;
    cout << "Name:";
    cin >> t_name;
    auto query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
        return person->name == t_name;
    });
    FamilyMember *member = nullptr;
    if (query_res.size() == 0) {
        cout << "It's a error to find this man" << endl;
        return;
    }
    if (query_res.size() > 1)
        member = handleMultiQueryResult(query_res);
    else
        member = query_res[0];
    cout << "Current member information:" << endl;
    printOneMember(member);
    cout << "Enter updated member information:" << endl;
    cout << "[name] [sex] [age] [pass/not pass](0/1) [divorced](female)" << endl;
    int t_age = 0, t_int_sex = 0, t_int_dead = 0, t_int_divorced = 0;
    cout << "Name:";
    cin >> t_name ;
    cout << "Sex:";
    cin >> t_int_sex ;
    cout << "Age:";
    cin >> t_age ;
    cout << "Dead/not Dead:" ;
    cin >> t_int_dead;
    if (member->sex == FamilyTree::Sex::girl) {
        cin >> t_int_divorced;
        member->divorced = t_int_divorced;
    } 
    member->name = t_name;
    member->sex = IntToSex[t_int_sex];
    member->age = t_age;
    member->dead = t_int_dead;
}

void ManagerUI::deleteMember() {
    cout << "@ deleteMember" << endl
         << "Enter the member's name" << endl;
    cout << "Name:" ;
    string t_name;
    cin >> t_name;
    auto query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
        return person->name == t_name;
    });
    FamilyMember *member = nullptr;
    if (query_res.size() == 0) {
        cout << "It's a error to find this member" << endl;
        return;
    }
    if (query_res.size() > 1)
        member = handleMultiQueryResult(query_res);
    else
        member = query_res[0];
    cout << "Current member information:" << endl;
    printOneMember(member);
    if(m_familytree_ptr->deleteMember([&](const FamilyMember* person) {
        return member == person;
    })) {
        cout << "He/She has been deleted" << endl;
    }
}

void ManagerUI::queryMember() {
    cout << "@ find" << endl
         << "Enter the information to find" << endl
         << "Choice: 0:name 1:sex 2:age 3:pass/not pass 4:divorced" << endl
         << "[Choice] [Value]" << endl;

    int condition = 0;
    cout << "Choice:";
    cin >> condition;

    vector<FamilyMember*> query_res;
    string t_name;
    int t_int_sex = 0;
    int t_age = 0;
    int t_int_dead;
    int t_int_divorced;

    switch (condition) {
        case 0:
        cout << "Name:" ;
        cin >> t_name;
        query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
            return person->name == t_name;
        });
        break;

        case 1:
        cout << "Sex:" ;
        cin >> t_int_sex;
        query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
            return person->sex == IntToSex[t_int_sex];
        });
        break;

        case 2:
        cout << "Age:"; 
        cin >> t_age;
        query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
            return person->age == t_age;
        });
        break;

        case 3:
        cout << "Dead/not Dead:" ;
        cin >> t_int_dead;
        query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
            return person->dead == t_int_dead ? true:false;
        });
        break;

        case 4:
        cout << "Divorced/not Divorced:";
        cin >> t_int_divorced;
        query_res = m_familytree_ptr->queryMember([&](const FamilyMember* person) -> bool {
            return person->divorced == t_int_divorced ? true:false;
        });
    }

    printMembers(query_res);
}

void ManagerUI::printTree() {
    FamilyTree::PrintMembers(m_familytree_ptr->root);
}

void ManagerUI::statisticAnalyze() {
    vector<FamilyMember*> query_res;
    query_res = m_familytree_ptr->queryMember([&](const FamilyMember *person) -> bool {
        return true;
    });
    cout << "The total number is: " << query_res.size() << endl;
}

FamilyMember* ManagerUI::handleMultiQueryResult(vector<FamilyMember*> &res) {
    cout << "The total number is " << res.size() << endl;
    for (int i = 0; i < res.size(); ++i) {
        cout << "Your choice is " << i << endl;
        printOneMember(res[i]);
    }
    cout << "Please choose a member" << endl;
    int select = 0;
    while (cin >> select, select < 0 || select >= res.size()) {
        cout << "Please enter the right number" << endl;
    }
    return res[select];
}
