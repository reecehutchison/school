#include <stdio.h> 
#include <ncurses.h>
#include "database.h"
#include <string.h>

#define STUDENT_FILE "student.data"

//
//
//  to do -- 
//  - LAST: the update stuff, so 6 (grades), and 7...
//  - 15 - this one looks tough
//
//
//
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
    parse_stack(course_file, stack);
    parse_struct(grade_file, grades);


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
    if(ch=='2') {
        int index=7; 
        display_students_in_order(root, &index);
    }
    if(ch=='r') {
        int index=7;
        display_students_in_order_reverse(root, &index);
    }
    if(ch=='3')
        display_courses(stack);
    if(ch=='4')     
        display_courses_fall(stack);
    if(ch=='5')
        display_courses_winter(stack);
    if(ch=='s')
        display_courses_spring(stack);
    if(ch=='6') 
        add_student(student_file);
    if(ch=='c')
        add_course(course_file);
    // 7 goes here
    if(ch=='8')
        search_course_by_name(stack);
    if(ch=='9')
        search_course_by_code(stack);
    if(ch=='z') 
        search_for_student_last_name(root);
    if(ch=='x')
        search_for_student_phone(root);
    if(ch=='v')
        list_student_courses(grades);
    if(ch=='b')
        list_student_average(grades);


    }

    endwin();

    return 0; 
}
