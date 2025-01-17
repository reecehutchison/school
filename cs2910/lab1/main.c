#include <stdio.h> 
#include <ncurses.h>
#include "database.h"
#include <string.h>

#define STUDENT_FILE "student.data"

// plan!
//  - parsing (do this after data structures)
//  - students (binary search tree, sort by id)
//  - courses (monotonic stack (with random access), sorted alphabetically)
//  - grades (2d array... classes by list of structs that hold grade and id)
//

int debug=1; 

//FILE *fp; 

int main() {


    int ch;

    init_ncurses();
    mvprintw(2, 3, "-- Database Program --"); 
    mvprintw(3, 3, "press q to quit");

/* -- parsing stuff --
    fp=fopen(STUDENT_FILE, "r");
    
    char word[STRING_LENGTH]; 
    fscanf(fp, "%s", word);
    mvprintw(7, 7, "%s", word);

    fclose(fp);
*/

/* bst tree stuff
    struct Node* a_node=create_node("1", "a", "a", "a", "a");
    struct Node* b_node=create_node("2", "b", "b", "b", "b");
    struct Node* c_node=create_node("-1", "c", "c", "c", "c");
    
    insert_node(a_node, b_node);
    insert_node(a_node, c_node);

    mvprintw(6, 6, "");
    display_tree(a_node);

*/
/* stack stuff
    struct Monotonic_Stack s; 
    struct Monotonic_Stack* stack=&s;
    stack->size=0;

    struct Course* a_course=create_course("a", "1", "Spring");
    struct Course* b_course=create_course("b", "2", "Fall");
    struct Course* c_course=create_course("c", "3", "Winter");

    insert_course(stack, c_course);
    insert_course(stack, a_course);
    insert_course(stack, b_course);

    mvprintw(5, 6, "");
    display_courses(stack);
*/


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
