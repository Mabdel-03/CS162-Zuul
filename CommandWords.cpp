//command words checks if input is a command and has the option to show all commands
#include "CommandWords.h"
#include <iostream>
#include <cstring>

using namespace std;

//checks if is a command
bool CommandWords::isCommand(char* inputCommand){
  for(int i = 0; i < sizeof(validCommands); i++){
    if(strcmp(inputCommand, validCommands[i]) == 0){ //if in validCommands list..
      return true;
    }
  }
  //else it is not a command
  return false;
}

//constructor
CommandWords::CommandWords(){


}

//when called, show all commands
void CommandWords::showAll(){
  for(int i = 0; i < 7; i++) { //the 7 is the amount of commands in this game
    cout << validCommands[i] << "  " << endl;
  }
  cout << " " << endl;
}
