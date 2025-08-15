#include<sstream>
#include<queue>
#include "AVL.h"
#include "helper.h"

void AVLTree::insert(std::string name, std::string id) {
    if (!searchHelperIDforInsert(root, id)) {
        this->root = insertHelper(this->root, name, ufid);
        helper::testResult(true);
    }else {
        helper::testResult(false);
    }
}

bool AVLTree::searchHelperIDforInsert(Node *root, const std::string &str) {
    if (root == nullptr) {
        return false;
    }
    if (root->id == str) {
        return true;
    }

    if (searchHelperIDforInsert(root->left, str)) {
        return true;
    }
    return searchHelperIDforInsert(root->right, str);

}

Node *AVLTree::insertHelper(Node *root, std::string name, std::string id) {
    /*
     if the tree is null
        Replace empty tree with a new tree with the item at the root and return true.
    else if the item is equal to root. // this can be ignored since all ufids are unique meaning it can not be euqal.
        The item is already in the tree; return false.
    else if the item is less than root. data
        Recursively insert the item in the left subtree.
    else
        Recursively insert the item in the right subtree.
    */

    if(root == nullptr){
        return new Node(name, id);
    }
    if(stoi(id)< stoi(root->id)){
        root->left = insertHelper(root->left, name, id);
    }else if (stoi(id)> stoi(root->id)) {
        root->right = insertHelper(root->right, name, id);
    }

    //UPDATE HEIGHTS
    //If tree is right heavy
        //If tree's right subtree is left heavy
            // perform right left rotation and Update height
        //else
            //perform left rotation and update height
    //else if tree is left heavy
        //if tree's left subtree is right heavy
            //perform left right rotation and update height
        //else
            //perform right rotation and update height

    root->height = UpdateHeight(root);

    if (getBalance(root)>=2) {
        if (getBalance(root->left)>=0) {
            root= rotate(root, "right");
        }else {
            root = rotate(root, "LR");
        }
    }else if (getBalance(root)<=-2) {
        if (getBalance(root->right)<=0 ){
            root= rotate(root, "left");
        }else {
            root = rotate(root, "RL");
        }
    }
    return root;
}

bool AVLTree::search(const std::string &target) {
    /*
     if the tree is empty
        return null (target is not found)
     else if the target matches the root node's data
        return the data stored at the root node
     else if the target is less than the root node's data
        return the result of searching the left subtree of the root
     else
        return the result of searching the right subtree of the root
    */
    vector<string> res;
    vector<string> resID;
    if (isalpha(target[0])) {
        searchHelperName(root, target, res);

        if (!res.empty()) {
            for (unsigned int i=0; i<res.size(); i++) {
                helper::printResult(res[i]);
            }
            return true;
        }else {
            helper::testResult(false);
            return false;
        }

    }else if (isdigit(target[0])) {
        searchHelperID(root, target, resID);
        if (!resID.empty()) {
            for (unsigned int i=0; i<resID.size(); i++) {
                helper::printResult(resID[i]);
            }
            return true;
        }else {
            helper::testResult(false);
            return false;
        }
    }
    return false;
}

void AVLTree::searchHelperName(Node *root, const std::string &name, vector<string> &res) {
    if (root == nullptr) {
        return;
    }
    if (root->name == name) {
        searchResult = true;
        res.push_back(root->id);

    }

    searchHelperName(root->left, name, res);
    searchHelperName(root->right, name, res);

}

void AVLTree::searchHelperID(Node *root, const std::string &str, vector<string> &resID) {
    if (root == nullptr) {
        return;
    }
    if (root->id == str) {
        searchResult = true;
        resID.push_back(root->name);
    }
    if (stoi(str)< stoi(root->id)) {
        searchHelperID(root->left, str, resID);
    }else if (stoi(str)> stoi(root->id)) {
        searchHelperID(root->right, str, resID);
    }
}

Node* AVLTree::rotate(Node* root, std::string rotateLR) {
    if (rotateLR == "left") {
        Node* grandchild = root->right->left;
        Node* newParent = root->right;
        newParent->left = root;
        root->right = grandchild;
        UpdateHeight(root);
        UpdateHeight(newParent);
        return newParent;
    }else if (rotateLR == "right") {
        Node* grandchild = root->left->right;
        Node* newParent = root->left;
        newParent->right = root;
        root->left = grandchild;

        UpdateHeight(root);
        UpdateHeight(newParent);
        return newParent;
    }else if (rotateLR == "LR") {
        root->left = rotate(root->left, "left");
        return rotate(root, "right");
    }else if (rotateLR == "RL") {
        root->right = rotate(root->right, "right");
        return rotate(root, "left");
    }
    return root;
}

long long AVLTree::getBalance(Node *root) {
    //Balance Factor of x =  height (left subtree of x) - height (right subtree of x)
    if (root == nullptr) {
        return 0;
    }
    int leftSubtreeHeight = (root->left ? root->left->height : 0);
    int rightSubtreeHeight = (root->right ? root->right->height : 0);
    return leftSubtreeHeight - rightSubtreeHeight;


}

int AVLTree::UpdateHeight(Node *root) {
    //UPDATE Height
    //root->height = 1+ std::max(
    //root-> left ? root->left->height:0,
    //root->right ? root->right->height:0)
    if (root == nullptr) {
        return 0;
    }
    return root->height = 1 + std::max(
        (root->left ? root->left->height : 0),
        (root->right ? root->right->height : 0));
}

vector<string> AVLTree::getInorder() {
    vector<string> res;
    Inorder(root, res);
    return res;
}

vector<string> AVLTree::Inorder(Node *root, vector<string> &res) {
    /*
    if the tree is empty
       return
    else
        inorder traverse the left subtree
        visit the root
        inorder traverse the right subtree
    */

    if (root == nullptr) {
        return res;
    }else{
        Inorder(root->left, res);
        res.push_back(root->name);
        Inorder(root->right, res);
    }
    return res;
}

vector<string> AVLTree::Postorder(Node *root, vector<string> &res) {
    /*
     if the tree is empty
        return
     else
        postorder traverse the left subtree
        postorder traverse the right subtree
        visit the root
     */
    if (root == nullptr) {
        return res;
    }
    Postorder(root->left, res);
    Postorder(root->right, res);
    res.push_back(root->name);
    return res;
}

vector<string> AVLTree::getPostorder() {
    vector<string> res;
    Postorder(root,res);
    return res;
}


bool AVLTree::removeID(std::string ufid) {
    if (searchHelperIDforInsert(root, ufid)) {
        int target = stoi(ufid);
        this->root = removeIDHelper(root, target);
        return true;
    }
    return false;
}

Node *AVLTree::removeIDHelper(Node *root, int ufid) {
    //BST delete: provided with three cases 1) no child 2) one child
    if (root == nullptr) {
        return root;
    }
    if (ufid < stoi(root->id)) {
        root->left = removeIDHelper(root->left, ufid);
    }else if (ufid> stoi(root->id)) {
        root->right = removeIDHelper(root->right, ufid);
    }else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        }else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }else {
            Node* succ = root->right;
            while (succ->left != nullptr) {
                succ = succ->left;
            }
            root->id = succ->id;
            root->name = succ->name;

            root->right = removeIDHelper(root->right, stoi(succ->id));
        }
    }
    if (getBalance(root)>=2) {
        if (getBalance(root->left)>=0) {
            root= rotate(root, "right");
        }else {
            root = rotate(root, "LR");
        }
    }else if (getBalance(root)<=-2) {
        if (getBalance(root->right)<=0 ){
            root= rotate(root, "left");
        }else {
            root = rotate(root, "RL");
        }
    }
    return root;
}

int AVLTree::getlevelCount() {
    return levelCount(root);
}

int AVLTree::levelCount(Node *root) {
    queue<Node*> q;
    q.push(root);
    int level  = 0;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node* curr = q.front();
            q.pop();

            if(curr->left != nullptr){
                q.push(curr->left);
            }
            if(curr->right != nullptr){
                q.push(curr->right);

            }
        }
        level++;
    }
    return level;
}

bool AVLTree::removeInorderN(string n) {
    if (stoi(n) > getNodeCounter()) {;
        return false;
    }

    vector<string> result;
    int counter = 0;
    removeInorderHelper(root, stoi(n), counter, result);
    return true;
}

vector<string> AVLTree::removeInorderHelper(Node *root ,  int n, int& counter, vector<string>& result) {
    if (root == nullptr) {
        return result;
    }

    removeInorderHelper(root->left, n, counter, result);
    if (counter == n) {
        result.push_back(root->name);
        removeID(root->id);
        counter++;
        return result;
    }

    counter++;

    removeInorderHelper(root->right , n, counter,result);

    return result;
}

std::vector<std::string> AVLTree::getPreorder() {
    vector<string> result;
    Preorder(root, result);
    return result;
}

std::vector<std::string> AVLTree::Preorder(Node *root, vector<string>& result) {
    /*
     if the tree is empty
        return
     else
        visit the root
        preorder traverse the left subtree
        then traverse the right subtree
     */
    if (root == nullptr) {
        return result;
    }

    result.push_back(root->name);
    Preorder(root->left, result);
    Preorder(root->right, result);
    return result;
}

int AVLTree::getNodeCounter() {
    return NodeCounter(root);
}

int AVLTree::NodeCounter(Node *root) {
    if (root == nullptr) {
        return 0;
    }
    queue<Node*> q;
    q.push(root);
    int nodes = 0;

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        nodes++;
        if (curr->left != nullptr) {
            q.push(curr->left);
        }
        if (curr->right != nullptr) {
            q.push(curr->right);
        }
    }
    return nodes;
}



void AVLTree::deleteNode(Node *root) {
    if (root != nullptr) {
        deleteNode(root->left);
        deleteNode(root->right);
        delete root;
    }
}