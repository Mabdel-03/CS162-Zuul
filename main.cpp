/* Code Written By Mahmoud Abdelmoneum
 * Code Written on 4/4/2021
 * Zuul is an adventure game that consists of a maze of rooms, where the player
 * Must search for items to construct a teloportation device to escape the room
 * Once all five items are found and dropped in main room, player wins and game ends
 */

#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "Room.h"
#include "Parser.h"

using namespace std;

//function prototypes
void createRooms(vector<Room*>* &roomVtr, Room *&currentRoom);
void printHelp(Parser *p);
void goRoom(tokens* command, Room* &currentRoom);
void quit();
void dropItem(tokens* command, Room* &currentRoom, vector<Items*> *&inventory, vector<Items*> *&sandwichVtr);
void getItem(tokens* command, Room* &currentRoom, vector<Items*> *&inventory);
bool printTeleporterContents(vector<Items*> *sandwichVtr);
void printInventory(vector<Items*> *inventory);
bool processCommand(tokens* command, Room* &currentRoom, vector<Items*> *&inventory, Parser *&p, vector<Items*> *&sandwichVtr);

void quit(){
  cout << "Thank you for playing The Void. Quitting program now." << endl;
}


//user picks up item from room, adds to inventory
void getItem(tokens* command, Room* &currentRoom, vector<Items*> *&inventory){
  char item[50];
  strcpy(item, command->word2);

  Items* newItem = NULL;
  newItem = currentRoom->getItem(item);
  if(newItem == NULL){
    cout << "That item is not in this room!" << endl;
  } else {
    inventory->push_back(newItem);
    currentRoom->removeItem(item);
    cout << "You picked up: " << newItem->getName() << endl;
  }
}

//remove from inventory and put in room
void dropItem(tokens* command, Room* &currentRoom, vector<Items*> *&inventory, vector<Items*> *&sandwichVtr){
  char item[50];
  strcpy(item, command->word2);
  Items* newItem = NULL;
  int index;

  //if name matches the name of an item in inventory...
  for(int i = 0; i < inventory->size(); i++){
    if(strcmp(inventory->at(i)->getName(), item) == 0){
      newItem = inventory->at(i);
      index = i;
    }
  }
  //if there is no item to drop
  if(newItem == NULL){
    cout << "You don't have anything like that to drop." << endl;
  } else {

    //if dropped in MainRoom...
    if(strcmp(currentRoom->getRoom(), "MainRoom") == 0){
      sandwichVtr->push_back(newItem); //add to sandwich vector
      cout << "You placed " << newItem->getName() << " in the teleporter!" << endl;
      cout << "To see contents of teleporter, type 'teleporter'" << endl;
    }
    else{
      currentRoom->addItem(newItem);
      cout << "You dropped: " << newItem->getName() << endl;
    }
    //remove from inventory
    inventory->erase(inventory->begin()+index);
  }
}

//initialize all rooms and items
void createRooms(vector<Room*> *&roomVtr, Room *&currentRoom){
  Room* MainRoom = new Room((char*)("MainRoom"));
  Room* DarkRoom = new Room((char*)("DarkRoom"));
  Room* Arsenal = new Room((char*)("Arsenal"));
  Room* Lavoratory = new Room((char*)("Lavoratory"));
  Room* AlienWashroom = new Room((char*)("AlienWashroom"));
  Room* CaptainRoom = new Room((char*)("CaptainRoom"));
  Room* MessHall = new Room((char*)("MessHall"));
  Room* Storage = new Room((char*)("Storage"));
  Room* Morgue = new Room((char*)("Morgue"));
  Room* Arcade = new Room((char*)("Arcade"));
  Room* Garden = new Room((char*)("Garden"));
  Room* Laboratory = new Room((char*)("Laboratory"));
  Room* Farm = new Room((char*)("Farm"));
  Room* Sewer = new Room((char*)("Sewer"));
  Room* Mechanic = new Room((char*)("Mechanic"));
  Room* Hallway = new Room((char*)("Hallway"));
  Room* BackRoom = new Room((char*)("BackRoom"));
  Room* OldShip = new Room((char*)("OldShip"));

  //print welcome
  cout << "********************************" << endl;
  cout << " " << endl;
  cout << "Welcome to The Void!" << endl;
  cout << "The Void takes place in abandoned alien catacombs on an unknown planet in a galaxy far far away. To escape back to earth, you must gather the parts necessary to construct an interstellar teleportation device!" << endl;
  cout << "Type 'help' if you need help." << endl; 
  cout << " " << endl;
  cout << "A metal frame lays in the middle of the room. To turn this frame into a functioning interstellar teleportation device, you must find a monitor, an antenna, a power switch, an accelerator, and fuel" << endl;
  cout << "Remember, to add parts to the frame, you must drop them in the main room!" << endl;
  cout << "Once you think you have dropped all 6 parts in the main room, type 'teleporter' to win!" << endl;
  cout << "Good luck!" << endl;
  cout << " " << endl;
  cout << "********************************" << endl;
  
  //MainRoom
  MainRoom->setDescription((char*)("You are in the main room of the void."));
  currentRoom = MainRoom;
  MainRoom->setExits((char*)("east"), Lavoratory);
  MainRoom->setExits((char*)("south"), CaptainRoom);
  MainRoom->setExits((char*)("west"), Arcade);
  MainRoom->setExits((char*)("north"), DarkRoom);
  currentRoom = MainRoom;
  roomVtr->push_back(MainRoom);
  cout << MainRoom->getLongDescription() << endl;

  
  //DarkRoom
  DarkRoom->setDescription((char*)("You enter a dark, eerie room. It is dank. There is no light."));
  DarkRoom->setExits((char*)("south"), MainRoom);
  DarkRoom->setExits((char*)("up"), Sewer);
  DarkRoom->setExits((char*)("east"), Arsenal);
  DarkRoom->setExits((char*)("west"), Garden);
  roomVtr->push_back(DarkRoom);
  
  //Arsenal
  Arsenal->setDescription((char*)("You are in an empty arsenal. Futuristic alien lazer guns are everywhere."));
  Arsenal->setExits((char*)("east"), BackRoom);
  Arsenal->setExits((char*)("southeast"), Hallway);
  Arsenal->setExits((char*)("south"), Lavoratory);
  Arsenal->setExits((char*)("west"), DarkRoom);
  roomVtr->push_back(Arsenal);
  
  //Lavoratory
  Lavoratory->setDescription((char*)("You are in an alien lavoratory. Stinky!"));
  Lavoratory->setExits((char*)("north"), Arsenal);
  Lavoratory->setExits((char*)("east"), Hallway);
  Lavoratory->setExits((char*)("south"), AlienWashroom);
  Lavoratory->setExits((char*)("west"), MainRoom);
  roomVtr->push_back(Lavoratory);
  
  //AlienWashroom
  AlienWashroom->setDescription((char*)("You have entered a room full of alien showers! These look so... Weird."));
  AlienWashroom->setExits((char*)("north"), Lavoratory);
  AlienWashroom->setExits((char*)("southwest"), MessHall);
  AlienWashroom->setExits((char*)("west"), CaptainRoom);
  roomVtr->push_back(AlienWashroom);

  //Captain Room
  CaptainRoom->setDescription((char*)("You have entered the Captain's room. Captain of what? I don't know. But he is alien, and he will not be too happy finding you here!"));
  CaptainRoom->setExits((char*)("north"), MainRoom);
  CaptainRoom->setExits((char*)("east"), AlienWashroom);
  CaptainRoom->setExits((char*)("southeast"), MessHall);
  CaptainRoom->setExits((char*)("west"), Storage);
  roomVtr->push_back(CaptainRoom);
  
  //Mess Hall
  MessHall->setDescription((char*)("You are in the mess hall! Here you will find the fuel that you need!"));
  MessHall->setExits((char*)("northwest"), CaptainRoom);
  MessHall->setExits((char*)("northeast"), AlienWashroom);
  roomVtr->push_back(MessHall);

  //storage
  Storage->setDescription((char*)("You are in an empty storage room. Boring!"));
  Storage->setExits((char*)("north"), Arcade);
  Storage->setExits((char*)("west"), Morgue);
  Storage->setExits((char*)("east"), CaptainRoom);
  roomVtr->push_back(Storage);

  //Morgue
  Morgue->setDescription((char*)("You are in the morgue. Gross! But, here you can find the accelerator you need"));
  Morgue->setExits((char*)("east"), Storage);
  Morgue->setExits((char*)("northeast"), Arcade);
  roomVtr->push_back(Morgue);

  //Arcade
  Arcade->setDescription((char*)("You have entered the arcade. Cool!"));
  Arcade->setExits((char*)("north"), Garden);
  Arcade->setExits((char*)("east"), MainRoom);
  Arcade->setExits((char*)("southwest"), Morgue);
  Arcade->setExits((char*)("south"), Storage);
  roomVtr->push_back(Arcade);

  //Garden
  Garden->setDescription((char*)("You are in the garden. But it is dark, and underground. Nothing interesting here!"));
  Garden->setExits((char*)("northwest"), Laboratory);
  Garden->setExits((char*)("east"), DarkRoom);
  Garden->setExits((char*) ("south"), Arcade);
  roomVtr->push_back(Garden);

  //Laboratory
  Laboratory->setDescription((char*)("You have entered the laboratory. All sorts of cool alien science here, but nothing that we need!"));
  Laboratory->setExits((char*)("east"), Farm);
  Laboratory->setExits((char*)("southeast"), Garden);
  roomVtr->push_back(Laboratory);

  //Farm
  Farm->setDescription((char*)("You are in the farm. Here you can find the power switch that you need!"));
  Farm->setExits((char*)("west"), Laboratory);
  roomVtr->push_back(Farm);
  
  //Sewer
  Sewer->setDescription((char*)("You are in the sewer. Yuck! It's gross, but here you can find the antenna that you need."));
  Sewer->setExits((char*)("down"), DarkRoom);
  Sewer->setExits((char*)("east"), Mechanic);
  roomVtr->push_back(Sewer);
  
  //Mechanic
  Mechanic->setDescription((char*)("You are in the mechanic's room! Here you will find the monitor that you need."));
  Mechanic->setExits((char*)("west"), Sewer);
  roomVtr->push_back(Mechanic);
  
  //Hallway
  Hallway->setDescription((char*)("You are in a hallway. Nothing special here."));
  Hallway->setExits((char*)("northwest"), Arsenal);
  Hallway->setExits((char*)("north"), BackRoom);
  Hallway->setExits((char*)("west"), Lavoratory);
  Hallway->setExits((char*)("down"), OldShip);
  roomVtr->push_back(Hallway);

  //backroom
  BackRoom->setDescription((char*)("You are in the back room. There are a lot of boxes, but nothing of value."));
  BackRoom->setExits((char*)("west"), Arsenal);
  BackRoom->setExits((char*)("south"), Hallway);
  roomVtr->push_back(BackRoom);
  
  //Old Ship
  OldShip->setDescription((char*)("You are in the old alien ship. It no longer works"));
  OldShip->setExits((char*)("up"), Hallway);
  roomVtr->push_back(OldShip);
  
  //items
  Farm->setItems(new Items((char*)("PowerSwitch")));
  Morgue->setItems(new Items((char*)("Accelerator")));
  MessHall->setItems(new Items((char*)("Fuel")));
  Mechanic->setItems(new Items((char*)("Monitor")));
  Sewer->setItems(new Items((char*)("Antenna"))); 
}

//takes in command, directs to other functions
bool processCommand(tokens* command, Room* &currentRoom, vector<Items*>* &inventory, Parser* &p, vector<Items*> *&sandwichVtr){
  bool wantToQuit = false;

  //direct commands to other functions
  if(strcmp(command->word1, "help") == 0){ //prints help message
    printHelp(p);
  }
  else if(strcmp(command->word1, "go") == 0){ //goes to new room
    goRoom(command, currentRoom);
  }
  else if(strcmp(command->word1, "quit") == 0){
    wantToQuit = true; //if user types quit, quit program
  }
  else if(strcmp(command->word1, "get") == 0){
    getItem(command, currentRoom, inventory); //this gets an item
  }
  else if(strcmp(command->word1, "drop") == 0){ //drops an item
    dropItem(command, currentRoom, inventory, sandwichVtr);
  }
  else if(strcmp(command->word1, "inventory") == 0){ //shows contents of inventory
    printInventory(inventory);
  }
  else if(strcmp(command->word1, "teleporter") == 0){ //shows contents of sandwich
    wantToQuit = printTeleporterContents(sandwichVtr);
  }
  return wantToQuit;
}

 //set up inventory and print what is in it
void printInventory(vector<Items*> *inventory) {
  cout << " " << endl;
  cout << "You are carrying:  " << endl;
  for(int i = 0; i < inventory->size(); i++){
    cout << inventory->at(i)->getName() << " " << endl;
  }
}

//set up teleporter content array and state what is in it
bool printTeleporterContents(vector<Items*> *sandwichVtr) {
  int count = 0; //amount of things in teleporter
  cout << " " << endl;
  cout << "The teleporter contains:  " << endl;
  for(int i = 0; i < sandwichVtr->size(); i++){
    cout << sandwichVtr->at(i)->getName() << " " << endl;
    count++;
  }
  //if there are 6 items in the teleporter you win
  if(count == 5){
    cout << "You have beat the Void and successfully made the teleporter!!" << endl;
    return true;
  }
  //otherwise they have not won yet so return false
  return false;
}
    
//if user types help, print out these messages
void printHelp(Parser *p){
  cout << "*************************************" << endl;
  cout << "You are lost in an alien catacombs." << endl;
  cout << "You need to build a teleporter with: a monitor, an antenna, fuel, a power switch, and an accelerator. " << endl;
  cout << "Your command words are: " << endl;
  cout << "go" << endl;
  cout << "get" << endl;
  cout << "drop" << endl;
  cout << "teleporter" << endl;
  cout << "quit" << endl;
  cout << "help" << endl;
  cout << "inventory" << endl;
  cout << "by the way, 'teleporter' returns contents of the teleporter." << endl;
  cout << "once you think you have dropped all 6 ingredients, type 'teleporter' to win!" << endl;
}

//traverse map by taking in direction and moving to room in that dir
void goRoom(tokens* command, Room* &currentRoom) {

  char* direction = command->word2;
  // Try to leave current room.
  Room* tempRoom= currentRoom->checkExits(direction);

  //if user tries to make up an exit..
  if (tempRoom == NULL){
    cout << "There is no door!" << endl;
  }
  else {
    currentRoom = tempRoom; //update current room
    cout << currentRoom->getLongDescription() << endl;
  }
  
}

//main class calls processCommand and creates vectors
int main(){
  //vectors
  vector<Room*> *roomVtr = new vector<Room*>();
  vector<Items*> *sandwichVtr = new vector<Items*>();
  vector<Items*> *inventory = new vector<Items*>();

  //set current room initially
  Room* currentRoom = NULL; 
  createRooms(roomVtr, currentRoom);
  currentRoom->getLongDescription();

  //create pointers to be passed around
  CommandWords *cw = new CommandWords();
  Parser *p = new Parser();
  bool finished = false;

  //while user has not won nor typed "quit"...
  while (finished == false){
    tokens* command = p->getCommand();
    finished = processCommand(command, currentRoom, inventory, p, sandwichVtr);
  }
  
  //program over!
  quit();
  return 0;
}

