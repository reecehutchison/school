/*
* Reece Hutchison
* Program 1 - Lab assignment 3
* cs2010 - Franco Carlnacci
*/

#include <iostream>

#define EXIT_CODE 0

using namespace std;

// create alisas
typedef int* VEC;
typedef VEC* MATRIX;

int main() {

    cout << "--- Aliases Program ---" << endl << endl;

    // initialize variables
    int a=5;
    VEC v=&a;
    MATRIX m=&v;

    // note: use two derefrences oporators since m is a 
    //       pointer to a pointer...
    cout << "V : " << *v << endl;
    cout << "M : " << **m << endl << endl;
    cout << "--- Done ---" << endl;

    return EXIT_CODE;
}
