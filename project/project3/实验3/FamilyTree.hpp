#ifndef FAMILY_TREE_HPP
#define FAMILY_TREE_HPP

#include <string>
#include <functional>
#include <vector>

using std::string;
using std::function;
using std::vector;

class FamilyTree {
 public:
  enum Sex {
    boy,
    girl,
    unknown
  };

  struct FamilyMember {
    static int current_id;
    int id;
    string name;
    Sex sex;
    int age;
    bool dead;
    bool divorced;
    FamilyMember *left;
    FamilyMember *right;
    FamilyMember(string t_name, Sex t_sex, int t_age, bool t_die = false, bool t_divorced = false, FamilyMember *t_left = nullptr, FamilyMember *t_right = nullptr) :  name(t_name), sex(t_sex), age(t_age), dead(t_die), divorced(t_divorced), left(t_left), right(t_right), id(current_id++) {}
  };

  FamilyTree();

  ~FamilyTree();

  void insertChild(FamilyMember *person, FamilyMember *mother);

  void insertWife(FamilyMember *person, FamilyMember *husband);

  bool deleteMember(function<bool(const FamilyMember *person)> filter);

  vector<FamilyMember*> queryMember(function<bool(const FamilyMember *person)> filter);

  bool updateMember(function<bool(const FamilyMember *person)> filter, function<void(FamilyMember *person)> switcher);

  size_t countMembers(function<bool(const FamilyMember *person)> filter);

  static void PrintMembers(const FamilyMember* root, int printLevel = 0, bool isLeft = false, vector<bool> blankIndex = {});

  FamilyMember *root;

};

#endif
