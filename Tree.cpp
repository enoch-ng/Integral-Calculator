#include "Tree.h"
using namespace std;

Tree::Tree() {
	definite = false;
	lower_bound = 0;
	upper_bound = 0;
	root = nullptr;
}

Tree::Tree(Node* node) {
	definite = false;
	lower_bound = 0;
	upper_bound = 0;
	root = node;
}

Tree::~Tree() {
	clear();
}

void Tree::insert_from(Node* parent, int c, int p) {
	// Recursive function that searches for the correct position to insert the node, which can be called by Tree::insert to start the process.
	// If a node of the specified power already exists, we should not insert a new one. Instead, we should edit the existing one.
	if (p < parent->get_power()) {
		if (parent->get_left())
			insert_from(parent->get_left(), c, p);
		else
			parent->set_left(new Node(c, p));
	}
	
	else if (p > parent->get_power()) {
		if (parent->get_right())
			insert_from(parent->get_right(), c, p);
		else
			parent->set_right(new Node(c, p));
	}
	
	else {
		parent->incr_coeff(c);
		cout << "A term with that power already exists -- combining ... " << endl;
	}
}

void Tree::insert(int c, int p) {
	if (!root) {
		root = new Node(c, p);
	}
	
	else {
		insert_from(root, c, p);
	}
}

void Tree::clear() {
	// Since we will only use one Tree in the program, we need a function which will clear the Tree to make it reusable.
	// This will be done recursively, by going down each path of the Tree, and creating new "subtrees" and calling the clear() function on them.
	if (root) {
		if (root->get_left()) {
			Tree left_subtree(root->get_left());
			left_subtree.clear();
		}
		
		if (root->get_right()) {
			Tree right_subtree(root->get_right());
			right_subtree.clear();
		}
	
		cout << "Deleting node ... " << endl;
		delete root;
	}
	
	root = nullptr;
}

void Tree::fill(string line) {
	clear();
	
	stringstream ss;
	ss << line;
	
	if (ss.peek() == '|') {
		cout << "Analyzing indefinite integral ... " << endl;
		definite = false;
		ss.ignore();
		ss.ignore();
	}
	
	else {
		cout << "Analyzing definite integral ... " << endl;
		definite = true;
		
		ss >> lower_bound;
		cout << "Lower bound: " << lower_bound << endl;
		ss.ignore();
		ss >> upper_bound;
		cout << "Upper bound: " << upper_bound << endl;	
		ss.ignore();
	}
	
	int coeff;
	int power;
	
	while (ss.peek() != 'd') {
		if (ss.peek() == 'x') {
			coeff = 1;
			ss.ignore();
			// If the next character is ^, then the term has power other than 1. Otherwise, the term is power 1.
			// This is true even if the term is the last in the expression.
			if (ss.peek() == '^') {
				ss.ignore();
				ss >> power;
			}
			
			else {
				power = 1;
			}
			
			cout << "Encountered term " << coeff << "x^" << power << endl;
			insert(coeff, power);
		}
		
		else if (ss.peek() == '-') {
			ss.ignore();
			
			while (ss.peek() == ' ') {
				ss.ignore();
			}
			
			if (ss.peek() == 'x') {
				coeff = -1;
				ss.ignore();
				// If the next character is ^, then the term has power other than 1. Otherwise, the term is power 1.
				// This is true even if the term is the last in the expression.
				if (ss.peek() == '^') {
					ss.ignore();
					ss >> power;
				}
				
				else {
					power = 1;
				}
			}
			
			else if (ss.peek() >= '1' && ss.peek() <= '9') {
				ss >> coeff;
				coeff *= -1;
				if (ss.peek() == 'x') {
					ss.ignore();
					// If the next character is ^, then the term has power other than 1. Otherwise, the term is power 1.
					// This is true even if the term is the last in the expression.
					if (ss.peek() == '^') {
						ss.ignore();
						ss >> power;
					}
					
					else {
						power = 1;
					}
				}
				
				else {
					power = 0;
				}
			}
			
			cout << "Encountered term " << coeff << "x^" << power << endl;
			insert(coeff, power);
		}
		
		else if (ss.peek() >= '1' && ss.peek() <= '9') {
			// It is necessary to allow 1 as a valid character in case the coefficient is 10
			ss >> coeff;
			if (ss.peek() == 'x') {
				ss.ignore();
				// If the next character is ^, then the term has power other than 1. Otherwise, the term is power 1.
				// This is true even if the term is the last in the expression.
				if (ss.peek() == '^') {
					ss.ignore();
					ss >> power;
				}
				
				else {
					power = 1;
				}
			}
			
			else {
				power = 0;
			}
			
			cout << "Encountered term " << coeff << "x^" << power << endl;
			insert(coeff, power);
		}
		
		else if (ss.peek() == ' ' || ss.peek() == '+') {
			ss.ignore();
		}
		
		else {
			cout << "Unexpected character '" << ss.peek() << "' encountered" << endl;
			break;
		}
	}

	cout << endl;
}

double Tree::integral_from(Node* node, bool rightmost, double sum, stringstream& ss) {
	if (node) {
		sum = integral_from(node->get_right(), rightmost, sum, ss);
		
		if (!rightmost || node->get_right()) {
			// Then the node is not the very first one that will be printed
			ss << ' ' << node->sign() << ' ';
		}
		
		else if (node->sign() == '-') {
			ss << node->sign();
		}
		
		if (definite) sum += node->definite(lower_bound, upper_bound);
		ss << node->integral();
		
		sum = integral_from(node->get_left(), false, sum, ss);
	}
	
	return sum;
}

string Tree::integral() {
	stringstream ss;
	double def_intrg = integral_from(root, true, 0, ss);
	// This variable is only used at most once, but it is necessary if the integral is definite, in order to format things nicely
	if (definite) {
		ss << ", " << lower_bound << '|' << upper_bound << " = " << setprecision(3) << fixed << def_intrg << endl;
	}
	
	else {
		ss << " + C" << endl;
	}
	
	return ss.str();
}
