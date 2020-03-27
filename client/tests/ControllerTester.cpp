/**
 * @brief Basic unit tests for the Chatter client View Controller
 * @author Samuel D. Villegas
 * @date March 25, 2020
 */

//Bring in unit testing code
#include "catch.hpp"

//Include your .h files
#include <iostream>
#include <random>
#include <string>
#include "RandomStringGenerator.h"
#include "ViewController.h"

using namespace std;

TEST_CASE("ViewController Constructor") {
    cout << "Testing ViewController Constructor" << endl;
    ViewController state;
    REQUIRE(state.getNumUsers() == 0);
}

// TEST_CASE("Text input") {
//     cout << "Testing text input getters & setters" << endl;
//     ViewController state;
//     RandomStringGenerator G;
//     string str = G.randomString();

//     state.setTextInput(str);

//     REQUIRE(state.getTextInput() == str);
// }

TEST_CASE("Add users to connected users list") {
    cout << "Testing adding users to & finding users in connected users list" << endl;
    RandomStringGenerator G;

    SECTION( "Number of connected users increases" ) {
        ViewController state;
        int num_users_previous = state.getNumUsers();
        string connected_username = G.randomString();

        state.addUser(connected_username);

        int num_users_current = state.getNumUsers();
        REQUIRE(num_users_current == num_users_previous + 1);
    }

    SECTION( "Can add at least 500 connected users" ) {
        ViewController state;

        for(int i = 0; i < 500; i++) {
            string connected_username = G.randomString();
            state.addUser(connected_username);
        }

        int num_users = state.getNumUsers();
        REQUIRE(num_users == 500);
    }

    SECTION( "Username appears/is searchable in connected user list" ) {
        ViewController state;
        string connected_username = G.randomString();
        REQUIRE(state.findUser(connected_username) == state.connected_users.end());

        state.addUser(connected_username);

        REQUIRE(state.findUser(connected_username) != state.connected_users.end());
    }
}

TEST_CASE("Remove users from connected users list") {
    cout << "Testing removing users from & finding users in connected users list" << endl;
    RandomStringGenerator G;

    SECTION( "Number of connected users decreases" ) {
        ViewController state;
        int num_users_previous = state.getNumUsers();
        string connected_username = G.randomString();
        state.addUser(connected_username);
        int num_users_current = state.getNumUsers();
        REQUIRE(num_users_current == num_users_previous + 1);
        num_users_previous = state.getNumUsers();

        state.removeUser(connected_username);

        num_users_current = state.getNumUsers();
        REQUIRE(num_users_current == num_users_previous - 1);
    }

    SECTION( "Can remove at least 500 added connected users" ) {
        ViewController state;
        string connected_username = "";
        for(int i = 0; i < 500; i++) {
            connected_username = G.randomString();
            state.addUser(connected_username);
        }
        int num_users = state.getNumUsers();
        REQUIRE(num_users == 500);

        auto itr = state.connected_users.begin();
        while (itr != state.connected_users.end())
            itr = state.connected_users.erase(itr);

        num_users = state.getNumUsers();
        REQUIRE(num_users == 0);
    }

    SECTION( "Cannot remove user that does not exist in connected users list" ) {
        ViewController state;
        string connected_username = G.randomString();
        state.addUser(connected_username);
        string some_random_username = "";
        while(some_random_username == connected_username)
            some_random_username = G.randomString();

        REQUIRE(-1 == state.removeUser(some_random_username));
    }

    SECTION( "Cannot remove user from empty connected users list" ) {
        ViewController state;
        int num_users = state.getNumUsers();
        REQUIRE(num_users == 0);
        string some_random_username = G.randomString();

        REQUIRE(-1 == state.removeUser(some_random_username));
    }

    SECTION( "Username does not appear/is not searchable in connected user list" ) {
        ViewController state;
        string connected_username = G.randomString();
        REQUIRE(state.findUser(connected_username) == state.connected_users.end());
        state.addUser(connected_username);
        REQUIRE(state.findUser(connected_username) != state.connected_users.end());
        state.removeUser(connected_username);
        REQUIRE(state.findUser(connected_username) == state.connected_users.end());
    }
}

TEST_CASE("Add messages to a conversation") {
    cout << "Testing Add messages to a conversation" << endl;
    RandomStringGenerator G;

    SECTION( "Number of messages in conversation increases" ) {
        ViewController state;
        string connected_username = G.randomString();
        state.addUser(connected_username);
        state.setCurrentConversation(connected_username);
        int num_messages_previous = state.current_conversation->second.length();
        string message = G.randomString();

        state.addMessage(message);

        int num_messages_current = state.current_conversation->second.length();
        REQUIRE(num_messages_current == num_messages_previous + 1);
    }

    SECTION( "Added message appears in conversation" ) {
        ViewController state;
        string connected_username = G.randomString();
        state.addUser(connected_username);
        state.setCurrentConversation(connected_username);
        string message = G.randomString();

        state.addMessage(message);

        string last_message_in_conversation = state.current_conversation->second.messages.back().contents;  // Messy last message access
        REQUIRE(last_message_in_conversation == message);
    }

    SECTION( "Can add at least 5000 messages" ) {
        ViewController state;
        string connected_username = G.randomString();
        state.addUser(connected_username);
        state.setCurrentConversation(connected_username);
        string message = "";
        
        for(int i = 0; i < 5000; i++) {
            message = G.randomString();
            state.addMessage(message);
            string last_message_in_conversation = state.current_conversation->second.messages.back().contents;  // Messy last message access
            REQUIRE(last_message_in_conversation == message);
        }

        int num_messages = state.current_conversation->second.length();
        REQUIRE(num_messages == 5000);
    }
}

// // Tests sendMessage()
// // Consider moving to ModelTester?
// TEST_CASE("Add text input to a conversation") {
//     cout << "Testing Add text input to a conversation" << endl;
//     RandomStringGenerator G;

//     SECTION( "Number of messages in conversation increases" ) {
//         ViewController state;
//         string connected_username = G.randomString();
//         state.addUser(connected_username);
//         state.setCurrentConversation(connected_username);
//         int num_messages_previous = state.current_conversation->second.length();
//         string message = G.randomString();
//         state.setTextInput(message);

//         state.sendMessage();

//         int num_messages_current = state.current_conversation->second.length();
//         REQUIRE(num_messages_current == num_messages_previous + 1);
//     }

//     SECTION( "Text input appears in conversation" ) {
//         ViewController state;
//         string connected_username = G.randomString();
//         state.addUser(connected_username);
//         state.setCurrentConversation(connected_username);
//         string message = G.randomString();
//         state.setTextInput(message);

//         state.sendMessage();

//         string last_message_in_conversation = state.current_conversation->second.messages.back().contents;  // Messy last message access
//         REQUIRE(last_message_in_conversation == message);
//     }

//     SECTION( "Text input is cleared" ) {
//         ViewController state;
//         string connected_username = G.randomString();
//         state.addUser(connected_username);
//         state.setCurrentConversation(connected_username);
//         string message = G.randomString();
//         state.setTextInput(message);

//         state.sendMessage();

//         string text_input = state.getTextInput();
//         REQUIRE(text_input == "");  // Or possibly the placeholder string
//     }
// }