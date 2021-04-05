//header for items
#include "Items.h"
#include <cstring>

//get name of item
char* Items::getName(){
  return name;
}

//copy the name of inputted item to the name stored here
Items::Items(char* inputName){
  strcpy(name, inputName);
}
