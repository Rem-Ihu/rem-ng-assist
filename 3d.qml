import QtQuick
import QtQuick.Window
import QtQuick.Controls

import Qt.labs.platform
import Qt.labs.settings

import QtQuick3D
import QtQuick3D.Helpers
import QtQuick3D.AssetUtils

Window {
    visible: true
    width: 800
    height: 600

    property url importUrl;

    //! [base scene]
    View3D {
        id: view3D
        anchors.fill: parent
        environment: SceneEnvironment {
            backgroundMode: SceneEnvironment.SkyBox
            lightProbe: Texture {
                textureData: ProceduralSkyTextureData{}
            }
        }

        camera: helper.orbitControllerEnabled ? orbitCamera : wasdCamera

        DirectionalLight {
            eulerRotation: "-30, -20, -40"
            ambientColor: "#333"
        }

        Node {
            id: orbitCameraNode
            PerspectiveCamera {
                id: orbitCamera
            }
        }

        PerspectiveCamera {
            id: wasdCamera
        }

    //! [base scene]
        function resetView() {
            if (importNode.status === RuntimeLoader.Success) {
                helper.resetController()
            }
        }


        QtObject {
            id: helper
            property real boundsDiameter: 0
            property vector3d boundsCenter
            property vector3d boundsSize
            property bool orbitControllerEnabled: true

            function updateBounds(bounds) {
                boundsSize = Qt.vector3d(bounds.maximum.x - bounds.minimum.x,
                                         bounds.maximum.y - bounds.minimum.y,
                                         bounds.maximum.z - bounds.minimum.z)
                boundsDiameter = Math.max(boundsSize.x, boundsSize.y, boundsSize.z)
                boundsCenter = Qt.vector3d((bounds.maximum.x + bounds.minimum.x) / 2,
                                           (bounds.maximum.y + bounds.minimum.y) / 2,
                                           (bounds.maximum.z + bounds.minimum.z) / 2 )
                console.log("Bounds changed: ", bounds.minimum, bounds.maximum,
                            " center:", boundsCenter, "diameter:", boundsDiameter)

                wasdController.speed = boundsDiameter / 1000.0
                wasdController.shiftSpeed = 3 * wasdController.speed
                wasdCamera.clipNear = boundsDiameter / 100
                wasdCamera.clipFar = boundsDiameter * 10
                view3D.resetView()
            }

            function resetController() {
                orbitCameraNode.eulerRotation = Qt.vector3d(0, 0, 0)
                orbitCameraNode.position = boundsCenter
                orbitCamera.position = Qt.vector3d(0, 0, 2 * helper.boundsDiameter)
                orbitCamera.eulerRotation = Qt.vector3d(0, 0, 0)
                orbitControllerEnabled = true
            }

            function switchController(useOrbitController) {
                if (useOrbitController) {
                    let wasdOffset = wasdCamera.position.minus(boundsCenter)
                    let wasdDistance = wasdOffset.length()
                    let wasdDistanceInPlane = Qt.vector3d(wasdOffset.x, 0, wasdOffset.z).length()
                    let yAngle = Math.atan2(wasdOffset.x, wasdOffset.z) * 180 / Math.PI
                    let xAngle = -Math.atan2(wasdOffset.y, wasdDistanceInPlane) * 180 / Math.PI

                    orbitCameraNode.position = boundsCenter
                    orbitCameraNode.eulerRotation = Qt.vector3d(xAngle, yAngle, 0)
                    orbitCamera.position = Qt.vector3d(0, 0, wasdDistance)

                    orbitCamera.eulerRotation = Qt.vector3d(0, 0, 0)
                } else {
                    wasdCamera.position = orbitCamera.scenePosition
                    wasdCamera.rotation = orbitCamera.sceneRotation
                    wasdController.focus = true
                }
                orbitControllerEnabled = useOrbitController
            }
        }

        //! [runtimeloader]
        RuntimeLoader {
            id: importNode
            source: importUrl
//            instancing: instancingButton.checked ? instancing : null
            onBoundsChanged: helper.updateBounds(bounds)
        }
        //! [runtimeloader]

        //! [bounds]
        Model {
            parent: importNode
            source: "#Cube"
            materials: PrincipledMaterial {
                baseColor: "blue"
            }
            opacity: 0.2
            visible: visualizeButton.checked && importNode.status === RuntimeLoader.Success
            position: helper.boundsCenter
            scale: Qt.vector3d(helper.boundsSize.x / 100,
                               helper.boundsSize.y / 100,
                               helper.boundsSize.z / 100)
        }
        //! [bounds]

        //! [status report]
        Rectangle {
            id: messageBox
            visible: importNode.status !== RuntimeLoader.Success
            color: "purple"
            width: parent.width * 0.8
            height: parent.height * 0.8
            anchors.centerIn: parent
            radius: Math.min(width, height) / 10
            opacity: 1
            Text {
                anchors.fill: parent
                font.pixelSize: 36
                text: "Status: " + importNode.errorString + "\nPress \"Import\" to import any model."
                color: "white"
                font.bold: true
                wrapMode: Text.Wrap
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }
        //! [status report]
    }

    //! [camera control]
    OrbitCameraController {
        id: orbitController
        origin: orbitCameraNode
        camera: orbitCamera
        enabled: helper.orbitControllerEnabled
    }
    WasdController {
        id: wasdController
        controlledObject: wasdCamera
        enabled: !helper.orbitControllerEnabled
    }
    //! [camera control]

    Column {
            spacing: 10  // Adjust the spacing between buttons
            anchors.horizontalCenter: parent.horizontalCenter  // Center the buttons horizontally

            Row {
                spacing: 10  // Adjust the spacing between buttons

                RoundButton {
                    id: importButton
                    text: "Import Model"
                    onClicked: fileDialog.open()
                    focusPolicy: Qt.NoFocus
                    padding: 10
                    background: Rectangle {
                        radius: 5
                        color: "purple"
                    }
                    contentItem: Text {
                        text: importButton.text
                        font.family: "Arial"
                        font.bold: true
                        font.pixelSize: 16
                        color: "white"
                        anchors.centerIn: parent
                    }
                }

                RoundButton {
                    id: resetButton
                    text: "Reset 3D view"
                    onClicked: view3D.resetView()
                    focusPolicy: Qt.NoFocus
                    padding: 10
                    background: Rectangle {
                        radius: 5
                        color: "purple"
                    }
                    contentItem: Text {
                        text: resetButton.text
                        font.family: "Arial"
                        font.bold: true
                        font.pixelSize: 16
                        color: "white"
                        anchors.centerIn: parent
                    }
                }

                RoundButton {
                    id: visualizeButton
                    checkable: true
                    text: "Visualize Bounds"
                    focusPolicy: Qt.NoFocus
                    padding: 10
                    background: Rectangle {
                        radius: 5
                        color: "purple"
                    }
                    contentItem: Text {
                        text: visualizeButton.text
                        font.family: "Arial"
                        font.bold: true
                        font.pixelSize: 16
                        color: "white"
                        anchors.centerIn: parent
                    }
                }
            }
        }
    FileDialog {
        id: fileDialog
        nameFilters: ["glTF files (*.gltf *.glb)", "All files (*)"]
        onAccepted: importUrl = file
//        Settings {
//            id: fileDialogSettings
//            category: "QtQuick3D.Examples.RuntimeLoader"
//            property alias folder: fileDialog.folder
//        }
    }
}
