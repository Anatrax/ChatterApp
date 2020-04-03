/**
 * @brief Implementation of class ClientData
 * @author Samuel D. Villegas
 * @date April 2, 2020
 */

#include "ClientData.h"

ClientData::ClientData() {
    this->current_conversation = connected_users.end();
}

unsigned int ClientData::getNumUsers() const {
   return this->connected_users.size();
}

bool ClientData::contains(const std::string& username) const {
   if(this->connected_users.find(username) != connected_users.end()) return true;
   return false;
}

std::map<std::string, Conversation>::iterator ClientData::findUser(const std::string& username){
   return this->connected_users.find(username);
}

int ClientData::addUser(const std::string& username){
      Conversation new_conversation(username);
      return std::get<1>(this->connected_users.emplace(username, new_conversation)) - 1;
}

int ClientData::removeUser(const std::string& username){
   auto it = this->connected_users.find(username);
   if(it != connected_users.end()) {
      connected_users.erase(it);  // Remove from map
      return 0;
   }
   return -1;
}

int ClientData::setCurrentConversation(const std::string& username){
   auto it = this->connected_users.find(username);
   if(it != connected_users.end()) {
       this->cur_convo = username;
       this->current_conversation = it;
      return 0;
   }
   return -1;
}

int ClientData::addMessage(const std::string& message){
    this->current_conversation->second.addMessage("You", message);
    return 0;
}

int ClientData::addMessage(const std::string& author, const std::string& message){
    if(author == "You") {
        this->current_conversation->second.addMessage("You", message);
        return 0;
    }
    auto it = this->connected_users.find(author);
    if(it != connected_users.end()) {
       it->second.addMessage(author, message);
       return 0;
    }
    return -1;
}

int ClientData::addMessage(const std::string& author, const std::string& message, const std::string& timestamp){
    if(author == "You") {
        this->current_conversation->second.addMessage("You", message, timestamp);
        return 0;
    }
    auto it = this->connected_users.find(author);
    if(it != connected_users.end()) {
       it->second.addMessage(author, message, timestamp);
       return 0;
    }
    return -1;
}

const std::string ClientData::getConversation() const {
    std::string message_list = "";

    // Get the current conversation
    auto it = this->connected_users.find(cur_convo);
    if(it != connected_users.end()) {
        // Format messages into a JSON string
        std::string message_list_json = "";
        for(auto message : it->second.messages) {
            message_list_json.append("{\"message\":\"<b>"+message.author+"</b>: "+message.contents+"\",\"timestamp\":\""+message.timestamp+"\"},");
        }
        message_list = "["+message_list_json.substr(0, message_list_json.size()-1)+"]";
    }

    return message_list;
}

std::string ClientData::getTimeStr() const {
    // Get current time
    time_t rawtime;
    time(&rawtime);

    // Convert to local time
    struct tm* timeinfo = localtime(&rawtime);

    // Format time string
    const int MAX_TIME_STR_LEN = 8;
    char buffer [MAX_TIME_STR_LEN];
    strftime (buffer,MAX_TIME_STR_LEN,"%I:%M%p",timeinfo);  // "Hours:Minutes{AM/PM}"

    std::string time(buffer);   // Convert char[] to std::string

    return time;
}

void ClientData::reset(){
    this->connected_users.clear();
    this->uname = "";
    this->uid = "";
    this->cur_convo = "";
}
