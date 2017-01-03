#include "Node.h"
using namespace std;

Node::Node() {
	coeff = 1;
	power = 1;
	left = nullptr;
	right = nullptr;
}

Node::Node(int c, int p) {
	coeff = c;
	power = p;
	left = nullptr;
	right = nullptr;
}

Node::Node(Node& node2) {
	coeff = node2.coeff;
	power = node2.power;
	left = node2.left;
	right = node2.right;
}

int Node::gcd(int a, int b) {
	int result;
	
	for (int i = 1; i <= a && i <= b; i++) {
		if (a % i == 0 && b % i == 0) {
			result = i;
		}
	}
	
	return result;
}

char Node::sign() {
	// The reason I am using a function like this is so it can be called by Tree, so I can easily avoid output like "4x + -3"
	if ((coeff > 0 && power + 1 > 0) || (coeff < 0 && power + 1 < 0)) {
		return '+';
	}
	
	else {
		return '-';
	}
}

string Node::simplify(int a, int b) {
	stringstream frac;
	
	if (b == 0) {
		throw string("Division by 0");
	}
	
	if (a == 0) {
		return "0";
	}
	
	if (a < 0) {
		a *= -1;
	}
	
	if (b < 0) {
		b *= -1;
	}
		
	int divisor = gcd(a, b);
	while (divisor > 1) {
		a /= divisor;
		b /= divisor;
		
		divisor = gcd(a, b);
	}

	if (b == 1) {
		frac << a;
		return frac.str();
	}
	
	frac << "(" << a << "/" << b << ")";
	return frac.str();
}

string Node::integral() {
	stringstream result;
	
	if (coeff == 0) {
		return "0";
	}
	
	if (simplify(coeff, power + 1) != "1") {
		result << simplify(coeff, power + 1);
	}
	
	if (power == 0) {
		result << "x";
	}
	
	else {
		result << "x^" << power + 1;
	}
	
	return result.str();
}

double Node::definite(int a, int b) {	
	return ((double) coeff / (power + 1)) * (pow(b, power + 1) - pow(a, power + 1));
}
