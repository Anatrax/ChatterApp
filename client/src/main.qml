import QtQuick 2.12
import QtQuick.Controls 2.2
import QtQuick.Window 2.12
import QtWebSockets 1.1

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

        Column {
            anchors.fill: parent

            Label {
                text: "<b>Connected Users</b>"
                padding: 10
                font.pixelSize: 20
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            ItemDelegate {
                text: qsTr("Connected User B")
                width: parent.width
                onClicked: {
                    stackView.push("ChatView.qml")
                    drawer.close()
                }
            }
//            ItemDelegate {
//                text: qsTr("Page 1")
//                width: parent.width
//                onClicked: {
//                    stackView.push("Page1Form.ui.qml")
//                    drawer.close()
//                }
//            }
//            ItemDelegate {
//                text: qsTr("Page 2")
//                width: parent.width
//                onClicked: {
//                    stackView.push("Page2Form.ui.qml")
//                    drawer.close()
//                }
//            }
        }
    }

    StackView {
        id: stackView
        initialItem: "CreateUserView.qml"
        anchors.fill: parent
    }

    WebSocket{
        id:socket
        active: true
        url: "ws://localhost:8080"
        onTextMessageReceived: function(message){
            console.log("Recieved:", message)
            socket.sendTextMessage("I received (" + message + ")")
        }
    }
}
