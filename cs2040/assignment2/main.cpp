#include "TreeNode.cpp" // my treenode file!!!

#include <iostream> // standard lib files. 
#include <string>
#include <vector>
#include <fstream>

using namespace std; 

void parse(TreeNode* root, string textfile); // functions used in main
vector<string> getWords(string str);

int DEBUG=0; // set to 1 for debugging on, 0 for off


/* 
Module name: main
Author: Reece Hutchison
Date: Thu Mar 20, 2025
Description: The entry point for my Morse code program. It will 
    parse a text file holding keys and values into a tree. Then 
    based off of user input, will encode the message they put in,
    and then will decode the message as well. This is done by searching
    the tree for the keys and the codes that match the users message. 
Parameters: Nothing. 
Output: Will display the results of the program in the terminal, aka
    output it to the standard output stream. 
*/
int main() {

    cout << ">";

    TreeNode* root=TreeNode::insert(nullptr, ' ', ""); // creates new tree
    parse(root, "codes.txt"); // parses values into tree

    // will print the tree in order, for debugging purposes!
    if(DEBUG) {
        TreeNode::print(root); 
        cout << "\n"; 
    }

    // get input from user on what message they want!!
    cout << "\nMorse Code Program (press enter twice when done message)\n";
    cout << "Enter a message: ";
    vector<string> lines; 
    string line; 
    while (getline(cin, line)) {
        if(line.empty()) {
            cin.setstate(ios::eofbit); // will end the input(acts like ctrl d)
            break;
        } 
        lines.push_back(line); // adds line to vector
    }
    if(lines.size()<1) { // just checks if vector is empty, so no out of bounds
        cout << "\nenter a message next time!!!\n>\n";
        return 0; 
    }  
    vector<string> input=getWords(lines[0]); // input stores words
    vector<string> codeWords; // stores morse codes

    cout << "Coded message: " << endl; // prints morse code
    int n=input.size();                 // and also fills codeWords
    for(int i=0; i<n; ++i) {
        string curr=input[i];
        int m=curr.size();
        for(int j=0; j<m; ++j) {
            string val=TreeNode::getCode(root, tolower(curr[j])); 
            cout << val << " "; 
            codeWords.push_back(val); 
        }
    }
    cout << endl << "\nDecoded message: " << endl; 

    n=codeWords.size(); // prints keys (aka words) based off of codes. 
    for(int i=0; i<n; ++i) 
        cout << TreeNode::getKey(root, codeWords[i]); 
    cout << endl << ">" << endl; 

    
    return 0;
}

/* 
Module name: main
Author: Reece Hutchison
Date: Thu Mar 20, 2025
Description: Using fstream, the function will parse the file that
    holds all of the codes and keys, and then will populate the 
    tree. 
Parameters: Root is a pointer to the TreeNode that is acting as the 
    root of the tree. Textfile is a string that is the name of the
    text file holding the keys and the codes. 
Output: NOTHING!
*/
void parse(TreeNode* root, string textfile) {
     ifstream infile(textfile);
     if(!infile) {
         cerr << "The file doesn't exist!!\n";
         return;  
     }
     string line;
     while (getline(infile, line)) {
         if (line.empty()) 
             continue;
         char key=line[0];
         string code=line.substr(2); 
         root=root->insert(root, key, code);
     }
     infile.close();
}
/* 
Module name: main
Author: Reece Hutchison
Date: Thu Mar 20, 2025
Description: Takes the line gotten from the user entering the message, 
    and separates the words into the array that the function returns. 
Parameters: The str parameter is the line (aka the user message) that 
    the user put in. 
Output: A vector that holds each word and space that the user entered. 
*/
vector<string> getWords(string str) {
    vector<string> ans; 
    int n=str.size();
    for(int i=0; i<n; ++i) {
        string curr="";
        while(str[i]!=' '&&i<n) {
            curr.push_back(str[i]);
            ++i;
        }
        ans.push_back(curr);
        ans.push_back(" "); // pushes each time  there is a space!
    }
    return ans; 
} 