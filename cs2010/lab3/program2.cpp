/*
* Reece Hutchison
* Program 2 - Lab assignment 3
* cs2010 - Franco Carlnacci
*/


#include <iostream>

#define EXIT_CODE 0

using namespace std;

int main() {

    cout << "--- Addition Program ---" << endl << endl;

    double x, y;

    // process input into x and y
    cout << "Enter a value for x : ";
    cin >> x;

    cout << "Enter a value for y : ";
    cin >> y;

    // initialize pointers to x and y
    double *a=&x;
    double *b=&y;

    // add the values using their pointers --> use dereference oporator
    const double sum=(*a)+(*b);

    // display results
    cout << endl;
    cout << "x : " << *a << endl;
    cout << "y : " << *b << endl;
    cout << endl << "x + y : " << sum << endl << endl;
    cout << "--- Done ---" << endl;

    return EXIT_CODE;
}
