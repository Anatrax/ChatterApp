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
        url: "ws://localhost:8888"  //TODO: Change to 8080
        onTextMessageReceived: function(message){
            console.log("Recieved:", message)
            connected_users_list.append({"uname":"User A"})//data.uname);
            connected_users_list.append({"uname":"User B"})//data.uname);
            connected_users_list.append({"uname":"User C"})//data.uname);
            client.addUser("User A")//data.uname);
            client.addUser("User B")//data.uname);
            client.addUser("User C")//data.uname);
            //socket.sendTextMessage("I received (" + message + ")")
        }
    }
}
