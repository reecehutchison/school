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
    char id[STRING_LENGTH], 
    char last_name[STRING_LENGTH], 
    char first_name[STRING_LENGTH], 
    char phone_number[STRING_LENGTH],
    char email[STRING_LENGTH]
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
    if(root==NULL) 
        return new_node; 

    if(atoi(new_node->id)<atoi(root->id))
        root->left=insert_node(root->left, new_node);  
    else
        root->right=insert_node(root->right, new_node);  
    return root;
}

void display_tree(struct Node* root) {
    if(root==NULL)
        return; 
    //printing logic
    printw("%s ", root->id);
    //
    display_tree(root->left);
    display_tree(root->right);
    return;
}

struct Course* create_course(
    char name[STRING_LENGTH], 
    char code[STRING_LENGTH],
    char semester[STRING_LENGTH]
) {
    struct Course* new_course=(struct Course*)malloc(sizeof(struct Course));
    strcpy(new_course->name, name); 
    strcpy(new_course->code, code); 
    strcpy(new_course->semester, semester);
    return new_course;
}

void insert_course(struct Monotonic_Stack* stack, struct Course* new_course) {
    if(stack->size==0) {
        stack->courses[0]=new_course;
        ++stack->size;
        return;
    }
    int index=0;
    for(int i=0; i<stack->size; ++i) {
        if(strcmp(stack->courses[i]->name, new_course->name)>0) {
            index=i;
            break;
        }
        if(i==stack->size-1) {  
            index=stack->size;
        }
    }
    for(int i=stack->size; i>index; --i) {
        stack->courses[i]=stack->courses[i-1];
    }
    stack->courses[index]=new_course;
    ++stack->size;
    return;
}

void display_courses(struct Monotonic_Stack* stack) { 
    for(int i=0; i<stack->size; ++i)
       printw("%s ", stack->courses[i]);
    return;
}
