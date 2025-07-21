#include <string>
#include <vector>
#pragma once

using namespace std;

struct Node {
    string name;
    string ufid;
    int height;
    Node* left;
    Node* right;

    Node(string name, string ufid) {
        this->name = name;
        this->ufid = ufid;
        this->height = 1;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class AVLTree {
private:
    bool searchResult = false;
    Node* root = nullptr;
    Node* insertHelper(Node* root, string name, string ufid);
    void searchHelperName(Node *root, const string &name, vector<string> &res);
    void searchHelperUFID(Node *root, const string &str, vector<string> &resID);
    Node* rotate(Node* root, string rotateLR);
    long long getBalance(Node *root);
    int UpdateHeight(Node *root);
    Node* removeIDHelper(Node *root, int ufid);
    int NodeCounter(Node* root);
    vector<string> Inorder(Node *root, vector<string> &res);
    vector<string> Postorder(Node *root, vector<string> &res);
    vector<string> Preorder(Node *root, vector<string> &result);
    int levelCount(Node *root);
    vector<string> removeInorderHelper(Node *root, int n, int &counter, vector<string> &result);
    bool searchHelperUFIDforInsert(Node *root, const string &str);

public:
    void insert(string name, string ufid);
    bool search(const string &target);
    bool removeID(string ufid);
    vector<string> getInorder();
    vector<string> getPostorder();
    vector<string> getPreorder();
    int getlevelCount();
    bool removeInorderN(string n);
    int getNodeCounter();
    void deleteNode(Node *root);
    ~AVLTree() {
        //Use a postorder traversal to delete nodes since each node
        //will onl get visited once with a postorder traversal
        deleteNode(root);
    };
};

