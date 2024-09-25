/*
* Reece Hutchison
* Program 1 - Lab assignment 3
* cs2010 - Franco Carlnacci
*/


#include <iostream>
#include <vector>

using namespace std;

extern const int QUARTER;
extern const int DIME;
extern const int NICKEL;
extern const int PENNY;

extern void display_change(int price);

int main() {

    // program definition
    cout << "------------------------------------------------------------------" << endl;
    cout << "This program finds the change owed from an amount of pennies 0-100" << endl << endl;


    // handle std input(s)
    vector<int> prices;
    cout << "Enter number of change calculations : ";
    int n;                     // note: input size must be specified as the
    cin >> n;                  //       first argument when running the exe...


    cout << endl;
    for(int i=0; i<n; ++i) {
        int tmp;
        cout << "Enter amount of change (0-100) : ";
        cin >> tmp;
        prices.push_back(tmp);
    }

    cout << "------------------------------------------------------------------" << endl << endl;

    // display result(s) to std output
    for(int i=0; i<n; ++i) {
        int price=prices[i];
        display_change(price);
    }

    cout << "------------------------------------------------------------------" << endl;

    return 0;
}
