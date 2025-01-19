#ifndef DB
#define DB

#define STRING_LENGTH 99
#define COURSE_LENGTH 99
#define ROWS 99
#define COLUMNS 99

void init_ncurses(); 
void display_debug_info(int ch);

// binary search tree stufff....
struct Node {
    char id[STRING_LENGTH]; 
    char last_name[STRING_LENGTH];
    char first_name[STRING_LENGTH];
    char phone_number[STRING_LENGTH];
    char email[STRING_LENGTH];

    struct Node *left;
    struct Node *right;
};
struct Node* create_node( 
    char id[STRING_LENGTH], 
    char last_name[STRING_LENGTH], 
    char first_name[STRING_LENGTH], 
    char phone_number[STRING_LENGTH],
    char email[STRING_LENGTH]
);
struct Node* insert_node(struct Node* root, struct Node* new_node);
void display_tree(struct Node* root, int* i); 

// array for classes 
struct Course {
    char name[STRING_LENGTH];
    char code[STRING_LENGTH];
    char semester[STRING_LENGTH];
};
struct Monotonic_Stack {
    struct Course* courses[COURSE_LENGTH];
    int size; // the top of the stack
};
struct Course* create_course(
    char name[STRING_LENGTH], 
    char code[STRING_LENGTH],
    char semester[STRING_LENGTH]
);
void insert_course(struct Monotonic_Stack* stack, struct Course* new_course);
void display_courses(struct Monotonic_Stack* stack);
void display_courses_fall(struct Monotonic_Stack* stack);
void display_courses_winter(struct Monotonic_Stack* stack);
void display_courses_spring(struct Monotonic_Stack* stack);

// grades stuff
struct Course_Grade {
    char course_name[STRING_LENGTH];
    char students[99][STRING_LENGTH];
    char grades[99][STRING_LENGTH];
};
struct Course_Grade* create_course_grade(char* course_name);
void display_grades(struct Course_Grade* grades);

// parser stuff
struct Node* parse_bst(char* student_file, struct Node* root);
void parse_stack(char* course_file, struct Monotonic_Stack* stack);
void test_parse(char* filename);
void parse_struct(char* grade_file, struct Course_Grade* grades);

// ui 
void display_ui(); 
void display_students_in_order(struct Node* root, int* i); 
void display_students_in_order_reverse(struct Node* root, int* i); 

// append stuff
void add_student(char* student_file);
void add_course(char* course_file);


#endif
