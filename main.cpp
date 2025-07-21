#include <iostream>
#include "AVL.h"
#include "helper.h"

using namespace std;

int main(){
	AVLTree* tree = new AVLTree();
	helper::instructionReader(tree);
	delete tree;
	return 0;
}
