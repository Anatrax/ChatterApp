/**
 * @brief Definitions for the Chatter client View Controller
 * @author Samuel D. Villegas
 * @date March 25, 2020
 */
#ifndef VIEW_CONTROLLER_H
#define VIEW_CONTROLLER_H

#include <map>
//#include "SomeObject.h"
#include "Conversation.h"

/**
 * @brief The Chatter client View Controller
 */
class ViewController {
public:
    //SomeObject login_button;
    //SomeObject send_button;

    //SomeObject text_input;

    std::map<std::string, Conversation>::iterator current_conversation; // Iterator to current conversation
    std::map<std::string, Conversation> connected_users;                // List of connected users

    /**
     * @brief ViewController Constructor
     */
    ViewController();

    /**
     * @brief ViewController Destructor
     */
    ~ViewController();

    /**
     * @brief Gets the number of connected users
     * @returns number of connected users
     */
    int getNumUsers();

    /**
     * @brief Sets the contents of the text input QML element
     * @param text - The text to put in the QML element
     */
    void setTextInput(std::string text);

    /**
     * @brief Gets the contents of the text input QML element
     * @returns a copy of the input text
     */
    std::string getTextInput();

    /**
     * @brief Checks if a username is in connected_users
     * @param username - Name of the user to find
     * @returns true if user is in connected_users
     */
    bool contains(std::string username);

    /**
     * @brief Find a conversation by username
     * @param username - Name of the user to find
     * @returns an iterator to conversation with user
     */
    std::map<std::string, Conversation>::iterator findUser(std::string username);

    /**
     * @brief Adds a user to the list of connected users
     * @param username - Name of the user to add
     * @returns 0 if user was added successfully, -1 otherwise
     */
    int addUser(std::string username);

    /**
     * @brief Removes a user from the list of connected users
     * @param username - Name of the user to remove
     * @returns 0 if user was removed successfully, -1 otherwise
     */
    int removeUser(std::string username);

    /**
     * @brief Points current_conversation* at the conversation with a specific user
     * @param username - Name of user to have a conversation with
     * @returns -1 if user doesn't exist, 0 otherwise
     */
    int setCurrentConversation(std::string username);

    /**
     * @brief Adds a message to the current conversation
     * @param message - Message to add to the current conversation
     */
    void addMessage(std::string message);

    /**
     * @brief Sends text input to server and adds it to the current conversation
     * @returns 0 on success, -1 otherwise
     */
    int sendMessage();
};

#endif // VIEW_CONTROLLER_H