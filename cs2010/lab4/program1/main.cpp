//
//  main.cpp
//  program_1
//
//  Created by Reece Hutchison on 2024-10-01.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

typedef int credit;

using namespace std;

void playGame();
void roll_dice(int& a, int& b, int& c);
void print_one();
void print_two();
void print_three();
void print_four();
void print_five();
void print_six();
void print_dice(int a, int b);
void pause();
void win(int wager);
void print_roles(int a, int b);
void lose(int wager);
void point(int target, int wager);

credit players_credit=100;

// ----------- FRANCO'S MAIN FUNCTION -------------

int main( ) {
  char ans;
  bool done = false;
  while ( ! done ) {
         playGame();   // YOU MUST WRITE THIS FUNCTION
         cout << " Play again (y/n) ? ";
         cin >> ans;
         if ( ans == 'n' || ans == 'N') done = true;
             else done = false;
  }
  return 0;
}

// ------------------------------------------------
 

void playGame() {

    int wager;
    int dice_a=0;
    int dice_b=0;
    int roll=0;
    bool valid_wager=false;
    bool second_go=false;
    
    cout << "--- craps --- " << endl << endl;
    
    cout << "You have " << players_credit << " credits. How much do you wager? ";
    cin >> wager;
    while(!valid_wager) {
        if(second_go) {
            cout << endl << "how much do you wager? ";
            cin >> wager;
        }
        if(wager<=players_credit&&wager>-1&&wager!=0) {
            valid_wager=true;
        } else
            cout << "your wager exceeds your balance, or is invalid. try again." << endl;
        second_go=true;
    
    }
    
    cin.ignore();
    cout << endl;
    
    pause();
    roll_dice(dice_a, dice_b, roll);
    print_dice(dice_a, dice_b);
    print_roles(dice_a, dice_b);
    cout << endl;
    
    if(roll==7||roll==11)
        win(wager);
    else if(roll==2||roll==3||roll==12)
        lose(wager);
    else
        point(roll, wager);
    
    if(players_credit<1) {
        cout << endl << "you are out of credits - game over!"<< endl;
        players_credit=100;
    }
    /*
     rules :
     if 7 or 11 win
     if 2, 3 or 12 lose
     if 4, 5, 6, 8, 9, or 10 ... go until get the same number again to win or lose if 7
     */
}

void roll_dice(int& a, int& b, int& c) {
    srand((int)time(0));
    b=1+(rand()%6);
    a=1+(rand()%6);
    c=a+b;
}

void print_one() {
    cout << " _____ " << endl;
    cout << "|     |" << endl;
    cout << "|  *  |" << endl;
    cout << "|     |" << endl;
    cout << " ----- " << endl;
}

void print_two() {
    cout << " _____ " << endl;
    cout << "| *   |" << endl;
    cout << "|     |" << endl;
    cout << "|   * |" << endl;
    cout << " ----- " << endl;

}

void print_three() {
    cout << " _____ " << endl;
    cout << "|   * |" << endl;
    cout << "|  *  |" << endl;
    cout << "| *   |" << endl;
    cout << " ----- " << endl;

}

void print_four() {
    cout << " _____ " << endl;
    cout << "| * * |" << endl;
    cout << "|     |" << endl;
    cout << "| * * |" << endl;
    cout << " ----- " << endl;

}

void print_five() {
    cout << " _____ " << endl;
    cout << "| * * |" << endl;
    cout << "|  *  |" << endl;
    cout << "| * * |" << endl;
    cout << " ----- " << endl;

}

void print_six() {
    cout << " _____ " << endl;
    cout << "| * * |" << endl;
    cout << "| * * |" << endl;
    cout << "| * * |" << endl;
    cout << " ----- " << endl;
}

void print_dice(int a, int b) {
    // print first dice
    if(a==1)
        print_one();
    else if(a==2)
        print_two();
    else if(a==3)
        print_three();
    else if(a==4)
        print_four();
    else if(a==5)
        print_five();
    else if(a==6)
        print_six();
    else
        cout << endl << " --- ERROR --- " << endl;
    //print second dice
    if(b==1)
        print_one();
    else if(b==2)
        print_two();
    else if(b==3)
        print_three();
    else if(b==4)
        print_four();
    else if(b==5)
        print_five();
    else if(b==6)
        print_six();
    else
        cout << endl << " --- ERROR --- " << endl << endl;
    cout << endl;
}

void pause() {
    cout << "press ENTER to roll...";
    cin.get();
    cout << endl;
}

void win(int wager) {
    int credits=wager;
    players_credit+=credits;
    cout << "player wins" << endl;
    cout << "you won " << credits << " credits. your new balance is " << players_credit << " credits." << endl << endl;
}

void print_roles(int a, int b) {
    cout << "player rolled " << a << " + " << b << " = " << a+b << endl;
}

void lose(int wager) {
    players_credit-=wager;
    cout << "player loses" << endl;
    cout << "you lost " << wager << " credits. your new balance is " << players_credit << " credits." << endl << endl;
}

void point(int target, int wager) {
    int dice_a=0;
    int dice_b=0;
    int roll=0;
    cout << "point is " << target << endl << endl;
    while(1) {
        pause();
        roll_dice(dice_a, dice_b, roll);
        print_dice(dice_a, dice_b);
        print_roles(dice_a, dice_b);
        cout << endl;
        if(roll==target) {
            win(wager);
            break;
        }
        else if(roll==7) {
            lose(wager);
            break;
        }
    }
}
