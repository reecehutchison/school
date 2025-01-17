#include <stdio.h> 
#include <ncurses.h>
#include "database.h"
#include <string.h>

#define STUDENT_FILE "student.data"
#define STRING_LENGTH 99


// plan!
//  - parsing (do this after data structures)
//  - students (binary search tree, sort by id)
//  - courses (binary search tree, sort by name ... alphabetically)
//  - grades (2d array... classes by list of structs that hold grade and id)
//

int debug=1; 

//FILE *fp; 

int main() {


    int ch;

    init_ncurses();
    mvprintw(2, 3, "-- Database Program --"); 
    mvprintw(3, 3, "press q to quit");

/*
    fp=fopen(STUDENT_FILE, "r");
    
    char word[STRING_LENGTH]; 
    fscanf(fp, "%s", word);
    mvprintw(7, 7, "%s", word);

    fclose(fp);
*/

    struct Node* a_node=create_node("1", "a", "a", "a", "a");
    struct Node* b_node=create_node("2", "b", "b", "b", "b");
    struct Node* c_node=create_node("-1", "c", "c", "c", "c");
    
    insert_node(a_node, b_node);
    insert_node(a_node, c_node);

    mvprintw(7, 7, a_node->id);
    mvprintw(8, 8, a_node->right->id);
    mvprintw(9, 9, a_node->left->id);


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
