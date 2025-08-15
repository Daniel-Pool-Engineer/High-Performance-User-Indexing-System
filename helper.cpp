#include <iostream>
#include <sstream>
#include "helper.h"

string helper::functionCalled;
string helper::next;
string helper::parameterOne;
string helper::next2;
string helper::parameterTwo;


bool helper::verifyID(string verifyThis) {
    if (verifyThis.length() != 8) {
        return false;
    }
    for (char c : verifyThis) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

bool helper::verifyName(string verifyThis) {
    for (char c : verifyThis) {
        if (c == ' ') {
            continue;
        }
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

bool helper::verifyKey(string verifyThis) {

	for (unsigned int i = 0; i < verifyThis.length(); i++) {
		if (!isdigit(verifyThis[i])) {
			return false;
		}
	}
    return true;
}

//Reference: https://cplusplus.com/reference/sstream/stringstream/str/
void helper::testResult(bool result) {
    std::stringstream ss;
    if (result) {
        ss<<"successful";
    }else {
        ss<<"unsuccessful";
    }
    cout<< ss.str()<<endl;
}

void helper::printResult(const string& result) {
    std::stringstream ss;
    ss<<result;
    cout<< ss.str()<<endl;
}

void helper::printTraversal(const vector<string> res) {
    stringstream ss;
    for (unsigned int i = 0; i <res.size(); i++) {
        ss<<res[i];
        if (i + 1 < res.size()) {
            ss <<", ";
        }
    }
    cout<<ss.str()<<"\n";
}

void helper::instructionReader(AVLTree *tree) {
    string line;
	getline(cin, line);
	int number = stoi(line);
	int i =0;

	while (i < number) {
		string instruction;
		getline(cin, instruction);
		stringstream inStream(instruction);

		getline(inStream, functionCalled, ' ');

		if (functionCalled == "insert") {
			getline(inStream, next, '"');
			getline(inStream, parameterOne,'"');
			getline(inStream, next2, ' ');
			getline(inStream, parameterTwo);
			if (verifyID(parameterTwo) && verifyName(parameterOne)) {
				tree->insert(parameterOne,parameterTwo);
			}else {
				helper::testResult(false);
			}
		}else if (functionCalled == "remove") {
			inStream >> parameterOne;
			if (verifyID(parameterOne)) {
				testResult(tree->removeID(parameterOne));
			}else {
				testResult(false);
			}
		}else if (functionCalled == "search") {
			inStream >> ws;
			char quote = inStream.peek();
			if (quote == '"') {
				inStream.get();
				getline(inStream, parameterOne,'"');
			}else {
				inStream >> parameterOne;
			}
			if (verifyID(parameterOne) || verifyName(parameterOne)) {
				//cout<<"Called Search Function"<<endl;
				tree->search(parameterOne);
			}else {
				testResult(false);
			}
		}else if (functionCalled == "printInorder") {
			printTraversal(tree->getInorder());
		}else if (functionCalled == "printPreorder") {
			printTraversal(tree->getPreorder());
		}else if (functionCalled == "printPostorder") {
			printTraversal(tree->getPostorder());
		}else if (functionCalled == "printLevelCount") {
			printResult(to_string(tree->getlevelCount()));
		}else if (functionCalled == "removeInorder") {
			inStream >> parameterOne;
			//cout << parameterOne << endl;
			if (verifyKey(parameterOne)) {
				//cout<<"passed"<<endl;
				//cout << parameterOne << endl;
				testResult(tree->removeInorderN(parameterOne));
			}else {
				testResult(false);
			}
		}else {
			testResult(false);
		}
		i++;
	}

}
