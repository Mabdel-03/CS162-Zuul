//header for Parser.cpp

#include "CommandWords.h"

//create a struct to hold each word in the command
struct tokens{
  char word1[20];
  char word2[20];
};

class Parser{
public:	
  tokens* getCommand();
  void showCommand();
  bool checkValid(tokens* mytoken);
  tokens* parseCommand(char* input);
  Parser();

  //store valid commands of type CommandWords   
private:
  CommandWords commands;
};


