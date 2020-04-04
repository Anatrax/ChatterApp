import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import QtWebSockets 1.1
import ChatClient.Backend 0.1

ApplicationWindow {
    id: window
    visible: true
    width: 400
    height: 500
    title: qsTr("Chatter")

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height


        ListView {
            focus: true
            currentIndex: -1
            anchors.fill: parent

            header: Label {
                text: "<b>Connected Users</b>"
                padding: 10
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            delegate: ItemDelegate {
                width: parent.width
                text: model.uname
                highlighted: ListView.isCurrentItem
                onClicked: {
                    client.cur_convo = model.uname
                    stackView.push("ChatView.qml")
                    drawer.close()
                }
            }

            model: ListModel { id: connected_users_list }

            ScrollIndicator.vertical: ScrollIndicator { }
        }
    }

    StackView {
        id: stackView
        initialItem: "LoginView.qml"
        anchors.fill: parent
    }

    // Backend
    Backend { id: client }

    WebSocket{
        id:socket
        active: false
        url: "ws://localhost:8080"
        onTextMessageReceived: function(message){
            console.log("Recieved:", message)
            var data = JSON.parse(message)

            switch(data.type){
            case 'TOKEN':
                // TOKEN is connection response from server
                // containing a unique ID for the client
                client.uid = data.id
                console.log("Set client user ID to: ", client.uid)

                // Client can now make its login request
                var login_request = JSON.stringify({type:'UN_REQ',uname:client.uname})
                socket.sendTextMessage(login_request)
                break;

            case 'LOGIN_FAIL':
                // LOGIN_FAIL means that the
                // requested username is already in use
                console.log("Login failed, username already in use")

                socket.active = false   // Disconnect from server
                // Show error message to user
                client.login_err = "Username is already taken. Try a different username."
                break;

            case 'LOGIN_SUCCESS':
                // LOGIN_SUCCESS contains the current list
                // of connected users from the chat server
                console.log("Login succeeded!")

                // Display this list in the client's
                // connected users list
                console.log(JSON.stringify(data.unames))
                data.unames.forEach(function initConnectedUsersList(user) {
                    console.log("Appending \""+user.uname+"\" to Connected Users List...")
                    connected_users_list.append(user)   // Add to visual model
                    client.addUser(user.uname)          // Add to data model
                });

                // Log the user in
                stackView.push("HomeView.qml")
                break;

            case 'ADD_UN':
                // ADD_UN contains the username
                // of a newly connected user
                console.log("New user, \""+data.uname+"\", connected")

                connected_users_list.append(data)   // Add to visual model
                client.addUser(data.uname)          // Add to data model
                break;

            case 'DEL_UN':
                // DEL_UN means a user has disconnected
                // and the client should remove the
                // username from its lists
                console.log("Deleting disconnected user, \""+data.uname+"\".")

                var i;
                for(i = 0; i < connected_users_list.count; i++) {
                    if(connected_users_list.get(i).uname === data.uname) {
                        connected_users_list.remove(i);    // Remove from visual model
                        client.removeUser(data.uname)    // Remove from data model
                        break;
                    }
                }
                break;

            case 'ADD_MSG':
                // ADD_MSG means that a message has
                // been sent to the client
                console.log("Received message from \""+data.author+"\": \""+data.message+"\"")

                //cur_convo message_list.append(data.message)   // Add to visual model
                client.addMessage(data.author, data.message, client.time)    // Add to data model
                break;
            default:
                break;
            }
        }
    }
}
