#ifndef DB
#define DB

#define STRING_LENGTH 99

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
    const char id[STRING_LENGTH], 
    const char last_name[STRING_LENGTH], 
    const char first_name[STRING_LENGTH], 
    const char phone_number[STRING_LENGTH],
    const char email[STRING_LENGTH]
);

struct Node* insert_node(struct Node* root, struct Node* new_node);

#endif
