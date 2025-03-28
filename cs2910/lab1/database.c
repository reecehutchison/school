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
    mvprintw(31, 3, "key: %c",ch);
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

void display_tree(struct Node* root, int* i) {
    mvprintw(4, 40, "id, first name, last name, phone number, email");
    mvprintw(5, 40, "----------------------------------------------");

    if(root==NULL)
        return; 
    display_tree(root->left, i);
    //printing logic
    
    mvprintw(*i, 40, "%s, %s, %s, %s, %s", 
            root->id, 
            root->first_name,
            root->last_name,
            root->phone_number, 
            root->email);
    ++(*i);
    display_tree(root->right, i);
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
    mvprintw(4, 40, "name, code, semester");
    mvprintw(5, 40, "--------------------");
    for(int i=0; i<stack->size; ++i) {
        mvprintw(8+i, 40, "%s, %s, %s", 
                stack->courses[i]->name, 
                stack->courses[i]->code,
                stack->courses[i]->semester);
        }
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

struct Node* parse_bst(char* student_file, struct Node* root) {
    FILE* file=fopen(student_file, "r");
    char line[LINE_LENGTH];
        while(fgets(line, sizeof(line), file)) {
            line[strcspn(line, "\n")] = 0; 
            struct Node* new_node=create_node("a", "a", "a", "a", "a");
            char* token=strtok(line, ",");
            if(token)strcpy(new_node->id, token); 
            token=strtok(NULL, ",");  
            if(token)strcpy(new_node->last_name, token);
            token=strtok(NULL, ","); 
            if(token)strcpy(new_node->first_name, token);  
            token=strtok(NULL, ","); 
            if(token)strcpy(new_node->phone_number, token);
            token=strtok(NULL, ","); 
            if(token)strcpy(new_node->email, token);
            root=insert_node(root, new_node);  
    }
    fclose(file);
    return root;
}

void parse_stack(char* course_file, struct Monotonic_Stack* stack) {
    FILE* file; 
    file=fopen(course_file, "r");
    while (!feof(file)) {
        char line[LINE_LENGTH];
        while(fgets(line, sizeof(line), file)) {  
            line[strcspn(line, "\n")] = 0; 
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
    int num_courses=0;
    char line[LINE_LENGTH];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0; 

        char* course_name=strtok(line, ",");
        char* student_name=strtok(NULL, ",");
        char* grade=strtok(NULL, ",");

        struct Course_Grade* current_course_grade=NULL;
        for (int i=0; i<num_courses; ++i) {
            if(strcmp(grades[i].course_name, course_name)==0) {
                current_course_grade = &grades[i];
                break;
            }
        }
        if(!current_course_grade) { // if not found in last for loop, make new
            current_course_grade=&grades[num_courses++];
            strcpy(current_course_grade->course_name, course_name);

            for(int i=0; i < 99; ++i) {
                current_course_grade->students[i][0]='\0';
                current_course_grade->grades[i][0]='\0';
            }
        }
        int student_index=0; // finds next available empty strings
        while(student_index<99&&current_course_grade->students[student_index][0]!='\0') {
            student_index++;
        }
        if (student_index < 99) {
            strcpy(current_course_grade->students[student_index], student_name);
            strcpy(current_course_grade->grades[student_index], grade);
        }
    }
    fclose(file);
}

void display_ui() {
    mvprintw(2, 3, "-- Database Program --"); 
    mvprintw(5, 1, "Options");
    mvprintw(6, 0, "---------");
    mvprintw(7, 1, "(q) quit (note: reset after appends)");
    mvprintw(8, 1, "(1) display list of all students");
    mvprintw(9, 1, "(2) students sorted by name");
    mvprintw(10, 1, "(r) students by name reversed");
    mvprintw(11, 1, "(3) list of all courses");
    mvprintw(12, 1, "(4) list all fall courses");
    mvprintw(13, 1, "(5) list all winter courses");
    mvprintw(14, 1, "(s) list all spring courses");
    mvprintw(15, 1, "(6) add student to db");
    mvprintw(16, 1, "(c) add course to db");
    mvprintw(17, 1, "(a) add grade to db");
    mvprintw(18, 1, "(u) update student info");
    mvprintw(19, 1, "(8) search for course by name");
    mvprintw(20, 1, "(9) search for course by code");
    mvprintw(21, 1, "(z) search for student by last name");
    mvprintw(22, 1, "(x) search for student by phone");
    mvprintw(23, 1, "(v) list all students courses taken");
    mvprintw(24, 1, "(b) list student average");
    mvprintw(25, 1, "(m) list student semester averages");
    mvprintw(26, 1, "(n) list class average");
}

void display_students_in_order(struct Node* root, int* i) { 
    mvprintw(4, 40, "first name, last name");
    mvprintw(5, 40, "---------------------");
    if(root==NULL)
        return; 
    display_students_in_order(root->left, i);
    //printing logic
    mvprintw(*i, 40, "%s, %s", 
            root->first_name,
            root->last_name);
    ++(*i);
    //
    display_students_in_order(root->right, i);
    return;
}

void display_students_in_order_reverse(struct Node* root, int* i) {  
    mvprintw(4, 40, "first name, last name");
    mvprintw(5, 40, "---------------------");
    if(root==NULL)
        return; 
    display_students_in_order_reverse(root->right, i);
    //printing logic
    mvprintw(*i, 40, "%s, %s", 
            root->first_name,
            root->last_name);
    ++(*i);
    //
    display_students_in_order_reverse(root->left, i);
    return;
}

void display_courses_fall(struct Monotonic_Stack* stack) {
    mvprintw(4, 40, "name, code --> (fall courses)");
    mvprintw(5, 40, "-----------------------------");
    int j=0; 
    for(int i=0; i<stack->size; ++i) {
        if(strcmp(stack->courses[i]->semester, " fall")==0) {
            mvprintw(8+j, 40, "%s, %s", 
                stack->courses[i]->name, 
                stack->courses[i]->code);
            ++j;  
        }
    }
    return;
}

void display_courses_winter(struct Monotonic_Stack* stack) {
    mvprintw(4, 40, "name, code --> (winter courses)");
    mvprintw(5, 40, "------------------------------");
    int j=0; 
    for(int i=0; i<stack->size; ++i) {
        if(strcmp(stack->courses[i]->semester, " winter")==0) {
            mvprintw(8+j, 40, "%s, %s", 
                stack->courses[i]->name, 
                stack->courses[i]->code);
            ++j;  
        }
    }
    return;
}
void display_courses_spring(struct Monotonic_Stack* stack) {
    mvprintw(4, 40, "name, code --> (spring courses)");
    mvprintw(5, 40, "-------------------------------");
    int j=0; 
    for(int i=0; i<stack->size; ++i) {
        if(strcmp(stack->courses[i]->semester, " spring")==0) {
            mvprintw(8+j, 40, "%s, %s", 
                stack->courses[i]->name, 
                stack->courses[i]->code);
            ++j;  
        }
    }
    return;
}

void add_student(char* student_file) {
    char id[STRING_LENGTH];
    char first_name[STRING_LENGTH];
    char last_name[STRING_LENGTH];
    char phone_number[STRING_LENGTH];
    char email[STRING_LENGTH];
    char input[STRING_LENGTH];

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter student id: ");
    refresh();
    getstr(input);
    strcpy(id, input);

    mvprintw(2, 10, "enter first name: ");
    refresh();
    getstr(input);
    strcpy(first_name, input);

    mvprintw(3, 10, "enter last mame: ");
    refresh();
    getstr(input);
    strcpy(last_name, input);

    mvprintw(4, 10, "enter phone number: ");
    refresh();
    getstr(input);
    strcpy(phone_number, input);

    mvprintw(5, 10, "enter email: ");
    refresh();
    getstr(input);
    strcpy(email, input);

    FILE* file=fopen(student_file, "a");  
    fprintf(file, "%s, %s, %s, %s, %s\n", id, last_name, first_name, phone_number, email);
    fclose(file);
    mvprintw(7, 10, "student data saved, press any button to exit");
    refresh();
    getch();  
    clear();
    curs_set(0);
    noecho();
}

void add_course(char* course_file) {
    char name[STRING_LENGTH];
    char code[STRING_LENGTH];
    char semester[STRING_LENGTH];
    char input[STRING_LENGTH];

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter course name: ");
    refresh();
    getstr(input);
    strcpy(name, input);

    mvprintw(2, 10, "enter code for course: ");
    refresh();
    getstr(input);
    strcpy(code, input);

    mvprintw(3, 10, "enter semester: ");
    refresh();
    getstr(input);
    strcpy(semester, input);


    FILE* file=fopen(course_file, "a");  
    fprintf(file, "%s, %s, %s\n", name, code, semester);
    fclose(file);
    mvprintw(7, 10, "course data saved, press any button to exit");
    refresh();
    getch();  
    clear();
    curs_set(0);
    noecho();
}

void search_course_by_name(struct Monotonic_Stack* stack) {  
    char input[STRING_LENGTH];
    curs_set(1);
    echo();

    mvprintw(1, 10, "enter course name: ");
    refresh();
    getstr(input);

    for(int i=0; i<99; ++i) {
        if(stack->courses[i]!=NULL&&strcmp(stack->courses[i]->name, input)==0) {
            mvprintw(3, 10, "course code: %s", stack->courses[i]->code);
            mvprintw(4, 10, "course semester: %s", stack->courses[i]->semester);
            mvprintw(8, 10, "(press any button to exit)");

            refresh();
            getch();  
            clear();
            curs_set(0);
            noecho();
            break;
        }

        if(i>80) {
            mvprintw(8, 10, "(course not found, press any button to exit)");

            refresh();
            getch();  
            clear();
            curs_set(0);
            noecho();
            break;
        }

    }
}

void search_course_by_code(struct Monotonic_Stack* stack) {

    char input[STRING_LENGTH]; 
    char str[STRING_LENGTH]=" ";

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter course code: ");
    refresh();
    getstr(input);
    strcat(str, input);


    for(int i=0; i<98; ++i) {
        if(stack->courses[i]!=NULL&&strcmp(stack->courses[i]->code, str)==0) {
            mvprintw(3, 10, "course name: %s", stack->courses[i]->name);
            mvprintw(4, 10, "course semester: %s", stack->courses[i]->semester);
            mvprintw(8, 10, "(press any button to exit)");

            refresh();
            getch();  
            clear();
            curs_set(0);
            noecho();
            break;
        }
        if(i>80) {
            mvprintw(8, 10, "(course not found, press any button to exit)");

            refresh();
            getch();  
            clear();
            curs_set(0);
            noecho();
            break;
        }
    }
}


void search_for_student_last_name(struct Node* root) {
    char input[STRING_LENGTH];
    int found=0;

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter student last name: ");
    refresh();
    getstr(input);

    dfs_student_last_name(input, root, &found);

    if(!found) 
        mvprintw(3, 10, "student not found, press anything to exit");
    else 
        mvprintw(9, 10, "press anything to exit");

    refresh();
    getch();  
    clear();
    curs_set(0);
    noecho();
}

void dfs_student_last_name(char* last_name, struct Node* root, int* found) {
    if(root==NULL||*found) 
        return;

    char str[STRING_LENGTH]=" ";
    strcat(str, last_name);

    if(strcmp(root->last_name, str)==0) {
        *found=1;
        mvprintw(3, 10, "student id: %s", root->id);
        mvprintw(4, 10, "student first name: %s", root->first_name);
        mvprintw(5, 10, "sudent email: %s", root->email);
        mvprintw(6, 10, "student phone number: %s", root->phone_number);
        return;
    }
    dfs_student_last_name(last_name, root->left, found);
    dfs_student_last_name(last_name, root->right, found);

    return; 
}

void search_for_student_phone(struct Node* root) {
    char input[STRING_LENGTH];
    int found=0;

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter student phone: ");
    refresh();
    getstr(input);

    dfs_student_phone(input, root, &found);

    if(!found) 
        mvprintw(3, 10, "student not found, press anything to exit");
    else 
        mvprintw(9, 10, "press anything to exit");

    refresh();
    getch();  
    clear();
    curs_set(0);
    noecho();
}

void dfs_student_phone(char* phone, struct Node* root, int* found) {
    if(root==NULL||*found) 
        return;

    char str[STRING_LENGTH]=" ";
    strcat(str, phone);

    if(strcmp(root->phone_number, str)==0) {
        *found=1;
        mvprintw(3, 10, "student id: %s", root->id);
        mvprintw(4, 10, "student first name: %s", root->first_name);
        mvprintw(5, 10, "student last name: %s", root->last_name);
        mvprintw(6, 10, "sudent email: %s", root->email);
        return;
    }
    dfs_student_phone(phone, root->left, found);
    dfs_student_phone(phone, root->right, found);

    return; 
}

void list_student_courses(struct Course_Grade* grades) {

    char input[STRING_LENGTH];
    char str[STRING_LENGTH]=" ";

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter student last name: ");
    refresh();
    getstr(input);
    strcat(str, input);

    mvprintw(3, 10, "class, grades");
    mvprintw(4, 10, "-------------");

    int n=0; 

    for(int i=0; i<80; ++i) {
        if(strcmp(grades[i].course_name, "")==0)
            break;
        for(int j=0; j<80; ++j) {
            if(strcmp(grades[i].students[j], "")==0) 
                break;
            if(strcmp(grades[i].students[j], str)==0)  {
                mvprintw(5+n, 10, "%s, ", grades[i].course_name);
                printw("%s", grades[i].grades[j]);
                ++n;
            }
        }
    }
    mvprintw(15, 45, "(press any button to exit.)");
    mvprintw(16, 45, "(if no results, student not found or has taken no classes)");

    refresh();
    getch();  
    clear();

    curs_set(0);
    noecho();
}

void list_student_average(struct Course_Grade* grades) {
    char input[STRING_LENGTH];
    char str[STRING_LENGTH]=" ";

    float sum=0; 
    float total=0;

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter student last name: ");
    refresh();
    getstr(input);
    strcat(str, input);

    for(int i=0; i<80; ++i) {
        if(strcmp(grades[i].course_name, "")==0)
            break;
        for(int j=0; j<80; ++j) {
            if(strcmp(grades[i].students[j], "")==0) 
                break;
            if(strcmp(grades[i].students[j], str)==0)  {
                sum+=atoi(grades[i].grades[j]); 
                ++total;
            }
        }
    }
    mvprintw(3, 10, "student average grade: %.2f", (sum/total));
    mvprintw(7, 10, "(press any button to exit. if result is nan, student not found)");

    refresh();
    getch();  
    clear();
 
    curs_set(0);
    noecho();
}

void list_class_average(struct Course_Grade* grades) {
    char input[STRING_LENGTH];

    float sum=0; 
    float total=0;

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter class name: ");
    refresh();
    getstr(input);

    for(int i=0; i<80; ++i) {
        if(strcmp(grades[i].course_name, "")==0)
            break;
        for(int j=0; j<80; ++j) {
            if(strcmp(grades[i].students[j], "")==0) 
                break;
            if(strcmp(grades[i].course_name, input)==0)  {
                sum+=atoi(grades[i].grades[j]);
                ++total;
            }
        }
    }
    mvprintw(3, 10, "class average grade: %.2f", (sum/total));
    mvprintw(7, 10, "(press any button to exit. if nan, then course not found)");

    refresh();
    getch();  
    clear();
 
    curs_set(0);
    noecho();
}

void add_grade(char* grade_file) {
    char course_name[STRING_LENGTH];
    char student[STRING_LENGTH];
    char grade[STRING_LENGTH];
    char input[STRING_LENGTH];

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter course name: ");
    refresh();
    getstr(input);
    strcpy(course_name, input);

    mvprintw(2, 10, "enter student last name: ");
    refresh();
    getstr(input);
    strcpy(student, input);

    mvprintw(3, 10, "enter student grade: ");
    refresh();
    getstr(input);
    strcpy(grade, input);


    FILE* file=fopen(grade_file, "a");  
    fprintf(file, "%s, %s, %s\n", course_name, student, grade);
    fclose(file);
    mvprintw(7, 10, "grade data saved, press any button to exit");
    refresh();
    getch();  
    clear();
    curs_set(0);
    noecho();
}

void update_student_info(struct Node* root, char* student_file) {

    char id[STRING_LENGTH];
    char first_name[STRING_LENGTH]=" ";
    char last_name[STRING_LENGTH]=" ";
    char phone_number[STRING_LENGTH]=" ";
    char email[STRING_LENGTH]=" ";
    char input[STRING_LENGTH]=" ";

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter student id: ");
    refresh();
    getstr(input);
    strcpy(id, input);

    mvprintw(2, 10, "enter first name: ");
    refresh();
    getstr(input);
    strcat(first_name, input);

    mvprintw(3, 10, "enter last name: ");
    refresh();
    getstr(input);
    strcat(last_name, input);

    mvprintw(4, 10, "enter phone number: ");
    refresh();
    getstr(input);
    strcat(phone_number, input);

    mvprintw(5, 10, "enter email: ");
    refresh();
    getstr(input);
    strcat(email, input);

    // write here

    //dfs to find and update 
    update_tree_info(
            root,
            student_file,
            id,
            first_name,
            last_name,
            phone_number,
            email);

    FILE* file=fopen(student_file, "w");


    //dfs to write everything into the file again
    write_bst_to_file(root, student_file);
    //

    mvprintw(7, 10, "student data saved, press any button to exit");
    refresh();
    getch();  
    clear();
    curs_set(0);
    noecho();
}

void update_tree_info(
        struct Node* root,
        char* student_file,
        char* id,
        char* first_name, 
        char* last_name,
        char* phone_number, 
        char* email) {

    if(root==NULL)
        return;
    if(strcmp(root->id, id)==0) {
        strcpy(root->first_name, first_name);
        strcpy(root->last_name, last_name);
        strcpy(root->phone_number, phone_number);
        strcpy(root->email, email);
    }
    update_tree_info(
            root->left,
            student_file,
            id,
            first_name,
            last_name, 
            phone_number, 
            email); 
    update_tree_info(
            root->right,
            student_file,
            id,
            first_name,
            last_name, 
            phone_number, 
            email);
    return;
}

void write_bst_to_file(struct Node* root, char* student_file) {
    if(root==NULL)
        return;
    // write stuff here
    
    FILE* file=fopen(student_file, "a");  
    fprintf(file, "%s,%s,%s,%s,%s\n", 
            root->id,
            root->last_name,
            root->first_name,
            root->phone_number,
            root->email);
    fclose(file);


    write_bst_to_file(root->left, student_file);
    write_bst_to_file(root->right, student_file);
}

void list_student_average_semester(
        struct Course_Grade* grades,
        struct Monotonic_Stack* stack) {
// ----------------------------------
    float fall_sum=0;
    float fall_total=0; 

    float winter_sum=0; 
    float winter_total=0; 

    float spring_sum=0; 
    float spring_total=0;

    char input[STRING_LENGTH];
    char str[STRING_LENGTH]=" ";

    float sum=0; 
    float total=0;

    curs_set(1);
    echo();

    mvprintw(1, 10, "enter student last name: ");
    refresh();
    getstr(input);
    strcat(str, input);

    for(int i=0; i<80; ++i) {
        if(strcmp(grades[i].course_name, "")==0)
            break;
        for(int j=0; j<80; ++j) {
            if(strcmp(grades[i].students[j], "")==0) 
                break;
            if(strcmp(grades[i].students[j], str)==0)  {
                for(int k=0; k<80; ++k) {

                    if(stack->courses[k]==NULL)
                        break;

                    char str[STRING_LENGTH]=" ";
                    strcat(str, grades[i].course_name);
                    if(stack->courses[k]!=NULL&&strcmp(grades[i].course_name, stack->courses[k]->name)==0) {
                        if(strcmp(stack->courses[k]->semester, " fall")==0) {
                             
                            fall_sum+=atoi(grades[i].grades[j]);
                            ++fall_total;
                        } 
                        if(strcmp(stack->courses[k]->semester, " winter")==0) {
                            winter_sum+=atoi(grades[i].grades[j]);
                            ++winter_total;
                        }
                        else {     
                            spring_sum+=atoi(grades[i].grades[j]);
                            ++spring_total;
                        }
                    }
                }
            }
        }
    }

    // print avgs here
    mvprintw(4, 35, "fall average: %.2f", (fall_sum / fall_total));
    mvprintw(5, 35, "winter average: %.2f", (winter_sum / winter_total));
    mvprintw(6, 35, "spring average: %.2f", (spring_sum / spring_total));
    mvprintw(17, 20, "(nan results mean no classes during semester were found, press anything to exit)");

    refresh();
    getch();  
    clear();
 
    curs_set(0);
    noecho();
}
