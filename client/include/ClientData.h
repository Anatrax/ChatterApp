/**
 * @brief Definitions for the Chatter Client data model
 * @author Samuel D. Villegas
 * @date April 2, 2020
 */
#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H

#include <map>
#include <ctime>
#include "Conversation.h"

/**
 * @brief The Chatter client data model
 */
class ClientData {
public:

    std::map<std::string, Conversation>::iterator current_conversation; // Iterator to current conversation
    std::map<std::string, Conversation> connected_users;                // List of connected users

    /**
     * @brief ClientData Constructor
     */
    ClientData();

    /**
     * @brief Gets the number of connected users
     * @returns number of connected users
     */
    unsigned int getNumUsers() const;

    /**
     * @brief Checks if a username is in connected_users
     * @param username - Name of the user to find
     * @returns true if user is in connected_users
     */
    bool contains(const std::string& username) const;

    /**
     * @brief Find a conversation by username
     * @param username - Name of the user to find
     * @returns an iterator to conversation with user
     */
    std::map<std::string, Conversation>::iterator findUser(const std::string& username);

    /**
     * @brief Adds a user to the list of connected users
     * @param username - Name of the user to add
     * @returns 0 if user was added successfully, -1 otherwise
     */
    int addUser(const std::string& username);

    /**
     * @brief Removes a user from the list of connected users
     * @param username - Name of the user to remove
     * @returns 0 if user was removed successfully, -1 otherwise
     */
    int removeUser(const std::string& username);

    /**
     * @brief Points current_conversation* at the conversation with a specific user
     * @param username - Name of user to have a conversation with
     * @returns -1 if user doesn't exist, 0 otherwise
     */
    int setCurrentConversation(const std::string& username);

    /**
     * @brief Adds a message to current conversation
     * @param message - Message to add to the current conversation
     * @returns 0
     */
    int addMessage(const std::string& message);

    /**
     * @brief Adds a message to the author's conversation
     * @param author - The author of the message
     * @param message - Message to add to the current conversation
     * @returns 0 on success, -1 otherwise
     */
    int addMessage(const std::string& author, const std::string& message);

    /**
     * @brief Adds a message to the author's conversation
     * @param author - The author of the message
     * @param message - Message to add to the current conversation
     * @param timestamp - The message's timestamp
     * @returns 0 on success, -1 otherwise
     */
    int addMessage(const std::string& author, const std::string& message, const std::string& timestamp);

    /**
     * @brief Gets the current time string
     * @returns current time
     */
    std::string getTimeStr() const;

    /**
     * @brief Gets the messages from the current conversation
     * @returns a JSON Object string of messages
     */
    const std::string getConversation() const;

    /**
     * @brief Clears all data and resets to default init state
     */
    void resetData();

    std::string uname;      // Client user's username
    std::string uid;        // Client user's server connection ID
    std::string cur_convo;  // Username of user that client user is conversing with
};

#endif // VIEW_CONTROLLER_H
