#include <fstream>
#include "Node.h"
#include "Tree.h"
using namespace std;

int main() {
	ifstream integrals("integrals.txt");
	ofstream answers;
	answers.open("answers.txt");
	
	Tree tree;
	
	while (!integrals.eof()) {
		string line;
		getline(integrals, line);
		cout << "Processing line '" << line << "' ... " << endl;
		tree.fill(line); // Calls Tree::clear();

		cout << endl;
		answers << tree.integral();
	}
}