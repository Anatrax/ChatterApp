import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: "\u002b"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: drawer.open()
        }

        Label {
            text: qsTr("Chatter")
            anchors.centerIn: parent
            padding: 10
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        ToolButton {
            anchors {
                right: parent.right
                rightMargin: 20
            }
            text: "\u2302\u21db"
            font.pixelSize: Qt.application.font.pixelSize * 2.6
            onClicked: {
                console.log("Logging out...")
                client.uname = ""   //TODO: complete client.reset()
                stackView.pop()
                socket.active = false
            }
        }
    }

    Label {
        anchors {
            top: parent.top
            topMargin: 20
        }
        padding: 10
        text: qsTr("Welcome to Chatter, " + client.uname + "!")
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.pixelSize: 20
    }

    Rectangle {
        anchors.centerIn: parent

        Text {
            anchors.centerIn: parent
            text: "No conversation selected.\nSelect the \'+\' to view the list of connected users."
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }
    }
}
