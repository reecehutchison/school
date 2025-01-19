#include <stdio.h> 
#include <ncurses.h>
#include "database.h"
#include <string.h>

#define STUDENT_FILE "student.data"

// plan!
//  - parsing (do this after data structures)
//  - students (binary search tree, sort by id)
//  - courses (monotonic stack (with random access), sorted alphabetically)
//  - grades (array of structs, has name, and two arrays one for student id, 
//  and one for grades, then they match indexs)
//  - do ui

int debug=1; 

int main() {

    int ch;

    init_ncurses();

    // init bst
    struct Node* root=NULL;

    // init stack
    struct Monotonic_Stack s; 
    struct Monotonic_Stack* stack=&s;
    stack->size=0;

    // init grades
    struct Course_Grade g[99];
    struct Course_Grade* grades=g;

    char* student_file="student.csv";
    char* course_file="course.csv";
    char* grade_file="grades.csv";
    
    // parse
    root=parse_bst(student_file, root);


    
    while(1) {

    display_ui();

    if(debug)
        display_debug_info(ch);

    refresh();
    ch=getch();
    clear();

    if(ch=='q')
        break;

    if(ch=='1') {
        int index=7;
        display_tree(root, &index);
    }

    }

    endwin();

    return 0; 
}
