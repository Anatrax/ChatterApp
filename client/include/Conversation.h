/**
 * @brief Definitions for class Message and class Conversation
 * @author Samuel D. Villegas
 * @date April 2, 2020
 * @todo Implement timestamp update for other classes
 * @todo Add data cleanup/clearing
 */
#ifndef CONVERSATION_H
#define CONVERSATION_H

#include <vector>
#include <string>

/**
 * @brief A message with a timestamp
 */
struct Message {
    std::string author;                 // Author of the message
    std::string contents;               // Contents of message
    std::string timestamp = "--:--";    // Timestamp

    /**
     * @brief Message constructor: Message with default timestamp
     * @param author - The author of the message
     * @param message - The message string
     */
    Message(const std::string& author, const std::string& message) {
        this->author = author;
        this->contents = message;
    }

    /**
     * @brief Message constructor: Message & Timestamp
     * @param author - The author of the message
     * @param message - The message string
     * @param timestamp - The message timestamp string
     */
    Message(const std::string& author, const std::string& message, const std::string& timestamp) {
        this->author = author;
        this->contents = message;
        this->timestamp = timestamp;
    }
};

/**
 * @brief A list of messages associated with a username
 */
class Conversation {
public:

    /**
     * @brief Conversation Constructor
     * @param username - The name to associate the list of messages with
     */
    Conversation(const std::string& uname);

    /**
     * @brief Returns the username associated with this conversation
     * @returns username
     */
    std::string getUname();

    /**
     * @brief Returns the number of messages in the conversation
     * @returns number of messages
     */
    unsigned int length();

    /**
     * @brief Adds a message to the conversation
     * @param author - The author of the message
     * @param message - Message to add to the conversation
     */
    void addMessage(const std::string& author, const std::string& message);

    /**
     * @brief Adds a message to the conversation
     * @param author - The author of the message
     * @param message - Message to add to the conversation
     * @param timestamp - The message's timestamp
     */
    void addMessage(const std::string& author, const std::string& message, const std::string& timestamp);

    /**
     * @brief Updates timestamp
     * @param num_indeces - Number of indeces to update
     * @param indices - Indeces of the messages that need to get updated
     * @param timestamp - The new timestamp to update them with
     */
    void updateTimestamps(const int& num_indices, const unsigned int* indices, const std::string& timestamp);

    std::string uname;   // Entity to have conversation with
    std::vector<struct Message> messages;   // List of messages
};

#endif // CONVERSATION_H
