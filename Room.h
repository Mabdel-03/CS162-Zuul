//header for room
#include <iostream>
#include "Items.h"
#include <vector>
#include <unordered_map>
using namespace std;


class Room {
public:
  void setDescription(char* inputDescription);
  char* getExits();
  void setExits(char* direction, Room* inputExits);
  char* getItems();
  void setItems(Items* inputItems);
  char* getLongDescription();
  char* getExitString();
  char* getRoom();
  Items* getItem(char* inputItem);
  void addItem(Items* inputItem);
  Room* checkExits(char* inputDirection);
  void removeItem(char* inputItem);
  Room(char* inputRoomName);
private:
  char description[200];
  char exitString[512];
  char roomName[50];
  unordered_map<char*, Room*> roomExits;
  vector<Items*> *itemVtr;
};
