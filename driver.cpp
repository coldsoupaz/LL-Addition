#include <iostream>
#include "multi_digit_addition.h"
using namespace std;

int main() {
	// example testing code here
    Number left = Number();
    left.insertBack(1);
    left.insertBack(2);
    left.insertBack(3);    // left: 123

    Number right = Number();
    right.insertBack(4);
    right.insertBack(5);
    right.insertBack(6);   // right: 456

    cout << left.add(right) << endl; // output: 579
    return 0;
}
