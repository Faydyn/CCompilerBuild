#ifndef __SYMBOLTABLE_H
#define __SYMBOLTABLE_H

typedef struct symboltable_element {
    char* name;
    int line;
    struct symboltable_element* left;
    struct symboltable_element* right;
} symboltable_element;

void symboltable_output();
void symboltable_output_internal(symboltable_element* anchor);

symboltable_element* symboltable_add(char* t);
symboltable_element* symboltable_add_internal(char* t, symboltable_element** anchor);

#endif
