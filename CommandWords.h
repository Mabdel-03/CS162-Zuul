//header for CommandWords.cpp

class CommandWords {
private:
  //char array of valid commands in game
 char validCommands[7][50] = {
    "go", "quit", "help", "get", "drop", "inventory", "sandwich"};
  //the command 'sandwich' displays contents of sandwich
  
public:
  void getCommands();
  bool isCommand(char* inputCommand);
  CommandWords();
  void showAll();
};
