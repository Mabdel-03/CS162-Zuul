//Parser takes in user's commands, checks if valid, and returns valid commands

#include "Parser.h"
#include "string.h"
#include <cstring>
#include <iostream>
using namespace std;

//take in command
tokens* Parser::getCommand(){
  bool isValid = false;
  char inputLine[50];
  char word1[20]; //allocate memory for each word
  char word2[20];
  tokens *mytoken = NULL;

  //keep looping until input is valid
  while(isValid == false){
    cout << "> "; //prompt input
    cin.get(inputLine, 50);
    cin.get();
    mytoken = parseCommand(inputLine);
    isValid = checkValid(mytoken); //check if valid
  }
  //out of loop, command is valid
  return mytoken;
}

//basically a bunch of hardcoded checks to see if the user typed in a valid command
bool Parser::checkValid(tokens* mytoken){
  //go commands
  if(strcmp(mytoken->word1, "go") == 0){
    if(strcmp(mytoken->word2, "north") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "east") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "south") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "west") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "up") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "down") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "northeast") == 0){
      return true;
    }
    
    else if(strcmp(mytoken->word2, "southeast") == 0){
      return true;
    }
    
    else if(strcmp(mytoken->word2, "southwest") == 0){
      return true;
    }
    
    else if(strcmp(mytoken->word2, "northwest") == 0){
      return true;
    }
 
    else{
      cout << "Second word not valid" << endl;
      return false;
    }
  }

  //quit
  if(strcmp(mytoken->word1, "quit") == 0){
    return true;
  }
  //help
  if(strcmp(mytoken->word1, "help") == 0){
    return true;
  }
  //get
  if(strcmp(mytoken->word1, "get") == 0){
    if(strcmp(mytoken->word2, "Fuel") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "Accelerator") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "PowerSwitch") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "Antenna") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "Monitor") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "Motor") == 0){
      return true;
    }
    else {
      cout << "get what?" << endl;
      return false;
    }   
  }
  //drop items
  if(strcmp(mytoken->word1, "drop") == 0){
    if(strcmp(mytoken->word2, "Fuel") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "Accelerator") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "PowerSwitch") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "Antenna") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "Motor") == 0){
      return true;
    }
    else if(strcmp(mytoken->word2, "Monitor") == 0){
      return true;
    }
    else {
      cout << "drop what?" << endl;
      return false;
    }
  }
  //inventory
  if(strcmp(mytoken->word1, "inventory") == 0){
    return true;
  }
  if(strcmp(mytoken->word1, "teleporter") == 0){
    return true;
  }
  
  if(strcmp(mytoken->word1, "eat") == 0){
    cout << "no, you cannot eat anything, it's not lunch time!" << endl;
    return false;
  }
  cout << "unknown command." << endl;
  return false;
}

//separates command into word 1 and word 2 and places in struct "tokens"
tokens* Parser::parseCommand(char* inputLine){
  char *charPtr;
  tokens *mytoken = new tokens;
  charPtr = strtok(inputLine, " "); //separate with a space
  if(charPtr !=  NULL){ //if not null, copy over
    strcpy(mytoken->word1, charPtr);
  } else { //else store "invalid" as the first word since that will not pass checkValid() 
    strcpy(mytoken->word1, "invalid");
  }
  
  //same for second word
  charPtr = strtok(NULL, " ");
  if(charPtr != NULL){
    strcpy(mytoken->word2, charPtr);
  } else {
    strcpy(mytoken->word2, "invalid");
  }
  return mytoken;
}

//show all commands
void  Parser::showCommand(){
  commands.showAll();
}

//constructor to create new commands
Parser::Parser(){
  commands = CommandWords();
}
