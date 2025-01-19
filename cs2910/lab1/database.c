#include "database.h"
#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h> 
#include <string.h>


#define STUDENT_FILE "student.data"
#define STRING_LENGTH 99
#define LINE_LENGTH 999


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
    if(strcmp(new_node->first_name, root->first_name)<0)
        root->left=insert_node(root->left, new_node);  
    else
        root->right=insert_node(root->right, new_node);  
    return root;
}

void display_tree(struct Node* root, int i) {
    if(root==NULL)
        return; 
    display_tree(root->left, i+1);
    //printing logic
    if(strcmp(root->id, "0")) {
    mvprintw(i, 40, "%s, %s, %s, %s, %s", 
            root->id, 
            root->first_name, 
            root->last_name, 
            root->phone_number, 
            root->email);
    }
    //
    display_tree(root->right, i+1);
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
       mvprintw(8+i, 40, "%s, %s, %s", 
               stack->courses[i]->name, 
               stack->courses[i]->code,
               stack->courses[i]->semester);
    return;
}

void test_parse(char* filename) {
    FILE* file=fopen(filename, "r");
    if(file==NULL) {
        mvprintw(7, 7,"Error opening file");
        return;
    }
    char line[LINE_LENGTH];

    while(fgets(line, sizeof(line), file)) {
        mvprintw(7, 7,"Read line: %s", line);
    }
}

void parse_files(
    char* student_file,
    char* course_file,
    char* grade_file, 
    struct Node* root,
    struct Monotonic_Stack* stack, 
    struct Course_Grade* grades
) {
    parse_bst(student_file, root);
    parse_stack(course_file, stack);
    parse_struct(grade_file, grades);
}

void parse_bst(char* student_file, struct Node* root) {
    FILE* file; 

    file=fopen(student_file, "r");
    while (!feof(file)) {
        char line[LINE_LENGTH];
        while(fgets(line, sizeof(line), file)) {
            struct Node* new_node=create_node("a", "a", "a", "a", "a");
            char* token=strtok(line, ",");
            strcpy(new_node->id, token); 
            token=strtok(NULL, ",");  
            strcpy(new_node->last_name, token);
            token=strtok(NULL, ","); 
            strcpy(new_node->first_name, token);  
            token=strtok(NULL, ","); 
            strcpy(new_node->phone_number, token);
            token=strtok(NULL, ","); 
            strcpy(new_node->email, token);
            insert_node(root, new_node);
        }
    } 
    fclose(file);
}

void parse_stack(char* course_file, struct Monotonic_Stack* stack) {
    FILE* file; 
    file=fopen(course_file, "r");
    while (!feof(file)) {
        char line[LINE_LENGTH];
        while(fgets(line, sizeof(line), file)) {  
            struct Course* new_course=create_course("a", "a", "a");
            char* token=strtok(line, ",");
            strcpy(new_course->name, token);
            token=strtok(NULL, ","); 
            strcpy(new_course->code, token);
            token=strtok(NULL, ","); 
            strcpy(new_course->semester, token);
            insert_course(stack, new_course);
        }
    } 
    fclose(file);
}

struct Course_Grade* create_course_grade(char* course_name) {
    struct Course_Grade* new_course_grade=
        (struct Course_Grade*)malloc(sizeof(struct Course_Grade));
    strcpy(new_course_grade->course_name, course_name);
    return new_course_grade;
}

void parse_struct(char* grade_file, struct Course_Grade* grades) {
    FILE* file=fopen(grade_file, "r");
    int n=0;
    char line[LINE_LENGTH];
    while(fgets(line, sizeof(line), file)&&n<99) {
        struct Course_Grade* new_course_grade=create_course_grade("a");
        if(!new_course_grade) {
            fclose(file);
            return; 
        }
        char* token=strtok(line, ",");
        if(token) {
            strcpy(new_course_grade->course_name, token);
        }
        int i=0;
        while((token=strtok(NULL, ","))!=NULL&&i<99) {
            strcpy(new_course_grade->students[i], token);
            if((token=strtok(NULL, ","))!=NULL) {
                strcpy(new_course_grade->grades[i], token);
            }
            ++i;
        }
        grades[n]=*new_course_grade;
        free(new_course_grade);
        ++n;
    }
    fclose(file);
}

// this shit does not work ...
void display_grades(struct Course_Grade* grades) {
    for(int i=0; i<99; ++i) {
        if(!strcmp(grades[i].course_name, ""))
            break;
        mvprintw(7, 40+(i*12), "%s", grades[i].course_name);
    }
    for(int i=0; i<99; ++i) {
        if(!strcmp(grades[i].course_name, ""))
            break;
        mvprintw(8, 40+(i*12), "---------");
    }
    for(int i=0; i<99; ++i) {  
        if(!strcmp(grades[i].course_name, ""))
            break;
        for(int j=0; j<99; ++j) {
            if(strcmp(grades[i].grades[j], ""))
                break;
            mvprintw(8+j, 40+(i*12), "");
            printw(grades[i].students[j]);
            printw(" %s", grades[i].students[j]);
        }
    }
}

void display_ui() {
    mvprintw(2, 3, "-- Database Program --"); 
    mvprintw(5, 1, "Options");
    mvprintw(6, 0, "---------");
    mvprintw(7, 1, "(q) quit");
    mvprintw(8, 1, "(1) display list of all students");
    mvprintw(9, 1, "(2) students sorted by name"); 
    mvprintw(10, 1, "(3) students reverse order");
}

void display_students_in_order(struct Node* root, int i) {
    if(root==NULL)
        return; 
    //printing logic
    if(strcmp(root->id, "0")) {
    mvprintw(i, 40,"%s, %s", 
            root->first_name, 
            root->last_name
            );
    }
    //
    display_students_in_order(root->left, i+1);
    display_students_in_order(root->right, i+1);
    return;
}

void display_students_in_order_reverse(struct Node* root, int i) {
    if(root==NULL)
        return; 
    //printing logic
    if(strcmp(root->id, "0")) {
    mvprintw(i, 40,"%s, %s", 
            root->first_name, 
            root->last_name
            );
    }
    //
    display_students_in_order_reverse(root->right, i+1);
    display_students_in_order_reverse(root->left, i+1);
    return;
}





