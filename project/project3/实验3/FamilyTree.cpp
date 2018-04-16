#include "FamilyTree.hpp"
#include <queue>
#include <vector>
#include <iostream>
using std::queue;
using std::vector;
using std::cout;
using std::endl;

int FamilyTree::FamilyMember::current_id = 0;

FamilyTree::FamilyTree() {
    root = NULL;
}

FamilyTree::~FamilyTree() {
    queue<FamilyMember*>q;
    if (root)
        q.push(root);
    while (!q.empty()) {
        FamilyMember* temp = q.front();

        if (temp->left) q.push(temp->left);
        if (temp->right) q.push(temp->right);

        q.pop();

        delete temp;
    }
}

void FamilyTree::insertChild(FamilyMember *person, FamilyMember *mother) {
    FamilyMember* p = mother;
    if (mother == NULL) {
        cout << "No Such a mother!" << endl;
        return;
    }
    while (p->right) p = p->right;
    p->right = person;
}


// when husband == null, insert ancestor
void FamilyTree::insertWife(FamilyMember *person, FamilyMember *husband) {
    if (husband) {
        FamilyMember* p = husband;
        while (p->left) {
            p = p->left;
        }
        p->left = person;
    } else {
        root = person;
    }
}

bool FamilyTree::deleteMember(function<bool(const FamilyMember *person)> filter) {
    int flag = 0;
    int flag1 = 0; // Judge whether she is a wife
    if (root != nullptr) {
        queue<FamilyMember*> q;
        q.push(root);
        while(!q.empty()) {
            FamilyMember* temp = q.front();
            if (temp->left != nullptr) q.push(temp->left);
            if (temp->right != nullptr) q.push(temp->right);
            if (filter(temp)) {
                flag = 1;
                int id = temp->id;
                if (temp->left != nullptr) {
                    queue<FamilyMember*> q1;
                    q1.push(temp->left);
                    while(!q1.empty()) {
                        FamilyMember* temp = q1.front();
                        if (temp->left != nullptr) q1.push(temp->left);
                        if (temp->right != nullptr) q1.push(temp->right);
                        //delete temp;
                        q1.pop();
                    }
                   temp->left = nullptr;
                }
                if (temp == root) {
                    root = temp->right;
                } else {
                    queue<FamilyMember*> q2;
                    q2.push(root);
                    while(!q2.empty()) {
                        FamilyMember* temp = q2.front();
                        if (temp->left != nullptr) q2.push(temp->left);
                        if (temp->right != nullptr) q2.push(temp->right);
                        if (temp->right != nullptr && temp->right->id == id) {
                            temp->right = temp->right->right;
                            break;
                        }
                        if (temp->left != nullptr && temp->left->id == id) {
                            flag1 = 1;
                        }
                        q2.pop();
                    }
                }
                if (flag1 == 0) {
                    delete temp;
                } else {
                    cout << "You can not delete wife" << endl;
                    return false;
                }
            }
            q.pop();
        }
    }
    if (flag == 0) {
        return false;
    } else {
        return true;
    }
}

vector<FamilyTree::FamilyMember*> FamilyTree::queryMember(function<bool(const FamilyMember *person)> filter) {
    vector<FamilyMember*> vec;
    if (root != nullptr) {
        queue<FamilyMember*> q;
        q.push(root);
        while(!q.empty()) {
            FamilyMember* temp = q.front();
            if (temp->left != nullptr) q.push(temp->left);
            if (temp->right != nullptr) q.push(temp->right);
            if (filter(temp)) {
                vec.push_back(temp);
            }
            q.pop();
        }
    }
    return vec;
}

bool FamilyTree::updateMember(function<bool(const FamilyMember *person)> filter, function<void(FamilyMember *person)> switcher) {
    vector<FamilyMember*> vec = queryMember(filter);
    int count = 0; // count the number of update object
    for(int i = 0; i < vec.size(); i++) {
        switcher(vec[i]);
        count++;
    }
    if (count != vec.size()) { // Judge whether it updates all the objects in vector
        return false;
    } else {
        return true;
    }
}

size_t FamilyTree::countMembers(function<bool(const FamilyMember *person)> filter) {
    return queryMember(filter).size();
}

void FamilyTree::PrintMembers(const FamilyMember* root, int printLevel, bool isLeft, vector<bool> blankIndex) {
    if (root != NULL) {
        // print
        if (isLeft) {  // wife
            if (root->sex == girl) { printLevel++; }  // printlevel
            if (root->left == NULL) {
                cout << " / ";
                cout << root->name;
                if (!root->divorced) {
                    cout << "[F]*";
                } else {
                    cout << "[F]--Divorced";
                }
                cout << endl;
                PrintMembers(root->right, printLevel, false, blankIndex);
            } else {
                for (int i = 0; i < printLevel-1; i++) {
                    if (blankIndex[i]) {
                        cout << "│  ";
                    } else {
                        cout << "   ";
                    }
                }
                if (root->left) {
                    cout << "├─ ";
                    while (blankIndex.size() > printLevel-1) { blankIndex.pop_back(); }
                    blankIndex.push_back(true);
                } else {
                    cout << "└─ ";
                    while (blankIndex.size() > printLevel-1) { blankIndex.pop_back(); }
                    blankIndex.push_back(false);  // blankindex
                }
                cout << root->name;
                if (!root->divorced) {
                    cout << "[F]*";
                } else {
                    cout << "[F]--Divorced";
                }
                cout << endl;
                PrintMembers(root->right, printLevel+1, false, blankIndex);
                if (root->left != NULL) {
                    if (root->left->left == NULL) {  // last wife
                        for (int i = 0; i < printLevel-1; i++) {
                            if (blankIndex[i]) {
                                cout << "│  ";
                            } else {
                                cout << "   ";
                            }
                        }
                        cout << "└─ " << root->left->name;
                        if (!root->left->divorced) {
                            cout << "[F]*";
                        }  else {
                            cout << "[F]--Divorced";
                        }
                        cout << endl;
                        while (blankIndex.size() > printLevel-1) { blankIndex.pop_back(); }
                        blankIndex.push_back(false);  // blankindex
                        PrintMembers(root->left->right, printLevel+1, false, blankIndex);
                    } else {
                        PrintMembers(root->left, printLevel-1, true, blankIndex);
                    }
                }
            }
        } else { // child
            if (printLevel > 0) {
                for (int i = 0; i < printLevel-1; i++) {
                    if (blankIndex[i]) {
                        cout << "│  ";
                    } else {
                        cout << "   ";
                    }
                }
                if (root->right) {
                    cout << "├─ ";
                    while (blankIndex.size() > printLevel-1) { blankIndex.pop_back(); }
                    blankIndex.push_back(true);
                } else {
                    cout << "└─ ";
                    while (blankIndex.size() > printLevel-1) { blankIndex.pop_back(); }
                    blankIndex.push_back(false);  // blankindex
                }
            }
            cout << root->name;
            if (root->sex == girl) {
                cout << "[F]";
            } else {
                cout << "[M]";
            }
            if (root->left == NULL) { cout << endl; }  // whether has a wife
            if (root->left != NULL) {
                if (root->left->left != NULL) {
                    cout << "(reMarriage)" << endl;
                }
            }
            PrintMembers(root->left, printLevel, true, blankIndex);
            PrintMembers(root->right, printLevel, false, blankIndex);
        }
    }
}
