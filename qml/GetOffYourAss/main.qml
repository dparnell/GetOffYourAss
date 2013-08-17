import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    initialPage: mainPage

    property int steps: 0;

    function trainingStarted() {
        mainPage.setStepsLabel( qsTr("Calibrating..."));
    }

    function trainingFinished() {
        mainPage.setStepsLabel( qsTr("Calibration finished, now get off your ass!"));
    }

    function stepDetected() {
//        console.log("Got step");
        appWindow.steps = appWindow.steps + 1;
//        console.log("steps: " + appWindow.steps);
        mainPage.setStepsLabel( qsTr("Steps: " + appWindow.steps) );
    }

    function reset() {
        appWindow.steps = 0;        
        mainPage.setStepsLabel( qsTr("Steps: 0") );
    }

    MainPage {
        id: mainPage
    }

    ToolBarLayout {
        id: commonTools
        visible: true
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: (myMenu.status === DialogStatus.Closed) ? myMenu.open() : myMenu.close()
        }
    }

    Menu {
        id: myMenu
        visualParent: pageStack
        MenuLayout {
            MenuItem { text: qsTr("Sample menu item") }
        }
    }
}
