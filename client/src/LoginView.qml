import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Page {
    Layout.fillWidth: true

    RowLayout {
        anchors.centerIn: parent

        TextArea {
            Layout.fillWidth: true
            wrapMode: TextArea.Wrap
            placeholderText: qsTr("Create a username...")

            text: client.uname
            onTextChanged: client.uname = text
        }

        Button {
            text: qsTr("Launch")
            enabled: client.uname.length > 0
            onClicked: {
                console.log("Creating user: " + client.uname)
                socket.active = true    // Connect chat client to chat server
                stackView.push("HomeView.qml")
            }
        }
    }
}
