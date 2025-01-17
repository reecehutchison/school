#ifndef DB
#define DB

#define STRING_LENGTH 99
#define COURSE_LENGTH 99

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
void display_tree(struct Node* root); 

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



#endif
