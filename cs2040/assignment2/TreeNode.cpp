#include <string>
#include <iostream>

using namespace std; 

class TreeNode {
public:  // each nodes values below!
char key;
string code; 
TreeNode* left;
TreeNode* right; 

// must create nodes by passing char for key and string for code
TreeNode(char ch, string code): key(ch), code(code), left(nullptr), right(nullptr){}; 

/* 
Module name: TreeNode
Author: Reece Hutchison
Date: Thu Mar 20, 2025
Description: Will insert a new node into tree, based off of 
    parameters given. If nullptr is passed as the root, instead 
    of a pointer to the node acting as root in the tree, then 
    a new node will be created, and be returned which will act as 
    a new root to a new tree. 
Parameters: root should either be a pointer to a TreeNode object
    acting as a root for a tree, or should be nullptr which will
    create a new tree. Key is a char which acts as a key for the 
    node (examples: a, b, c). Code will be the morse code equivalent
    of the key. 
Output: a pointer to the root of the tree where the insert is taking 
    place. 
*/
static TreeNode* insert(TreeNode* root, char key, string code) {
    // if nullptr is passed to root, this makes a new tree!
    if(!root) {
        return new TreeNode(key, code); 
    }
    TreeNode* node=new TreeNode(key, code);
    TreeNode* curr=root;
    TreeNode* prev=nullptr; 
    int n=code.size(); 
    int i=0;
    while(i<n&&curr) { // traverse tree in ladder fashion to find
        prev=curr;     // insert location. 
        if(code[i]=='*') 
            curr=curr->left;
        else
            curr=curr->right;
        ++i; 
    }
    if(code[i-1]=='*')    // insert node in location
        prev->left=node; 
    else
        prev->right=node; 
    return root; 
}

/* 
Module name: TreeNode
Author: Reece Hutchison
Date: Thu Mar 20, 2025
Description: Will print a tree in-order based off of the given root. 
Parameters: A pointer to the TreeNode acting as the root of the tree
    that you want to print. 
Output: Does not return anything! 
*/
static void print(TreeNode* node) {
    if(!node)
        return; 
    print(node->left);
    cout << node->key << " "; // in order
    print(node->right);
}

/* 
Module name: TreeNode
Author: Reece Hutchison
Date: Thu Mar 20, 2025
Description: Based off of the key given in the parameters, the 
    function searches the tree and returns the morse code associated
    with the key given. If no associated code is found it will give a
    "?". 
Parameters: Node is the root of the tree that you want to search.
    Key is the key you want the morse code to. 
Output: Returns the morse code associated with the key.  
*/
static string getCode(TreeNode* node, char key) {
    if(!node)
        return "?";  // returns ? if node is null
    if(node->key==key)
        return node->code; // returns code if key matches node key
    string leftResult=getCode(node->left, key);
    if(leftResult!="?")
        return leftResult; // if left result is not ?, then it is found
    return getCode(node->right, key); // else check right side. 
}

/* 
Module name: TreeNode
Author: Reece Hutchison
Date: Thu Mar 20, 2025
Description: Will return the key associatedwith the given morse 
code in a tree.  
Parameters: Node is a pointer to a TreeNode acting as the tree's root.
    Code is the morse code that you want the key for. 
Output: Returns the key for that specific morse code. Note: it will 
    return ? if code is not found. 
*/
static char getKey(TreeNode* node, string code) {
    if(code=="?")
        return '?';
    int n=code.size();
    for(int i=0; i<n; ++i) { // goes down based off of * or -
        if(code[i]=='*')
            node=node->left;
        else
            node=node->right; 
    }
    return node->key; // when morse code ends, then that must  
}                     // be the location wanted, so returns key.
};