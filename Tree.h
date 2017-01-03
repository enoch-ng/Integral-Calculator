#ifndef TREE_H
#define TREE_H
#include <iomanip>
#include "Node.h"

class Tree {
	private:
		bool definite;
		int lower_bound, upper_bound;
		Node* root;
		
		void insert_from(Node*, int, int);
		double integral_from(Node*, bool, double, std::stringstream&);
		
	public:
		Tree();
		Tree(Node*);
		~Tree();
		
		void insert(int, int);
		void clear();
		void fill(std::string);
		std::string integral();
};

#endif