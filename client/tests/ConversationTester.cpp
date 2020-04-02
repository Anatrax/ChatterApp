/**
 * @brief Basic unit tests for class Conversation
 * @author Samuel D. Villegas
 * @date April 2, 2020
 */

//Bring in unit testing code
#include "catch.hpp"

//Include your .h files
#include <iostream>
#include <string>
#include "RandomStringGenerator.h"
#include "Conversation.h"

using namespace std;

TEST_CASE("Message Struct Defaults") {
    cout << "Testing Message Struct Defaults" << endl;
    RandomStringGenerator G;

    SECTION("2 argument Message Constructor Defaults"){
        cout << "Testing 2 argument Message Constructor Defaults" << endl;
        string author = G.randomString();
        string message = G.randomString();
        
        Message TestMessage(author, message);

        REQUIRE(TestMessage.author() == author);
        REQUIRE(TestMessage.contents() == message);
    }

    SECTION("3 argument Message Constructor Defaults"){
        cout << "Testing 3 argument Message Constructor Defaults" << endl;
        string author = G.randomString();
        string message = G.randomString();
        string timestamp = G.randomString();
        
        Message M(author, message, timestamp);

        REQUIRE(TestMessage.author() == author);
        REQUIRE(TestMessage.contents() == message);
        REQUIRE(TestMessage.timestamp() == timestamp);
    }
}

TEST_CASE("Conversation Constructor Defaults") {
    cout << "Testing Conversation Constructor Defaults" << endl;
    RandomStringGenerator G;
    string username = G.randomString();
    
    Conversation convo(username);

    REQUIRE(convo.length() == 0);   // Length just returns std::vector<>.size()
    REQUIRE(convo.getUsername() == username);
}

TEST_CASE("Add messages to the conversation, 2 args") {
    cout << "Testing adding messages to the conversation, 2 args" << endl;
    RandomStringGenerator G;

    SECTION("Matching conversation & author"){
        cout << "Testing adding message (2 args) with matching conversation & author" << endl;

        SECTION( "Number of messages in conversation increases" ) {
            cout << "Testing if the number of messages in conversation increases" << endl;
            string username = G.randomString();
            Conversation convo(username);
            int num_messages_previous = convo.length();
            string message = G.randomString();

            convo.addMessage(username, message);

            int num_messages_current = convo.length();
            REQUIRE(num_messages_current == num_messages_previous + 1);
        }

        SECTION( "Added message appears in conversation" ) {
            cout << "Testing if message appears in the conversation" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string message = G.randomString();

            convo.addMessage(username, message);

            string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
            REQUIRE(last_message_in_conversation == message);
        }

        SECTION( "Added message retains author information" ) {
            cout << "Testing if author appears in the added message" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string message = G.randomString();

            convo.addMessage(username, message);

            string author_of_last_message_in_conversation = convo.messages[convo.length() - 1].author;
            REQUIRE(author_of_last_message_in_conversation == username);
        }

        SECTION( "Can add at least 5000 messages" ) {
            cout << "Testing to see if a conversation can add at least 5000 messages" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string message = "";
            
            for(int i = 0; i < 5000; i++) {
                message = G.randomString();

                convo.addMessage(username, message);

                string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
                REQUIRE(last_message_in_conversation == message);
                string author_of_last_message_in_conversation = convo.messages[convo.length() - 1].author;
                REQUIRE(author_of_last_message_in_conversation == username);
            }

            int num_messages = convo.length();
            REQUIRE(num_messages == 5000);
        }
    }

    SECTION("Random author"){
        cout << "Testing adding message (2 args) with random author" << endl;

        SECTION( "Number of messages in conversation increases" ) {
            cout << "Testing if the number of messages in conversation increases" << endl;
            string username = G.randomString();
            Conversation convo(username);
            int num_messages_previous = convo.length();
            string author = G.randomString();
            string message = G.randomString();

            convo.addMessage(author, message);

            int num_messages_current = convo.length();
            REQUIRE(num_messages_current == num_messages_previous + 1);
        }

        SECTION( "Added message appears in conversation" ) {
            cout << "Testing if message appears in the conversation" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string author = G.randomString();
            string message = G.randomString();

            convo.addMessage(author, message);

            string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
            REQUIRE(last_message_in_conversation == message);
        }

        SECTION( "Added message retains author information" ) {
            cout << "Testing if author appears in the added message" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string author = G.randomString();
            string message = G.randomString();

            convo.addMessage(author, message);

            string author_of_last_message_in_conversation = convo.messages[convo.length() - 1].author;
            REQUIRE(author_of_last_message_in_conversation == author);
        }

        SECTION( "Can add at least 5000 messages" ) {
            cout << "Testing to see if a conversation can add at least 5000 messages" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string author = "";
            string message = "";
            
            for(int i = 0; i < 5000; i++) {
                author = G.randomString();
                message = G.randomString();

                convo.addMessage(author, message);

                string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
                REQUIRE(last_message_in_conversation == message);
                string author_of_last_message_in_conversation = convo.messages[convo.length() - 1].author;
                REQUIRE(author_of_last_message_in_conversation == author);
            }

            int num_messages = convo.length();
            REQUIRE(num_messages == 5000);
        }
    }
}

TEST_CASE("Add messages to the conversation, 3 args") {
    cout << "Testing adding messages to the conversation, 3 args" << endl;
    RandomStringGenerator G;

    SECTION("Matching conversation & author"){
        cout << "Testing adding message (3 args) with matching conversation & author" << endl;

        SECTION( "Number of messages in conversation increases" ) {
            cout << "Testing if the number of messages in conversation increases" << endl;
            string username = G.randomString();
            Conversation convo(username);
            int num_messages_previous = convo.length();
            string timestamp = G.randomString();
            string message = G.randomString();

            convo.addMessage(username, message, timestamp);

            int num_messages_current = convo.length();
            REQUIRE(num_messages_current == num_messages_previous + 1);
        }

        SECTION( "Added message appears in conversation" ) {
            cout << "Testing if message appears in the conversation" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string timestamp = G.randomString();
            string message = G.randomString();

            convo.addMessage(username, message, timestamp);

            string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
            REQUIRE(last_message_in_conversation == message);
        }

        SECTION( "Added message retains author information" ) {
            cout << "Testing if author appears in the added message" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string timestamp = G.randomString();
            string message = G.randomString();

            convo.addMessage(username, message, timestamp);

            string author_of_last_message_in_conversation = convo.messages[convo.length() - 1].author;
            REQUIRE(author_of_last_message_in_conversation == username);
        }

        SECTION( "Added message retains timestamp" ) {
            cout << "Testing if timestamp appears in the added message" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string timestamp = G.randomString();
            string message = G.randomString();

            convo.addMessage(username, message, timestamp);

            string timestamp_of_last_message_in_conversation = convo.messages[convo.length() - 1].timestamp;
            REQUIRE(timestamp_of_last_message_in_conversation == timestamp);
        }

        SECTION( "Can add at least 5000 messages" ) {
            cout << "Testing to see if a conversation can add at least 5000 messages" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string timestamp = "";
            string message = "";
            
            for(int i = 0; i < 5000; i++) {
                timestamp = G.randomString();
                message = G.randomString();

                convo.addMessage(username, message, timestamp);

                string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
                REQUIRE(last_message_in_conversation == message);
                string author_of_last_message_in_conversation = convo.messages[convo.length() - 1].author;
                REQUIRE(author_of_last_message_in_conversation == username);
                string timestamp_of_last_message_in_conversation = convo.messages[convo.length() - 1].timestamp;
                REQUIRE(timestamp_of_last_message_in_conversation == timestamp);
            }

            int num_messages = convo.length();
            REQUIRE(num_messages == 5000);
        }
    }

    SECTION("Random author"){
        cout << "Testing adding message (3 args) with random author" << endl;

        SECTION( "Number of messages in conversation increases" ) {
            cout << "Testing if the number of messages in conversation increases" << endl;
            string username = G.randomString();
            Conversation convo(username);
            int num_messages_previous = convo.length();
            string author = G.randomString();
            string timestamp = G.randomString();
            string message = G.randomString();

            convo.addMessage(author, message, timestamp);

            int num_messages_current = convo.length();
            REQUIRE(num_messages_current == num_messages_previous + 1);
        }

        SECTION( "Added message appears in conversation" ) {
            cout << "Testing if message appears in the conversation" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string author = G.randomString();
            string timestamp = G.randomString();
            string message = G.randomString();

            convo.addMessage(author, message, timestamp);

            string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
            REQUIRE(last_message_in_conversation == message);
        }

        SECTION( "Added message retains author information" ) {
            cout << "Testing if author appears in the added message" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string author = G.randomString();
            string timestamp = G.randomString();
            string message = G.randomString();

            convo.addMessage(author, message, timestamp);

            string author_of_last_message_in_conversation = convo.messages[convo.length() - 1].author;
            REQUIRE(author_of_last_message_in_conversation == author);
        }

        SECTION( "Added message retains timestamp" ) {
            cout << "Testing if timestamp appears in the added message" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string author = G.randomString();
            string timestamp = G.randomString();
            string message = G.randomString();

            convo.addMessage(author, message, timestamp);

            string timestamp_of_last_message_in_conversation = convo.messages[convo.length() - 1].timestamp;
            REQUIRE(timestamp_of_last_message_in_conversation == timestamp);
        }

        SECTION( "Can add at least 5000 messages" ) {
            cout << "Testing to see if a conversation can add at least 5000 messages" << endl;
            string username = G.randomString();
            Conversation convo(username);
            string author = "";
            string message = "";
            string timestamp = "";
            
            for(int i = 0; i < 5000; i++) {
                author = G.randomString();
                timestamp = G.randomString();
                message = G.randomString();

                convo.addMessage(author, message, timestamp);

                string last_message_in_conversation = convo.messages[convo.length() - 1].contents;
                REQUIRE(last_message_in_conversation == message);
                string author_of_last_message_in_conversation = convo.messages[convo.length() - 1].author;
                REQUIRE(author_of_last_message_in_conversation == author);
                string timestamp_of_last_message_in_conversation = convo.messages[convo.length() - 1].timestamp;
                REQUIRE(timestamp_of_last_message_in_conversation == timestamp);
            }

            int num_messages = convo.length();
            REQUIRE(num_messages == 5000);
        }
    }
}