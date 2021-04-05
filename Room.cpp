//Room class contains all items in room, exits, descriptions
#include "Room.h"
#include <iostream>
#include <cstring>
#include <unordered_map>
#include <map>
#include <cstddef>
using namespace std;

void Room::setDescription(char* inputDescription){
  strcpy(description, inputDescription);

}

void Room::removeItem(char* inputItem){
  for(int i = 0; i < itemVtr->size(); i++){
    if(strcmp(itemVtr->at(i)->getName(), inputItem) == 0){
      itemVtr->erase(itemVtr->begin()+i);
      break;
    }
  }
}

void Room::addItem(Items* inputItem){
  itemVtr->push_back(inputItem);
}


//diff from getItems()
Items* Room::getItem(char* inputItem){
  for(int i = 0; i < itemVtr->size(); i++){
    if(strcmp(itemVtr->at(i)->getName(), inputItem) == 0){
      return itemVtr->at(i);
    }
  }
  return NULL;
}

Room* Room::checkExits(char* inputDirection){
  unordered_map<char*, Room*>:: iterator index;
  Room *nextRoom = NULL;
  for (index = roomExits.begin(); index != roomExits.end(); index++) {
    if (strcmp(index->first, inputDirection) ==0) {
      cout << " ***************************************" << endl;
      cout << "\nYou head " << inputDirection << " to " << index->second->getRoom() << endl;
      nextRoom = index->second;
    }
  }
  return nextRoom;
}

void Room::setExits(char* direction, Room* inputExits){
  roomExits.insert(make_pair(direction, inputExits));
}

char*  Room::getItems(){
  char* toReturn = new char[80];
  
  for(int i = 0; i < itemVtr->size(); i++){
    strcat(toReturn, "\n");
    strcat(toReturn, itemVtr->at(i)->getName());
    strcat(toReturn, "\n");
  }
  return toReturn; 
}

void Room::setItems(Items* inputItems){
  itemVtr->push_back(inputItems);
  
}

char* Room::getLongDescription(){
  char* output = new char[100];
  strcpy(output, getRoom());
  strcat(output, "\n");
  strcat(output, description);
  strcat(output, "\n");
  strcat(output, getExitString());
  return output;
}

//got from cplusplus.com
char* Room::getExitString(){
  unordered_map< char*, Room*>:: iterator index;
  strcpy(exitString, "\nExits in this room: \n");

  //iterate through room exits
  for (index = roomExits.begin(); index != roomExits.end(); index++) {
    strcat(exitString, index->first);
    strcat(exitString, "\n");
  }
  strcat(exitString, "\n");
  strcat(exitString, "Items in this room: \n");

  //get items from room
  if(strcmp(getItems(), "") == 0){ //if no items...
    strcat(exitString, "no items.");
  } else { //else get items
    strcat(exitString, " ");
    strcat(exitString, getItems());
  }
  return exitString;
}

//returns name of room
char* Room::getRoom(){
  return roomName;
}

//constructor to add items into room and set room name
Room::Room(char* inputRoomName){
  itemVtr = new vector<Items*>();
  strcpy(roomName, inputRoomName);
}
