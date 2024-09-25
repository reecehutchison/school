#include <iostream>

using namespace std;

// values of the coins

const int QUARTER=25;

const int DIME=10;

const int NICKEL=5;

const int PENNY=1;

// display change

void display_change(int price) {

    int hold=price;
    int quarter_count=0;
    int dime_count=0;
    int nickel_count=0;
    int penny_count=0;

    //find coin amounts
    while(price>0) {
        if(price>=QUARTER) {
            ++quarter_count;
            price-=QUARTER;
        } else if(price>=DIME) {
            ++dime_count;
            price-=DIME;
        } else if(price>=NICKEL) {
            ++nickel_count;
            price-=NICKEL;
        } else {
            ++penny_count;
            price-=PENNY;
        }
    }

    //display coins
    cout << "Change in pennies : " << hold << endl;
    cout << " --- Coins ---" << endl;
    cout << "Quarter(s) : " << quarter_count << endl;
    cout << "Dime(s)    : " << dime_count << endl;
    cout << "Nickel(s)  : " << nickel_count << endl;
    cout << "Penny(s)   : " << penny_count << endl << endl;
}
