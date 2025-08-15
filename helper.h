#include "AVL.h"
#pragma once
#include <string>
#include <vector>
using namespace std;

class helper {
public:
    static string functionCalled;
    static string next;
    static string parameterOne;
    static string next2;
    static string parameterTwo;
    static bool verifyID(string verifyThis);
    static bool verifyName(string verifyThis);
    static bool verifyKey(string verifyThis);
    static void testResult(bool result);
    static void printResult(const string& result);
    static void printTraversal(vector<string> res);
    static void instructionReader(AVLTree* tree);
};
