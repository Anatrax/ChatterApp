/**
 * @brief Basic unit tests for class Conversation
 * @author Samuel D. Villegas
 * @date March 25, 2020
 * @todo Test timestamp getters/setters
 */

//Bring in unit testing code
#include "catch.hpp"

//Include your .h files
#include <iostream>
#include <string>
#include "RandomStringGenerator.h"
#include "Conversation.h"

using namespace std;

TEST_CASE("Conversation Constructor") {
    cout << "Testing Conversation Constructor" << endl;
    RandomStringGenerator G;
    std::string username = G.randomString();
    
    Conversation convo(username);

    REQUIRE(convo.length() == 0);   // Length just returns std::vector<>.size()
    REQUIRE(convo.getUsername() == username);
}

TEST_CASE("Add messages to the conversation") {
    cout << "Testing adding messages to the conversation" << endl;
    RandomStringGenerator G;

    SECTION( "Number of messages in conversation increases" ) {
        std::string username = G.randomString();
        Conversation convo(username);
        int num_messages_previous = convo.length();
        string message = G.randomString();

        convo.addMessage(message);

        int num_messages_current = convo.length();
        REQUIRE(num_messages_current == num_messages_previous + 1);
    }

    SECTION( "Added message appears in conversation" ) {
        std::string username = G.randomString();
        Conversation convo(username);
        string message = G.randomString();

        convo.addMessage(message);

        string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
        REQUIRE(last_message_in_conversation == message);
    }

    SECTION( "Can add at least 5000 messages" ) {
        std::string username = G.randomString();
        Conversation convo(username);
        string message = "";
        
        for(int i = 0; i < 5000; i++) {
            message = G.randomString();
            convo.addMessage(message);
            string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
            REQUIRE(last_message_in_conversation == message);
        }

        int num_messages = convo.length();
        REQUIRE(num_messages == 5000);
    }
}