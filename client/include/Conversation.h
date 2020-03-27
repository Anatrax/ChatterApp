/**
 * @brief Definitions for class Message and class Conversation
 * @author Samuel D. Villegas
 * @date March 25, 2020
 * @todo Implement timestamp getters/setters
 */
#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <vector>
#include <string>
#include <ctime>

/**
 * @brief A message with a timestamp
 */
struct Message {
    std::string contents;   // Contents of message
    time_t timestamp;       // Timestamp

    /**
     * @brief Message constructor
     * @param message - The message string
     * @param timestamp - The message timestamp
     */
    Message(std::string message, time_t timestamp) {
        this->contents = message;
        this->timestamp = timestamp;
    }
};

/**
 * @brief A list of messages associated with a username
 */
class Conversation {
public:
    std::vector<struct Message> messages;   // List of messages

    /**
     * @brief Conversation Constructor
     * @param username - The name to associate the list of messages with
     */
    Conversation(std::string username);

    /**
     * @brief Returns the username associated with this conversation
     * @returns username
     */
    std::string getUsername();

    /**
     * @brief Returns the number of messages in the conversation
     * @returns number of messages
     */
    int length();

    /**
     * @brief Adds a message to the conversation
     * @param message - Message to add to the conversation
     */
    void addMessage(std::string message);

private:
    std::string username;   // Entity to have conversation with
};

#endif // CONVERSATION_H