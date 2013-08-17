import QtQuick 1.1
import com.nokia.meego 1.0

Page {
    tools: commonTools

    function setStepsLabel(s) {
        stepsLabel.text = s;
    }

    Label {
        id: stepsLabel
        anchors.centerIn: parent
        text: qsTr("Training")
        visible: true
    }

    Button {
        anchors {
            horizontalCenter: parent.horizontalCenter
            top: stepsLabel.bottom
            topMargin: 10
        }
        text: qsTr("Reset")
        onClicked: appWindow.reset()
    }
}
