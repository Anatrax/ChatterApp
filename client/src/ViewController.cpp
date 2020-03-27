/**
 * @brief Implementation of class Controller
 * @author Samuel D. Villegas
 * @date March 25, 2020
 * @todo Connect QML elements
 * @todo Send text input to server using QML WebSocket
 */

#include "ViewController.h"

ViewController::ViewController() {
    //SomeObject login_button;
    //SomeObject send_button;

    //SomeObject text_input;

    this->current_conversation = connected_users.end();
}

ViewController::~ViewController() {
    //SomeObject login_button;
    //SomeObject send_button;

    //SomeObject text_input;
}

int ViewController::getNumUsers(){
   return this->connected_users.size();
}

void ViewController::setTextInput(std::string text){
   //text_input.set();
}

std::string ViewController::getTextInput(){
   //return text_input.get();
}


bool ViewController::contains(std::string username){
   if(this->connected_users.find(username) != connected_users.end()) return true;
   return false;
}

std::map<std::string, Conversation>::iterator ViewController::findUser(std::string username){
   return this->connected_users.find(username);
}

int ViewController::addUser(std::string username){
      Conversation new_conversation(username);
      return std::get<1>(this->connected_users.emplace(username, new_conversation)) - 1;
}

int ViewController::removeUser(std::string username){
   auto it = this->connected_users.find(username);
   if(it != connected_users.end()) {
      connected_users.erase(it);  // Remove from map
      return 0;
   }
   return -1;
}

int ViewController::setCurrentConversation(std::string username){
   auto it = this->connected_users.find(username);
   if(it != connected_users.end()) {
      this->current_conversation = it;
      return 0;
   }
   return -1;
}

void ViewController::addMessage(std::string message){
   this->current_conversation->second.addMessage(message);
}

int ViewController::sendMessage(){
   this->addMessage(this->getTextInput());
   // Send text input contents to server
}