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

int debug=1; 

int main() {

    int ch;

    init_ncurses();
    mvprintw(2, 3, "-- Database Program --"); 
    mvprintw(3, 3, "press q to quit");

    // init bst
    struct Node* root=create_node("0", "a", "a", "a", "a");

    // init stack
    struct Monotonic_Stack s; 
    struct Monotonic_Stack* stack=&s;
    stack->size=0;

    //init grades
    struct Course_Grade g[99];
    struct Course_Grade* grades=g;

    
    char* student_file="student.csv";
    char* course_file="course.csv";
    char* grade_file="grades.csv";
    parse_files(student_file, course_file, grade_file, root, stack, grades);

    while(1) {

    if(debug)
        display_debug_info(ch);

    refresh();
    ch=getch();

    if(ch=='q')
        break;
    }

    endwin();

    return 0; 
}
