//header for Items.cpp
#include <iostream>


class Items{
public:
  char* getName();
  Items(char* inputName); //constructor to name items
private:
  char name[20]; //store name variable
};

