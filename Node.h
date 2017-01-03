#ifndef NODE_H
#define NODE_H
#include <sstream>
#include <iostream>
#include <cmath>

class Node {
	private:
		int coeff, power;
		Node* left;
		Node* right;
		
		int gcd(int, int);
		std::string simplify(int, int);
	
	public:
		Node();
		Node(int, int);
		Node(Node&);
		
		int incr_coeff(int incr) { coeff += incr; }
		int get_power() { return power; }
		Node* get_left() { return left; }
		Node* get_right() { return right; }
		void set_left(Node* l) { left = l; }
		void set_right(Node* r) { right = r; }
		
		char sign();
		std::string integral();
		double definite(int, int);
};

#endif