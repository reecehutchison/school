#ifndef DB
#define DB

#define STRING_LENGTH 99

void init_ncurses(); 
void display_debug_info(int ch);

// binary search tree stufff....
struct Node {
    int id; 
    char last_name[STRING_LENGTH];
    char first_name[STRING_LENGTH];
    char phone_number[STRING_LENGTH];
    char email[STRING_LENGTH];

    struct Node *left;
    struct Node *right;
};


#endif
