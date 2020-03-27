/**
 * @brief Implementation of class Conversation
 * @author Samuel D. Villegas
 * @date March 25, 2020
 * @todo Implement timestamp getters/setters
 */
#include "Conversation.h"

Conversation::Conversation(std::string username) {
    this->username = username;
}

std::string Conversation::getUsername(){
    return this->username;
}

int Conversation::length(){
    return messages.size();
}

void Conversation::addMessage(std::string message) {
    struct Message new_message(message, time(NULL));
    messages.push_back(new_message);
}
