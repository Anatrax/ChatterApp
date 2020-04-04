/**
 * @brief Implementation of class Conversation
 * @author Samuel D. Villegas
 * @date April 2, 2020
 */
#include "Conversation.h"

Conversation::Conversation(const std::string& uname) {
    this->uname = uname;
}

std::string Conversation::getUname(){
    return this->uname;
}

unsigned int Conversation::length(){
    return messages.size();
}

void Conversation::addMessage(const std::string& author, const std::string& message) {
    struct Message new_message(author, message);
    messages.push_back(new_message);
}

void Conversation::addMessage(const std::string& author, const std::string& message, const std::string& timestamp) {
    struct Message new_message(author, message, timestamp);
    messages.push_back(new_message);
}
