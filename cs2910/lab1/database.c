#include "database.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>


#define STUDENT_FILE "student.data"
#define STRING_LENGTH 99


void init_ncurses() {
    initscr();
    cbreak();                // disables line buffering
    noecho();               // turns of echoing of typed charecters
    keypad(stdscr, TRUE);  // enables keypad input 
    curs_set(0);          // disable cursor
    return;
}

void display_debug_info(int ch) {
    mvprintw(27, 3, "key: %c",ch);
    return;
}

// binary search tree stuff. 

struct Node* create_node( 
    const char id[STRING_LENGTH], 
    const char last_name[STRING_LENGTH], 
    const char first_name[STRING_LENGTH], 
    const char phone_number[STRING_LENGTH],
    const char email[STRING_LENGTH]
) {
    struct Node* new_node=(struct Node*)malloc(sizeof(struct Node));
    strcpy(new_node->id, id);
    strcpy(new_node->last_name, last_name);
    strcpy(new_node->first_name, first_name);
    strcpy(new_node->phone_number, phone_number);
    strcpy(new_node->email, email);
    new_node->left=NULL;
    new_node->right=NULL;

    return new_node; 
}

struct Node* insert_node(struct Node* root, struct Node* new_node) { 
    if(atoi(root->id)>=atoi(new_node->id))
        insert_node(root->left, new_node); 
    else
        insert_node(root->right, new_node);
    return root;  
}











